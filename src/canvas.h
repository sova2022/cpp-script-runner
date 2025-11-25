#pragma once
#include <QWidget>
#include <QPainter>

enum Type {
    Line,
    Rect,
    Ellipse,
    Triangle
};

struct DrawCommand {
    Type type;
    QColor color;
    double x1, y1, x2, y2, x3, y3, w, h;
};

class CanvasWidget : public QWidget {
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget* parent = nullptr);
    
    void AddLine(double x1, double y1, double x2, double y2, QColor color);
    void AddRect(double x, double y, double w, double h, QColor color);
    void AddEllipse(double x, double y, double w, double h, QColor color);
    void AddTriangle(double x1, double y1, double x2, double y2, double x3, double y3, QColor color);
    void Clear();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QVector<DrawCommand> cmds_;
};


class CanvasAPI : public QObject {
    Q_OBJECT
public:
    explicit CanvasAPI(CanvasWidget* canvas, QObject* parent = nullptr);

public slots:
    void line(double x1, double y1, double x2, double y2, const QString& color = "black");
    void rect(double x, double y, double w, double h, const QString& color = "black");
    void ellipse(double x, double y, double w, double h, const QString& color = "black");
    void triangle(double x1, double y1, double x2, double y2, double x3, double y3, const QString& color = "black");
    void clear();

private:
    CanvasWidget* canvas_;
};

