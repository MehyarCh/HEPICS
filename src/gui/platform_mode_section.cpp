#include "platform_mode_section.h"

Platform_Mode_Section::Platform_Mode_Section(QMainWindow *parent) //
    : QWidget (parent)
{
    // set the platform section
    text_platform = new QLabel(this);
    text_platform->setText("Choose Platform");
    text_platform->setGeometry(100, 45, 325, 45);

    // set check-boxes for each platform
    cbox_cpu = new QCheckBox("CPU", this);
    cbox_cpu->setGeometry(100, 90, 90, 35);
    cbox_gpu = new QCheckBox("GPU", this);
    cbox_gpu->setGeometry(200, 90, 90, 35);
    cbox_fpga = new QCheckBox("FPGA", this);
    cbox_fpga->setGeometry(300, 90, 90, 35);

    // set the operation mode section
    text_operation_mode = new QLabel(this);
    text_operation_mode->setText("Choose Operation Mode");
    text_operation_mode->setGeometry(100, 135, 325, 45);

    // add combo box
    box_operation_mode = new QComboBox(this);
    box_operation_mode->addItem("High Performance");
    box_operation_mode->addItem("Low Power Consumption");
    box_operation_mode->addItem("High Energy Efficiency");
    box_operation_mode->setGeometry(100, 180, 325, 35);
    box_operation_mode->setEditable(false);
    // disable the combo box
    box_operation_mode->setEnabled(false);

    // initialize the number of selected platforms
    counter_platform = 0;

    // initialize the scheduler
    /*MainWindow *m_main_window = parent;
    scheduler = m_main_window->getScheduler();*/

    /* when one of the three check-boxes' states is changed,
     * the combo box for selection of mode should be checked if it should be enabled now
     * and the selection of platforms should be informed to the back-end via scheduler
     */
    connect(cbox_cpu, SIGNAL(stateChanged(int)), this, SLOT(enableModeComboBox(int)));
    connect(cbox_gpu, SIGNAL(stateChanged(int)), this, SLOT(enableModeComboBox(int)));
    connect(cbox_fpga, SIGNAL(stateChanged(int)), this, SLOT(enableModeComboBox(int)));

    // send the choice of mode to the back-end
    //connect(box_operation_mode, SIGNAL(currentIndexChanged()), this, SLOT(setOperationMode()));

}

void Platform_Mode_Section::enableModeComboBox(int state)
{
	// when check-box is checked, state = 2; unchecked state = 0
    counter_platform += (state - 1);

    // only if more than one platform are selected, the mode combo box will be enabled
    if (counter_platform >= 2) {
        box_operation_mode->setEnabled(true);
    } else {
        box_operation_mode->setEnabled(false);
    }

    // send the choice to the scheduler
    if (cbox_cpu->isChecked()) {
        //scheduler->activate(Platform(cpu));
    }

    if (cbox_gpu->isChecked()) {
		//scheduler->activate(Platform(gpu));
    }

    if (cbox_fpga->isChecked()) {
    	//scheduler->activate(Platform(fpga));
    }
}

void Platform_Mode_Section::setOperationMode() {
	// send the choice to the scheduler
	 switch (box_operation_mode->currentIndex()){
		case 0:
			//scheduler.chooseMode(Mode(high_performance));
			break;
		case 1:
			//scheduler.chooseMode(Mode(low_power));
			break;
		case 2:
			//scheduler.chooseMode(Mode(energy_efficient));
			break;
	}
}

