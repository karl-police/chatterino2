#pragma once

#include "widgets/BaseWindow.hpp"

#include <pajlada/signals/signal.hpp>

namespace chatterino {

struct Link;
class ChannelView;
class Channel;
using ChannelPtr = std::shared_ptr<Channel>;
class Label;

class CompletionSelector : public BaseWindow
{
    //Q_OBJECT

public:
    CompletionSelector();

    void loadChannel(ChannelPtr channel);

    virtual void closeEvent(QCloseEvent *event) override;

    pajlada::Signals::Signal<Link> linkClicked;
    
    void UpdateSelectorModel(QAbstractItemModel* model);

    void refresh(const QString matchString);

private:
    //ChannelView *viewEmojis_{};
      
    struct {
        Label *testLabel = nullptr;
        QHBoxLayout *test2Layout = nullptr;
    } ui_;
};
    
} //namespace chatterino
