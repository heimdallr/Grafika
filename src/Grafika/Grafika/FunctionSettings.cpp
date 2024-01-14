#include "FunctionSettings.h"

#include "ui_FunctionSettings.h"

namespace
{
    void SetupAutoMode(QCheckBox * checkBox, QWidget * widget)
    {
        QObject::connect(checkBox, &QCheckBox::stateChanged, widget, [=](int state) {widget->setEnabled(state == Qt::Unchecked); });
    }
}

int FunctionSettings::nextNumber = 0;

FunctionSettings::FunctionSettings(QWidget * parent)
    : QDialog(parent)
    , ui(std::make_unique <Ui::FunctionSettings>())
{
    ui->setupUi(this);
    ui->lineEditTitle->setText(tr("Function %1").arg(++nextNumber));
    connect(ui->lineEditTitle, &QLineEdit::textChanged, this, &FunctionSettings::titleChanged);
    connect(ui->buttonRemove, &QAbstractButton::clicked, this, &QObject::deleteLater);
    connect(ui->doubleSpinBoxXMax, &QDoubleSpinBox::valueChanged, ui->doubleSpinBoxXMin, &QDoubleSpinBox::setMaximum);
    connect(ui->doubleSpinBoxXMin, &QDoubleSpinBox::valueChanged, ui->doubleSpinBoxXMax, &QDoubleSpinBox::setMinimum);
    SetupAutoMode(ui->checkBoxXMaxAuto, ui-> doubleSpinBoxXMax);
    SetupAutoMode(ui->checkBoxXMinAuto, ui->doubleSpinBoxXMin);
    SetupAutoMode(ui->checkBoxDeltaXAuto, ui->doubleSpinBoxDeltaX);
    FillStyleCombobox();
}

FunctionSettings::~FunctionSettings() = default;

QString FunctionSettings::GetTitle() const
{
    return ui->lineEditTitle->text();
}

QPolygonF FunctionSettings::GetPoints() const
{
    QPolygonF points;
    for (auto x = ui->doubleSpinBoxXMin->value(); x <= ui->doubleSpinBoxXMax->value(); x += ui->doubleSpinBoxDeltaX->value())
        points << QPointF(x, F(x));
    return points;
}

double FunctionSettings::F(double x) const
{
    return x;
}

void FunctionSettings::FillStyleCombobox()
{
    ui->comboBoxStyle->addItem(tr("Solid line"), static_cast<int>(Qt::SolidLine));
    ui->comboBoxStyle->addItem(tr("Dash line"), static_cast<int>(Qt::DashLine));
    ui->comboBoxStyle->addItem(tr("Dot line"), static_cast<int>(Qt::DotLine));
    ui->comboBoxStyle->addItem(tr("Dash dot line"), static_cast<int>(Qt::DashDotLine));
    ui->comboBoxStyle->addItem(tr("Dash dot dot line"), static_cast<int>(Qt::DashDotDotLine));
    ui->comboBoxStyle->setCurrentIndex(0);
}
