////
//// Created by St on 2019-04-14.
////
//
//#include <stdio.h>
//#include "About.h"
//#include "../UI.h"
//#include "Welcome.h"
//#include "../UI_Utils.h"
//#include "../Menu.h"
//#include "../../data/Serializer.h"
//#include "../../data/DataManager.h"
//#include "Browsing.h"
//#include "View.h"
//#include "../Table.h"
//#include "../../model/Consultation.h"
//
//#define MENU_CNT 7
//
//#define menu 101
//#define form 102
//int tem = 101;
//
//Menu *mMenu;
//
//void updatePrintf();
//void mountingsPrint();
//void sellerPrint();
//void guestPrint();
//void timePrint();
//void menu_inLoop();
//void form_inLoop();
//
//Table *dataTable;
//
//void Browsing_init(){
//    READ_SPEC = true;
//    stringbuf name[] = {
//            STR_BUF("  配 件"),
//            STR_BUF("  供货商"),
//            STR_BUF("  客 户"),
//            STR_BUF("  时 间"),
//    };
//    stringbuf columnName[] = {
//            STR_BUF(""),
//            STR_BUF(""),
//            STR_BUF(""),
//            STR_BUF(""),
//            STR_BUF(""),
//            STR_BUF("")
//    };
//    mMenu = Menu_create(-7, 3, name, MENU_CNT, 0);
//    UI_startScene(SCENE_BROWSING, STR_BUF("首页>浏览记录"));
//    //表格
//    int columnWidth[] = {24, 8, 8, 19,13,9};
//    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
//    Table_setColumnTitle(dataTable, columnName, columnWidth, 6);
//}
//
//void Browsing_inLoop(){
//    Menu_inLoop(mMenu);
//    if (READ_SPEC) {
//        updatePrintf();
////        if(SPEC_KEY == KEY_TAB&&tem == menu){
////            tem = form;
////        }
////        else
////            tem = menu;
////        if(tem == menu){
//                menu_inLoop();
////            }
////        else
//                form_inLoop();
//        if(SPEC_KEY == KEY_ESC){
//            UI_endScene();
//        }
//    }
//}
//
//int  Browsing_render(int line){
//    UI_printMidString(LITERAL("欢迎使用浏览记录!"), line);
//    line += 1;
//    putchar('\n');
//    line += 1;
//    line += Menu_render(mMenu, line);
//    updatePrintf();
//    return line;
//}
//
//void updatePrintf(){
//    string instruction = NULL;
//    switch (mMenu->cur) {
//        case 0:
//            instruction = LITERAL("查询某个配件的购买/进货记录。");
//            break;
//        case 1:
//            instruction = LITERAL("查询某个进货商的进货记录。");
//            break;
//        case 2:
//            instruction = LITERAL("查询某个客户的购买记录。");
//            break;
//        case 3:
//            instruction = LITERAL("查询某段时间的购买/进货记录。");
//            break;
//        default:
//            instruction = LITERAL("");
//    }
//    UI_setFooterUpdate(instruction);
//}
//
//void mountingsPrint(){
//    Menu *MountingMenu;
//    stringbuf mountings_name[] = {
//            STR_BUF("    购买记录"),
//            STR_BUF("    进货记录"),
//    };
//    MountingMenu = Menu_create(-1, 3, mountings_name, MENU_CNT, 0);
//    UI_startScene(SCENE_BROWSING, STR_BUF("首页>浏览记录>查询零配件"));
//    Menu_inLoop(MountingMenu);
//    if (READ_SPEC) {
//        if (SPEC_KEY == KEY_ENTER) {
//            switch (MountingMenu->cur) {
//                case 0:{
//                printf("请输入选择配件种类："
//                           "   (输入序号)\n"
//                           "        1.鼠标\n"
//                           "        2.键盘\n"
//                           "        3.内存\n"
//                           "        4.显卡\n"
//                           "        5.硬盘\n"
//                           "        6.CPU\n"
//                           "        7.屏幕\n");
//                    int number;
//                    scanf("%d",&number);
//                    Database *create = AccessoryIn(number-1);
//                    int i=0,num=0;
//                    ForEach(cur, create){num++;}
//                    stringbuf testData[num][6];
//                    ForEach(cur, create){
//                        PurchaseRecord *now = GetData(PurchaseRecord, cur);
//                        Provider *rec_provider = GetById(Provider,PROVIDER,now->sellerId);
//                        char ch1[20],ch2[20],ch3[20],ch4[20],ch5[20];
//                        sprintf(ch1, "%d", now->id);
//                        testData[i][0] = newString(ch1);
//                        testData[i][1] = rec_provider->name;
//                        sprintf(ch2,"%d",now->amount);
//                        testData[i][2] = newString(ch2);
//                        sprintf(ch3, "%d", now->amount);
//                        testData[i][3] = newString(ch3);
//                        sprintf(ch4, "%f", now->total);
//                        testData[i][4] = newString(ch4);
//                        sprintf(ch5, "%f", now->price);
//                        i++;
//                    };
//                    int columnWidth[] = {24, 8, 8, 19,13,9};
//                    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
//                    stringbuf columnName[] = {
//                            STR_BUF("Id"),
//                            STR_BUF("供货商"),
//                            STR_BUF("数量"),
//                            STR_BUF("总价"),
//                            STR_BUF("单价"),
//                    };
//                    Table_setColumnTitle(dataTable, columnName, columnWidth, 6);
//                    for (int j = 0; j < num; j++)
//                        Table_pushLine(dataTable, testData[j]);
//                    break;
//                }
//                case 1:{
//                    printf("请输入选择配件种类："
//                           "   (输入序号)\n"
//                           "        1.鼠标\n"
//                           "        2.键盘\n"
//                           "        3.内存\n"
//                           "        4.显卡\n"
//                           "        5.硬盘\n"
//                           "        6.CPU\n"
//                           "        7.屏幕\n");
//                    int number;
//                    scanf("%d",&number);
//                    Database *create = AccessoryOut(number-1);
//                    int i=0,num=0;
//                    ForEach(cur, create){num++;}
//                    stringbuf testData[num][6];
//                    ForEach(cur, create){
//                        SellingRecord *now = GetData(SellingRecord, cur);
//                        Guest *rec_guest = GetById(Guest,GUEST,now->guestId);
//                        char ch1[20],ch2[20],ch3[20],ch4[20],ch5[20];
//                        sprintf(ch1, "%d", now->id);
//                        testData[i][0] = newString(ch1);
//                        testData[i][1] = rec_guest->name;
//                        sprintf(ch2,"%d",now->amount);
//                        testData[i][2] = newString(ch2);
//                        sprintf(ch3, "%d", now->amount);
//                        testData[i][3] = newString(ch3);
//                        sprintf(ch4, "%f", now->total);
//                        testData[i][4] = newString(ch4);
//                        sprintf(ch5, "%f", now->price);
//                        i++;
//                    };
//                    int columnWidth[] = {24, 8, 8, 19, 13, 9};
//                    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
//                    stringbuf columnName[] = {
//                            STR_BUF("Id"),
//                            STR_BUF("客户"),
//                            STR_BUF("数量"),
//                            STR_BUF("总价"),
//                            STR_BUF("单价"),
//                    };
//                    Table_setColumnTitle(dataTable, columnName, columnWidth, 6);
//                    for (int j = 0; j < num; j++)
//                        Table_pushLine(dataTable, testData[j]);
//                    break;
//                }
//            }
//        }
//    }
//}
//
//void sellerPrint(){
//    Menu *SellerMenu;
//    int num = 0, i = 0;
//    ForEach(cur,SELLING_RECORD){num++;}
//    stringbuf sellers_name[num];
//    ForEach(cur,SELLING_RECORD){
//        Provider *record = GetData(Provider,cur);
//        sellers_name[i] = record->name;
//        i++;
//    }
//    SellerMenu = Menu_create(-1, 3, sellers_name, MENU_CNT, 0);
//    UI_startScene(SCENE_BROWSING, STR_BUF("查询供货商"));
//    Menu_inLoop(SellerMenu);
//    if (READ_SPEC) {
//        if (SPEC_KEY == KEY_ENTER) {
//            switch (SellerMenu->cur) {
//                case 0: {
//                    printf("请输入选择配件种类："
//                           "   (输入序号)\n"
//                           "        1.鼠标\n"
//                           "        2.键盘\n"
//                           "        3.内存\n"
//                           "        4.显卡\n"
//                           "        5.硬盘\n"
//                           "        6.CPU\n"
//                           "        7.屏幕\n");
//                    int number;
//                    scanf("%d", &number);
//                    Database *create = AccessoryIn(number - 1);
//                    int i = 0, num = 0;
//                    ForEach(cur, create) { num++; }
//                    stringbuf testData[num][6];
//                    ForEach(cur, create) {
//                        PurchaseRecord *now = GetData(PurchaseRecord, cur);
//                        Provider *rec_provider = GetById(Provider, PROVIDER, now->sellerId);
//                        char ch1[20], ch2[20], ch3[20], ch4[20], ch5[20];
//                        sprintf(ch1, "%d", now->id);
//                        testData[i][0] = newString(ch1);
//                        testData[i][1] = rec_provider->name;
//                        sprintf(ch2, "%d", now->amount);
//                        testData[i][2] = newString(ch2);
//                        sprintf(ch3, "%d", now->amount);
//                        testData[i][3] = newString(ch3);
//                        sprintf(ch4, "%f", now->total);
//                        testData[i][4] = newString(ch4);
//                        sprintf(ch5, "%f", now->price);
//                        i++;
//                    };
//                    int columnWidth[] = {24, 8, 8, 19, 13, 9};
//                    dataTable = Table_create(-1, 1, 100, 8, 1, 0);
//                    stringbuf columnName[] = {
//                            STR_BUF("Id"),
//                            STR_BUF("供货商"),
//                            STR_BUF("数量"),
//                            STR_BUF("总价"),
//                            STR_BUF("单价"),
//                    };
//                    Table_setColumnTitle(dataTable, columnName, columnWidth, 6);
//                    for (int j = 0; j < num; j++) Table_pushLine(dataTable, testData[j]);
//                }
//            }
//        }
//    }
//}
//
//void menu_inLoop(){
//    if (SPEC_KEY == KEY_ENTER) {
//        switch (mMenu->cur) {
//            case 0:
//                mountingsPrint();
//                break;
//            case 1:
//                sellerPrint();
//                break;
//            case 2:
//                guestPrint();
//                break;
//            case 3:
//                timePrint();
//                break;
//            case 4:
//                DataManager_save(LITERAL("data"));
//                exit(0);
//            default:
//                break;
//        }
//    }
//}
//
//void form_inLoop(){
//    Table_inLoop(dataTable);
//    UI_setFooterUpdate(Table_getSelection(dataTable));
//}
//
//
