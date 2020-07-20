#pragma once

#include "widgets/BaseWindow.hpp"

#include <pajlada/signals/signal.hpp>

namespace chatterino {

struct Link;
class ChannelView;
class Channel;
using ChannelPtr = std::shared_ptr<Channel>;

class CompletionSelector : public BaseWindow
{
public:
    CompletionSelector(QWidget *parent = nullptr);

    void loadChannel(ChannelPtr channel);
    void loadEmojis();

    virtual void closeEvent(QCloseEvent *event) override;

    pajlada::Signals::Signal<Link> linkClicked;

    void setCompleter(QCompleter *c);
    QCompleter *completer() const;

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void focusInEvent(QFocusEvent *e) override;

private slots:
    void insertCompletion(const QString &completion);

private:
    QString textUnderCursor() const;

private:
    QCompleter *c = nullptr;

private:
    ChannelView *globalEmotesView_{};
    ChannelView *channelEmotesView_{};
    ChannelView *subEmotesView_{};
    ChannelView *viewEmojis_{};
};
