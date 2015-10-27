#ifndef RBUTTON_H
#define RBUTTON_H

#include <QToolButton>

//! [0]
class RButton : public QToolButton
{
    Q_OBJECT

public:
    explicit RButton(const QString &text, QWidget *parent = 0);

    QSize sizeHint() const;
};
//! [0]

#endif
