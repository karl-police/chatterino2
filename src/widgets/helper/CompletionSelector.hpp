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
    Q_OBJECT

public:
    CompletionSelector(QWidget *parent = nullptr);

    void loadChannel(ChannelPtr channel);

    virtual void closeEvent(QCloseEvent *event) override;

    pajlada::Signals::Signal<Link> linkClicked;

    void refresh(const QString matchString);

private:
    ChannelView *viewEmojis_{};
};
