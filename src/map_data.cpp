#ifndef _MAP_DATA_H
#define _MAP_DATA_H

#include "food.h"
#include <vector>

std::vector<Food> map_data_get_food_vector()
{
  Food myFood1(10,50);
  Food myFood2(10,90);
  Food myFood3(10,130);
  Food myFood4(10,170);
  Food myFood5(10,210);
  Food myFood6(10,250);
  Food myFood7(10,290);
  Food myFood8(10,330);
  Food myFood9(10,370);
  Food myFood10(10,410);
  
  Food myFood11(50,10);
  Food myFood12(50,250);
  Food myFood13(50,450);  
  Food myFood14(90,10);
  Food myFood15(90,170);
  Food myFood16(90,210);
  Food myFood17(90,250);
  Food myFood18(90,290);
  Food myFood19(90,330);

  Food myFood20(90,370);
  Food myFood21(90,410);
  Food myFood22(90,450);  
  Food myFood23(130,10);
  Food myFood24(130,170);
  Food myFood25(130,450);
  Food myFood26(170,10);
  Food myFood27(170,50);
  Food myFood28(170,90);
  Food myFood29(170,130);

  Food myFood30(170,170);
  Food myFood31(170,210);
  Food myFood32(170,250);
  Food myFood33(170,290);
  Food myFood34(170,330);
  Food myFood35(170,370);
  Food myFood36(170,410);
  Food myFood37(170,450);
  Food myFood38(210,10);
  Food myFood39(210,90);

  Food myFood40(210,250);
  Food myFood41(210,450);
  Food myFood42(250,10);
  Food myFood43(250,90);
  Food myFood44(250,250);
  Food myFood45(250,290);
  Food myFood46(250,330);
  Food myFood47(250,370);
  Food myFood48(250,410);
  Food myFood49(250,450);
  
  Food myFood50(290,10);
  Food myFood51(290,90);
  Food myFood52(290,250);
  Food myFood53(290,330);
  Food myFood54(290,450);  
  Food myFood55(330,10);
  Food myFood56(330,250);
  Food myFood57(330,330);
  Food myFood58(330,450);  
  Food myFood59(370,10);
  
  Food myFood60(370,50);
  Food myFood61(370,90);
  Food myFood62(370,130);
  Food myFood63(370,170);
  Food myFood64(370,210);
  Food myFood65(370,250);
  Food myFood66(370,450);
  Food myFood67(410,10);
  Food myFood68(410,90);
  Food myFood69(410,170);

  Food myFood70(410,250);
  Food myFood71(410,290);
  Food myFood72(410,330);
  Food myFood73(410,370);
  Food myFood74(410,410);
  Food myFood75(410,450);

  Food myFood76(450,10);
  Food myFood77(450,90);
  Food myFood78(450,170);
  Food myFood79(450,450);

  Food myFood80(490,10);
  Food myFood81(490,90);
  Food myFood82(490,170);
  Food myFood83(490,250);
  Food myFood84(490,290);
  Food myFood85(490,330);
  Food myFood86(490,370);
  Food myFood87(490,410);
  Food myFood88(490,450);
  Food myFood89(530,10);

  Food myFood90(530,90);
  Food myFood91(530,170);
  Food myFood92(530,290);
  Food myFood93(530,450);
  Food myFood94(570,10);
  Food myFood95(570,90);
  Food myFood96(570,170);
  Food myFood97(570,250);
  Food myFood98(570,290);
  Food myFood99(570,330);

  Food myFood100(570,450);
  Food myFood101(610,10);
  Food myFood102(610,50);
  Food myFood103(610,90);
  Food myFood104(610,130);
  Food myFood105(610,170);
  Food myFood106(610,210);
  Food myFood107(610,250);
  Food myFood108(610,330);
  Food myFood109(610,370);
  Food myFood110(610,410);

  return {myFood1,myFood2,myFood3,myFood4,myFood5,myFood6,myFood7,myFood8,myFood9,myFood10,
      myFood11,myFood12,myFood13,myFood14,myFood15,myFood16,myFood17,myFood18,myFood19,myFood20,
      myFood21,myFood22,myFood23,myFood24,myFood25,myFood26,myFood27,myFood28,myFood29,myFood30,
      myFood31,myFood32,myFood33,myFood34,myFood35,myFood36,myFood37,myFood38,myFood39,myFood40,
      myFood41,myFood42,myFood43,myFood44,myFood45,myFood46,myFood47,myFood48,myFood49,myFood50,
      myFood51,myFood52,myFood53,myFood54,myFood55,myFood56,myFood57,myFood58,myFood59,myFood60,
      myFood61,myFood62,myFood63,myFood64,myFood65,myFood66,myFood67,myFood68,myFood69,myFood70,
      myFood71,myFood72,myFood73,myFood74,myFood75,myFood76,myFood77,myFood78,myFood79,myFood80,
      myFood81,myFood82,myFood83,myFood84,myFood85,myFood86,myFood87,myFood88,myFood89,myFood90,
      myFood91,myFood92,myFood93,myFood94,myFood95,myFood96,myFood97,myFood98,myFood99,myFood100,
      myFood101,myFood102,myFood103,myFood104,myFood105,myFood106,myFood107,myFood108,myFood109,myFood110};
}

