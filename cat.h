#ifndef CAT_H
#define CAT_H

#include <iostream>
#include "color.h"
#include "vec2.h"

class cat {
    public:
        cat(int wid = 300, vec2 cen = vec2(150,150), int dep=5, color backC = (color(255, 255, 255))) : width(wid), height(wid), center(cen), depth(dep), backgroundC(backC){
            color black = color(0,0,0);
            verticesHair = {vec2(cen.x()-width/2, cen.y()+width/2),
                                        vec2(cen.x()-0.4*width, cen.y()+0.1*width), 
                                        vec2(cen.x()-0.2*width, cen.y()-0.1*width),
                                        vec2(cen.x()+0.2*width, cen.y()-0.1*width),
                                        vec2(cen.x()+0.4*width, cen.y()+0.1*width),
                                        vec2(cen.x()+width/2, cen.y()+width/2)};
           
            Polygon hair(verticesHair, 1, black);
            hairEyesNose.push_back(hair);

            color faceColor = color(255, 245, 191);
            Rect face1(vec2(cen.x()-0.25*width, cen.y()+0.15*width), vec2(cen.x()+0.25*width, cen.y()+0.4*width), faceColor, 2);
            bangsFace.push_back(face1);

            ellipse face2(vec2(cen.x(), cen.y() + 0.4*width), vec2(0.25*width, 0.1*width), 3, faceColor);
            face.push_back(face2);

            color noseColor = color(255, 194, 179);
        }
        color eval(int x, int y, color backgroundC) {
            float res;
            color inC;
            bool inTrue = false;
            double curDepth = -1.0;
            for (auto obj : face) {
                res = obj.eval(x,y);
                if (res < 0 && obj.getDepth() > curDepth) {
                    inC = obj.getInC();
                    inTrue = true;
                    curDepth = obj.getDepth();
                }
            }
            for (auto obj : hairEyesNose) {
                res = obj.eval(x,y);
                if (res && obj.getDepth() > curDepth) {
                    inC = obj.getInC();
                    inTrue = true;
                    curDepth = obj.getDepth();
                }
            }
            for (auto obj : bangsFace) {
                res = obj.evalIn(x,y);
                if (res && obj.getDepth() > curDepth) {
                    inC = obj.getInC();
                    inTrue = true;
                    curDepth = obj.getDepth();
                }
            }

            if (inTrue) {
                return inC;
            }
            else
                return backgroundC;
        }
    private:
        vector<ellipse> face;
        vector<Polygon> hairEyesNose;
        vector<Rect> bangsFace;
        vector<vec2> verticesHair;

        int depth;
        int width;
        int height;
        vec2 center;
        color inC;
        color backgroundC;


};


#endif