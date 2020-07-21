#include "CompletionSelector.hpp"

#include "controllers/accounts/AccountController.hpp"
#include "debug/Benchmark.hpp"
#include "messages/Message.hpp"
#include "messages/MessageBuilder.hpp"
#include "providers/twitch/TwitchChannel.hpp"
#include "singletons/Emotes.hpp"
#include "singletons/WindowManager.hpp"
#include "widgets/helper/ChannelView.hpp"

#include <QApplication>
#include <QHBoxLayout>
#include <QShortcut>
#include <QTabWidget>

CompletionSelector::CompletionSelector(QWidget *parent)
    : BaseWindow(BaseWindow::EnableCustomFrame)
{
    this->setWindowTitle("Autocomplete Selector");
    this->setStayInScreenRect(true);

    auto layout = new QVBoxLayout(this);
    this->getLayoutContainer()->setLayout(layout);

    auto notebook = new Notebook(this);
    layout->addWidget(notebook);
    layout->setMargin(0);

    auto clicked = [this](const Link &link) { this->linkClicked.invoke(link); };

    auto makeView = [&](QString tabTitle) {
        auto view = new ChannelView();

        view->setOverrideFlags(MessageElementFlags{
            MessageElementFlag::Default, MessageElementFlag::AlwaysShow,
            MessageElementFlag::EmoteImages});
        view->setEnableScrollingToBottom(false);
        notebook->addPage(view, tabTitle);
        view->linkClicked.connect(clicked);

        return view;
    };
    
    
    this->viewEmojis_ = makeView("Emojis");
}

    void CompletionSelector::refresh(QString matchList)
    {
        auto &emojis = getApp()->emotes->emojis.emojis;

        ChannelPtr emojiChannel(new Channel("", Channel::Type::None));

        // emojis
        MessageBuilder builder;
        builder->flags.set(MessageFlag::Centered);
        builder->flags.set(MessageFlag::DisableCompactEmotes);

        emojis.each([&builder](const auto &key, const auto &value) {
            
            if (value.name.find(matchList) != std::string::npos) {
                builder
                    .emplace<EmoteElement>(value->emote, MessageElementFlag::AlwaysShow)
                    ->setLink(
                        Link(Link::Type::InsertText, ":" + value->shortCodes[0] + ":"));
            }
        });
        emojiChannel->addMessage(builder.release());

        this->viewEmojis_->setChannel(emojiChannel);
    }

    void CompletionSelector::closeEvent(QCloseEvent *event)
    {
        //getApp()->windows->setEmotePopupPos(this->pos());
        QWidget::closeEvent(event);
    }
