#include "CompletionSelector.hpp"

#include "Application.hpp"
#include "controllers/accounts/AccountController.hpp"
#include "debug/Benchmark.hpp"
#include "messages/Message.hpp"
#include "messages/MessageBuilder.hpp"
#include "providers/twitch/TwitchChannel.hpp"
#include "singletons/Emotes.hpp"
#include "singletons/WindowManager.hpp"
#include "widgets/Notebook.hpp"
#include "widgets/helper/ChannelView.hpp"
#include "util/LayoutCreator.hpp"
#include "widgets/Label.hpp"

#include <QApplication>
#include <QHBoxLayout>
#include <QShortcut>
#include <QTabWidget>


namespace chatterino {
CompletionSelector::CompletionSelector()
    : BaseWindow(BaseWindow::EnableCustomFrame)
{
#ifdef Q_OS_LINUX
    this->setWindowFlag(Qt::Popup);
#endif

    this->setWindowTitle("Autocomplete Selector");
    this->setStayInScreenRect(true);

    auto layout = LayoutCreator<QWidget>(this->getLayoutContainer())
                      .setLayoutType<QHBoxLayout>();
    
    auto mainbox = layout.emplace<QVBoxLayout>().withoutMargin();
    {
        // emotebox
        auto emotebox = mainbox.emplace<QHBoxLayout>().withoutMargin();
        {
            // emote item
            auto emoteitem = emotebox.emplace<QVBoxLayout>().withoutMargin();
            emoteitem.emplace<Label>("test")
                .assign(&this->ui_.testLabel);
        }
    }

    auto clicked = [this](const Link &link) { this->linkClicked.invoke(link); };

   /* auto makeView = [&](QString tabTitle) {
        auto view = new ChannelView();

       view->setOverrideFlags(MessageElementFlags{
            MessageElementFlag::Default, MessageElementFlag::AlwaysShow,
            MessageElementFlag::EmoteImages});
        view->setEnableScrollingToBottom(false);
        view->linkClicked.connect(clicked);

        return view;
    };
    
    
    this->viewEmojis_ = makeView("Emojis");*/
}
    
    // refresh function
    void CompletionSelector::refresh(QString matchString)
    {
        /*auto &emojis = getApp()->emotes->emojis.emojis;

        ChannelPtr emojiChannel(new Channel("", Channel::Type::None));

        // emojis
        MessageBuilder builder;
        builder->flags.set(MessageFlag::Centered);
        builder->flags.set(MessageFlag::DisableCompactEmotes);

        emojis.each([&builder, matchString](const auto &key, const auto &value) {
            
            if (value->shortCodes[0].contains(matchString, Qt::CaseInsensitive) == true) {
                builder
                    .emplace<EmoteElement>(value->emote, MessageElementFlag::AlwaysShow)
                    ->setLink(
                        Link(Link::Type::InsertText, ":" + value->shortCodes[0] + ":"));
            }
        });
        emojiChannel->addMessage(builder.release());

        this->viewEmojis_->setChannel(emojiChannel);*/
        
        this->ui_.testLabel->setText(matchString);
    }

    void CompletionSelector::closeEvent(QCloseEvent *event)
    {
        //getApp()->windows->setEmotePopupPos(this->pos());
        QWidget::closeEvent(event);
    }
    
} //namespace chatterino
