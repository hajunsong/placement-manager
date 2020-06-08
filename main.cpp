#include "ControlMain/controlmain.h"
#include "DataControl/datacontrol.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

#include <stdio.h>

using namespace rapidjson;
using namespace std;

static ControlMain *controlMain;
static DataControl *dataControl;

int main()
{
    char readBuffer[65536];
    FILE* fp = fopen("../conf.json", "r");
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Document document;
    document.ParseStream(is);

    dataControl = new DataControl();
    dataControl->DXL_Origin_Axis_1 = document["DXL_Origin_Axis_1"].GetInt();
    dataControl->DXL_Down_Axis_2 = document["DXL_Down_Axis_2"].GetInt();
    dataControl->DXL_Turn_Axis_1 = document["DXL_Turn_Axis_1"].GetInt();
    dataControl->DXL_Up_Axis_2 = document["DXL_Up_Axis_2"].GetInt();
    dataControl->DXL_Block_Axis_2 = document["DXL_Block_Axis_2"].GetInt();
    dataControl->DXL_Block_Axis_1 = document["DXL_Block_Axis_1"].GetInt();
    dataControl->IRR_Release_Pos_1 = document["IRR_Release_Pos"].GetInt();
    dataControl->IRR_Release_Pos_2 = document["IRR_Release_Pos"].GetInt();
    dataControl->IRR_Grip_Pos_1 = document["IRR_Grip_Pos"].GetInt();
    dataControl->IRR_Grip_Pos_2 = document["IRR_Grip_Pos"].GetInt();
    dataControl->IRR_Block_Pos_1 = document["IRR_Block_Pos"].GetInt();
    dataControl->IRR_Block_Pos_2 = document["IRR_Block_Pos"].GetInt();
    dataControl->TCP_ADDRESS = document["TCP_ADDRESS"].GetString();
    dataControl->TCP_ADDRESS.replace(3, 1, ".");
    dataControl->TCP_ADDRESS.replace(7, 1, ".");
    dataControl->TCP_ADDRESS.replace(11, 1, ".");
    dataControl->MAIN_VISION_PORT = document["MAIN_VISION_PORT"].GetInt();
    dataControl->PLACE_VISION_PORT = document["PLACE_VISION_PORT"].GetInt();

    controlMain = new ControlMain(dataControl);
    controlMain->start();

    while(true){
    }

    delete controlMain;
    usleep(10000);

    return 0;
}
