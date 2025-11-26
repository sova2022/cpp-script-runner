#include "canvas.h"

#include <QPainter>
#include <QPolygonF>

// CanvasWidget

CanvasWidget::CanvasWidget(QWidget* parent) 
    : QWidget(parent) {
    setMinimumSize(400, 400);
}

void CanvasWidget::AddShape(const Shape& shape) {
    shapes_.append(shape);
    update();
}

void CanvasWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.fillRect(rect(), Qt::white);

    for (auto& s : shapes_) {
        p.setPen(QPen(s.strokeColor, s.strokeWidth));

        QBrush brush(s.fillColor);
        p.setBrush(brush);

        switch (s.type) {
        case Type::Line:
            p.setBrush(Qt::NoBrush);
            p.drawLine(s.data.toLineF());
            break;
        case Type::Rect:
            p.drawRect(s.data.toRectF());
            break;
        case Type::Ellipse:
            p.drawEllipse(s.data.toRectF());
            break;
        case Type::Triangle:
            p.drawPolygon(s.data.value<QPolygonF>());
            break;        
        }
    }
}

void CanvasWidget::Clear() {
    shapes_.clear();
    update();
}

// CanvasAPI

CanvasAPI::CanvasAPI(CanvasWidget* canvas, QObject* parent)
    : QObject(parent), canvas_(canvas) {
}

void CanvasAPI::clear() {
    if (canvas_) {
        canvas_->Clear();
    }
}

void CanvasAPI::line(double x1, double y1, double x2, double y2, const QString& color) {
    if (canvas_) {
        Shape s;
        s.data = QLineF(x1, y1, x2, y2);
        s.strokeColor = QColor(color);
        s.type = Type::Line;
        canvas_->AddShape(s);
    }
}

void CanvasAPI::rect(double x, double y, double w, double h, 
    const QString& color, const QString& fillColor) {
    if (canvas_) {
        Shape s;
        s.data = QRectF(x, y, w, h);
        s.strokeColor = QColor(color);
        s.fillColor = QColor(fillColor);
        s.type = Type::Rect;
        canvas_->AddShape(s);
    }
}

void CanvasAPI::ellipse(double x, double y, double w, double h, 
    const QString& color, const QString& fillColor) {
    if (canvas_) {
        Shape s;
        s.data = QRectF(x, y, w, h);
        s.strokeColor = QColor(color);
        s.fillColor = QColor(fillColor);
        s.type = Type::Ellipse;
        canvas_->AddShape(s);
    }
}

void CanvasAPI::triangle(double x1, double y1, double x2, double y2, double x3, double y3,
    const QString& color, const QString& fillColor) {
    if (canvas_) {
        Shape s;
        QPolygonF poly;
        poly << QPointF(x1, y1)
             << QPointF(x2, y2)
             << QPointF(x3, y3);

        s.data = poly;
        s.strokeColor = QColor(color);
        s.fillColor = QColor(fillColor);
        s.type = Type::Triangle;
        canvas_->AddShape(s);
    }
}
