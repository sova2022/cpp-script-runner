#include "canvas.h"

#include <QPainter>
#include <QPolygonF>

CanvasWidget::CanvasWidget(QWidget* parent) : QWidget(parent) {
    setMinimumSize(400, 400);
}

void CanvasWidget::AddLine(double x1, double y1, double x2, double y2, QColor color)
{
    DrawCommand cmd;
    cmd.type = Type::Line;
    cmd.color = color;
    cmd.x1 = x1; cmd.y1 = y1;
    cmd.x2 = x2; cmd.y2 = y2;
    cmds_.append(cmd);
    update();
}

void CanvasWidget::AddRect(double x, double y, double w, double h, QColor color)
{
    DrawCommand cmd;
    cmd.type = Type::Rect;
    cmd.color = color;
    cmd.x1 = x; cmd.y1 = y;
    cmd.w = w; cmd.h = h;
    cmds_.append(cmd);
    update();
}

void CanvasWidget::AddEllipse(double x, double y, double w, double h, QColor color)
{
    DrawCommand cmd;
    cmd.type = Type::Ellipse;
    cmd.color = color;
    cmd.x1 = x; cmd.y1 = y;
    cmd.w = w; cmd.h = h;
    cmds_.append(cmd);
    update();
}

void CanvasWidget::AddTriangle(double x1, double y1, double x2, double y2, double x3, double y3, QColor color)
{
    DrawCommand cmd;
    cmd.type = Type::Triangle;
    cmd.color = color;
    cmd.x1 = x1; cmd.y1 = y1;
    cmd.x2 = x2; cmd.y2 = y2;
    cmd.x3 = x3; cmd.y3 = y3;
    cmds_.append(cmd);
    update();
}

void CanvasWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.fillRect(rect(), Qt::white);

    for (auto& c : cmds_) {
        p.setPen(QPen(c.color, 2));

        switch (c.type) {
        case Type::Line:
            p.drawLine(c.x1, c.y1, c.x2, c.y2);
            break;
        case Type::Rect:
            p.drawRect(c.x1, c.y1, c.w, c.h);
            break;
        case Type::Ellipse:
            p.drawEllipse(c.x1, c.y1, c.w, c.h);
            break;
        case Type::Triangle:
            QPolygonF poly;
            poly << QPointF(c.x1, c.y1)
                << QPointF(c.x2, c.y2)
                << QPointF(c.x3, c.y3);
            p.drawPolygon(poly);
            break;        
        }
    }
}

void CanvasWidget::Clear() {
    cmds_.clear();
    update();
}