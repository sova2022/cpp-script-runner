#pragma once
#include <QWidget>
#include <QPainter>
#include <QVariant>

Q_DECLARE_METATYPE(QPolygonF)

enum Type {
    Line,
    Rect,
    Ellipse,
    Triangle
};

struct Shape {
    Type type;    
    QColor strokeColor = Qt::black;
    QColor fillColor   = Qt::transparent;
    double strokeWidth = 1.0;
    QVariant data;
};

class CanvasWidget : public QWidget {
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget* parent = nullptr);

    void AddShape(const Shape& shape);
    void Clear();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QVector<Shape> shapes_;
};


class CanvasAPI : public QObject {
    Q_OBJECT
public:
    explicit CanvasAPI(CanvasWidget* canvas, QObject* parent = nullptr);

public slots:
    void clear();
    void line(double x1, double y1, double x2, double y2, const QString& color = "black");
    void rect(double x, double y, double w, double h, const QString& color = "black", const QString& fillColor = "");
    void ellipse(double x, double y, double w, double h, const QString& color = "black", const QString& fillColor = "");
    void triangle(double x1, double y1, double x2, double y2, double x3, double y3, const QString& color = "black", 
        const QString& fillColor = "");
    

private:
    CanvasWidget* canvas_;
};

