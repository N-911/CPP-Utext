#include <QVBoxLayout>
#include <QButtonGroup>

#include <QRadioButton>
#include "tabSetings.h"
#include "app.h"

#include "loggingcategories.h"



TabSetings::TabSetings(QWidget *parent) : QWidget(parent) {
    settings = App::utext_app()->utext_settings();

    auto mlayout = new QVBoxLayout();
    setLayout(mlayout);

    // create some buttons
    auto rb_frst = new QRadioButton("first");
    auto rb_scnd = new QRadioButton("second");
    auto rb_thrd = new QRadioButton("third");
    auto buttonGroup = new QButtonGroup();

    buttonGroup->addButton(rb_frst,0);
    buttonGroup->addButton(rb_scnd,1);
    buttonGroup->addButton(rb_thrd,2);
    // layout buttons for visual representation
    auto rb_layout = new QHBoxLayout();
    rb_layout->addWidget(rb_frst);
    rb_layout->addWidget(rb_scnd);
    rb_layout->addWidget(rb_thrd);
    mlayout->addLayout(rb_layout);

    // use Functor-Based Connection due to overloaded buttonReleased
    connect( buttonGroup,
             SIGNAL(buttonReleased(int)),
             this,
             SLOT(handle_buttonReleased(int)));

    // restore button from settings
    int id = settings->value("buttonGroup").toInt();
    buttonGroup->button(id)->setChecked(true);
}

void
TabSetings::handle_buttonReleased(int id)
{
    // save new status to the settings
    qInfo(logInfo()) << "handle_buttonReleased" << id;
//    settings->setValue("buttonGroup", id);
}