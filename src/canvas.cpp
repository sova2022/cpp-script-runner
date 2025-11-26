#include "canvas.h"

#include <QPainter>
#include <QPolygonF>

inline Shape BuildShape(const ShapeType type, const QVariant& data, 
    const QColor& color = Qt::black, const QColor& fillColor = Qt::white) {
    Shape s;

    s.type = type;
    s.data = data;    
    s.strokeColor = color;
    s.fillColor = fillColor;

    return s;
}

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
        case ShapeType::Line:
            p.setBrush(Qt::NoBrush);
            p.drawLine(s.data.toLineF());
            break;
        case ShapeType::Rect:
            p.drawRect(s.data.toRectF());
            break;
        case ShapeType::Ellipse:
            p.drawEllipse(s.data.toRectF());
            break;
        case ShapeType::Triangle:
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
        Shape s = BuildShape(
            ShapeType::Line,
            QVariant::fromValue(QLineF(x1, y1, x2, y2)),
            QColor(color)
        );

        canvas_->AddShape(s);
    }
}

void CanvasAPI::rect(double x, double y, double w, double h, 
    const QString& color, const QString& fillColor) {
    if (canvas_) {
        Shape s = BuildShape(
            ShapeType::Rect,
            QVariant::fromValue(QRectF(x, y, w, h)),
            QColor(color),
            QColor(fillColor)        
        );

        canvas_->AddShape(s);
    }
}

void CanvasAPI::ellipse(double x, double y, double w, double h, 
    const QString& color, const QString& fillColor) {
    if (canvas_) {
        Shape s = BuildShape(
            ShapeType::Ellipse,
            QVariant::fromValue(QRectF(x, y, w, h)),
            QColor(color),
            QColor(fillColor)
        );

        canvas_->AddShape(s);
    }
}

void CanvasAPI::triangle(double x1, double y1, double x2, double y2, double x3, double y3,
    const QString& color, const QString& fillColor) {
    if (canvas_) {        
        QPolygonF poly;
        poly << QPointF(x1, y1)
             << QPointF(x2, y2)
             << QPointF(x3, y3);

        Shape s = BuildShape(
            ShapeType::Triangle,
            QVariant::fromValue(poly),
            QColor(color),
            QColor(fillColor)
        );

        canvas_->AddShape(s);
    }
}
