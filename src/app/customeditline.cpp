/*
 *   This file is part of Maily.
 *
 *   Maily is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Maily is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Maily. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QPainter>
#include <QStyleOption>

#include "customeditline.h"

namespace Maily
{
namespace Widgets
{

namespace Details
{
    struct CustomEditLinePrivate
    {
        CustomEditLinePrivate() :
            m_drawEmptyMsg(true)
        {

        }

        bool m_drawEmptyMsg;
        QString m_emptyMessage;
    };
}


CustomEditLine::CustomEditLine(QWidget *parent) :
    QLineEdit(parent), m_data(new Details::CustomEditLinePrivate())
{

}

CustomEditLine::~CustomEditLine()
{
    delete m_data;
}

void CustomEditLine::setEmptyMessage(const QString& msg)
{
    Q_ASSERT(m_data);
    if (!m_data)
        return;

    m_data->m_emptyMessage = msg;
    m_data->m_drawEmptyMsg = text().isEmpty();
    update();
}

void CustomEditLine::paintEvent(QPaintEvent* ev)
{
    QLineEdit::paintEvent(ev);

    Q_ASSERT(m_data);
    if (!m_data)
        return;

    if (text().isEmpty()) {
        QPainter p(this);
        QFont f = font();
        f.setItalic(true);
        p.setFont(f);

        QColor color(palette().color(foregroundRole()));
        color.setAlphaF(0.5);
        p.setPen(color);

        QStyleOptionFrame opt;
        initStyleOption(&opt);
        QRect cr = style()->subElementRect(QStyle::SE_LineEditContents, &opt, this);
        cr.setLeft(cr.left() + 2);
        cr.setRight(cr.right() - 2);

        p.drawText(cr, Qt::AlignLeft | Qt::AlignVCenter, m_data->m_emptyMessage);
    }
}

void CustomEditLine::focusInEvent(QFocusEvent* ev)
{
    Q_ASSERT(m_data);
    if (!m_data)
        return;

    if (m_data->m_drawEmptyMsg) {
        m_data->m_drawEmptyMsg = false;
        update();
    }

    QLineEdit::focusInEvent(ev);
}

void CustomEditLine::focusOutEvent( QFocusEvent* ev)
{
    Q_ASSERT(m_data);
    if (!m_data)
        return;

    if (text().isEmpty()) {
        m_data->m_drawEmptyMsg = true;
        update();
    }

    QLineEdit::focusOutEvent(ev);
}

} // namespace Widgets
} // namespace Maily