std::vector<Special_Food> map_data_get_special_food_vector()
{
  Special_Food mySpecial_Food1(10,10);
  Special_Food mySpecial_Food2(10,450);
  Special_Food mySpecial_Food3(610 ,10);
  Special_Food mySpecial_Food4(570,410);
  Special_Food mySpecial_Food(370,0);

  return {mySpecial_Food1,mySpecial_Food2,mySpecial_Food3,mySpecial_Food4};
}

std::vector<SDL_Rect> map_data_get_maze_vector()
{
  SDL_Rect wall1 = {40,40,40,200};
  SDL_Rect wall2 = {80,40,80,40};
  SDL_Rect wall3 = {80,120,40,40};
  SDL_Rect wall4 = {120,40,40,120};
  SDL_Rect wall5 = {200,40,160,40};
  SDL_Rect wall6 = {320,80,40,40};
  SDL_Rect wall7 = {200,120,160,40};
  SDL_Rect wall8 = {200,160,40,40};
  SDL_Rect wall9 = {200,200,160,40};
  SDL_Rect wall10 = {400,40,200,40};
  SDL_Rect wall11 = {400,120,200,40};
  SDL_Rect wall12 = {40,280,40,160};
  SDL_Rect wall13 = {120,200,40,240};
  SDL_Rect wall14 = {200,280,40,160};
  SDL_Rect wall15 = {280,280,120,40};
  SDL_Rect wall16 = {360,320,40,40};
  SDL_Rect wall17 = {280,360,120,80};
  SDL_Rect wall18 = {400,200,200,40};
  SDL_Rect wall19 = {440,240,40,200};
  SDL_Rect wall20 = {520,240,40,40};
  SDL_Rect wall21 = {600,280,40,40};
  SDL_Rect wall22 = {520,320,40,120};
  SDL_Rect wall23 = {560,360,40,40};
  SDL_Rect wall24 = {600,440,40,40};

  return {wall1,wall2,wall3,wall4,wall5,wall6,wall7,wall8,wall9,wall10,
      wall11,wall12,wall13,wall14,wall15,wall16,wall17,wall18,wall19,
      wall20,wall21,wall22,wall23,wall24};
}

std::vector<SDL_Rect> map_data_get_checkpoint_vector()
{
  SDL_Rect checkpoint1 = {15,260,5,5};
  SDL_Rect checkpoint2 = {175,15,5,5};
  SDL_Rect checkpoint3 = {375,15,5,5};
  SDL_Rect checkpoint4 = {375,100,5,5};
  SDL_Rect checkpoint5 = {260,260,5,5};
  SDL_Rect checkpoint6 = {260,500,5,5};
  SDL_Rect checkpoint7 ={175,100,5,5};
  SDL_Rect checkpoint8={175,260,5,5};
  SDL_Rect checkpoint9={375,260,5,5};
  SDL_Rect checkpoint10={375,175,5,5};
  SDL_Rect checkpoint11={175,460,5,5};
  SDL_Rect checkpoint12={260,460,5,5};
  SDL_Rect checkpoint13={415,460,5,5};
  SDL_Rect checkpoint14={500,460,5,5};
  SDL_Rect checkpoint15={500,300,5,5};
  SDL_Rect checkpoint16={570,300,5,5};
  SDL_Rect checkpoint17={620,175,5,5};
  SDL_Rect checkpoint18={620,100,5,5};
  SDL_Rect checkpoint19={620,15,5,5};
  SDL_Rect checkpoint20={175,175,5,5};
  SDL_Rect checkpoint21={100,260,5,5};
  SDL_Rect checkpoint22={100,460,5,5};

  return {checkpoint1,checkpoint2,checkpoint3,checkpoint4,checkpoint5,
      checkpoint6,checkpoint7,checkpoint8,checkpoint9,checkpoint10,
      checkpoint11,checkpoint12,checkpoint13,checkpoint14,checkpoint15,
      checkpoint16,checkpoint17,checkpoint18,checkpoint19,checkpoint20,
      checkpoint21,checkpoint22};
}


#endif // _MAP_DATA_H
