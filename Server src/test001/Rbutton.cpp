
#include <QtWidgets>

#include "Rbutton.h"

//! [0]
RButton::RButton(const QString &text, QWidget *parent)
    : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
}
//! [0]

//! [1]
QSize RButton::sizeHint() const
//! [1] //! [2]
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}
//! [2]
