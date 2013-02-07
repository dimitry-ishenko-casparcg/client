#pragma once

#include "../Shared.h"
#include "AbstractRundownWidget.h"
#include "ui_RundownKeyerWidget.h"
#include "GpiDevice.h"

#include "Global.h"

#include "Animations/ColorAnimation.h"
#include "Commands/AbstractCommand.h"
#include "Commands/AbstractPlayoutCommand.h"
#include "Commands/KeyerCommand.h"
#include "Models/LibraryModel.h"

#include <QtCore/QString>
#include <QtCore/QTimer>

#include <QtGui/QWidget>

class WIDGETS_EXPORT RundownKeyerWidget : public QWidget, Ui::RundownKeyerWidget, public AbstractRundownWidget, public AbstractPlayoutCommand
{
    Q_OBJECT

    public: 
        explicit RundownKeyerWidget(const LibraryModel& model, QWidget* parent = 0,
                                    const QString& color = Color::DEFAULT_TRANSPARENT_COLOR, bool active = false,
                                    bool inGroup = false, bool disconnected = false, bool compactView = false);

        virtual AbstractRundownWidget* clone();

        virtual bool isGroup() const;

        virtual AbstractCommand* getCommand();
        virtual LibraryModel* getLibraryModel();

        virtual void setActive(bool active);
        virtual void setInGroup(bool inGroup);
        virtual void setColor(const QString& color);

        virtual void setExpanded(bool expanded) {}

        virtual bool executeCommand(enum Playout::PlayoutType::Type type);

        virtual void readProperties(boost::property_tree::wptree& pt);
        virtual void writeProperties(QXmlStreamWriter* writer);

        virtual void setCompactView(bool compactView);

    protected:
        virtual bool eventFilter(QObject* target, QEvent* event);

    private:
        bool active;
        bool inGroup;
        bool disconnected;
        bool compactView;
        QString color;
        LibraryModel model;
        KeyerCommand command;
        ColorAnimation* animation;

        QTimer executeTimer;

        void checkEmptyDevice();
        void checkGpiTriggerable();

        Q_SLOT void executeClearVideolayer();
        Q_SLOT void executeClearChannel();
        Q_SLOT void channelChanged(int);
        Q_SLOT void executePlay();
        Q_SLOT void executeStop();
        Q_SLOT void videolayerChanged(int);
        Q_SLOT void delayChanged(int);
        Q_SLOT void allowGpiChanged(bool);
        Q_SLOT void gpiDeviceConnected(bool, GpiDevice*);
};
