#pragma once
#include <QWidget>
#include <QPainter>
#include <QVariant>

Q_DECLARE_METATYPE(QPolygonF)

enum ShapeType {
    Line,
    Rect,
    Ellipse,
    Triangle
};

struct Shape {
    ShapeType type;
    QColor strokeColor = Qt::black;
    QColor fillColor   = Qt::white;
    double strokeWidth = 1.0;
    QVariant data;
};

/**
 * @brief Холст для рисования фигур.
 *
 * Хранит список фигур (Shape) и отвечает за их отрисовку через QPainter.
 * Поддерживает линии, прямоугольники, эллипсы и треугольники.
 */
class CanvasWidget : public QWidget {
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget* parent = nullptr);

    /**
     * @brief Добавить фигуру на холст.
     * @param shape Фигура для отрисовки.
     */
    void AddShape(const Shape& shape);
    void Clear();

protected:
    /**
     * @brief Обработчик перерисовки.
     *
     * Рендерит все фигуры из списка shapes_.
     */
    void paintEvent(QPaintEvent* event) override;

private:
    QVector<Shape> shapes_;
};

/**
 * @brief API для рисования фигур из Qt Script.
 *
 * Предоставляет набор JS-доступных функций:
 *  - line(x1, y1, x2, y2, strokeColor)
 *  - rect(x, y, w, h, strokeColor, fillColor)
 *  - ellipse(x, y, w, h, strokeColor, fillColor)
 *  - triangle(x1, y1, x2, y2, x3, y3, strokeColor, fillColor)
 *  - clear()
 *
 * CanvasAPI действует как мост между QScriptEngine и CanvasWidget.
 */
class CanvasAPI : public QObject {
    Q_OBJECT
public:
    explicit CanvasAPI(CanvasWidget* canvas, QObject* parent = nullptr);

public slots:
    void clear();

    /**
     * @brief Нарисовать линию.
     * @param x1 Начальная точка X.
     * @param y1 Начальная точка Y.
     * @param x2 Конечная точка X.
     * @param y2 Конечная точка Y.
     * @param color Цвет линии.
     */
    void line(double x1, double y1, double x2, double y2, const QString& color = "black");

    /**
     * @brief Нарисовать прямоугольник.
     * @param x Позиция X.
     * @param y Позиция Y.
     * @param w Ширина.
     * @param h Высота.
     * @param color Цвет рамки.
     * @param fillColor Цвет заливки.
     */
    void rect(double x, double y, double w, double h, const QString& color = "black", const QString& fillColor = "transparent");

    /**
     * @brief Нарисовать эллипс.
     * @param x Позиция X.
     * @param y Позиция Y.
     * @param w Ширина.
     * @param h Высота.
     * @param color Цвет рамки.
     * @param fillColor Цвет заливки.
     */
    void ellipse(double x, double y, double w, double h, const QString& color = "black", const QString& fillColor = "transparent");

    /**
     * @brief Нарисовать треугольник.
     * @param x1 Вершина 1 X.
     * @param y1 Вершина 1 Y.
     * @param x2 Вершина 2 X.
     * @param y2 Вершина 2 Y.
     * @param x3 Вершина 3 X.
     * @param y3 Вершина 3 Y.
     * @param color Цвет линии.
     * @param fillColor Цвет заливки.
     */
    void triangle(double x1, double y1, double x2, double y2, double x3, double y3, const QString& color = "black", 
        const QString& fillColor = "transparent");
    
private:
    CanvasWidget* canvas_;
};

