

class Button{
public:
    ofVec2f pos;
    int radius, dragging,toggled, name;
    string names[4];
    void setup(int tpos){
        radius=50;
        dragging=-1;
        pos.x=100+tpos*(2*radius+10);
        name=tpos;
        position(pos);
        names[0]="g";
        names[1]="b";
        names[2]="f";
        names[3]="x";
        toggled=false;
    };
    void draw(){
        //if it is being held under finger
        if(toggled){
            ofSetColor(0);
            
            //ofSetColor((name+0)%200,(name+92)%200,(name+184)%200);
        }else{
            ofSetColor((name*90+0)%255,(name*90+92)%255,(name*90+184)%255);
        }
        ofPushMatrix();
        ofTranslate(pos.x,pos.y);
        ofSetCircleResolution(9);
        ofDrawCircle(0, 0, radius);
        ofSetColor(255);
        fuente.drawString(names[name], 0,50);
        
        ofPopMatrix();
        
        
    }
    void position(int posx,int posy){
        ofVec2f npos;
        npos.x=posx;
        npos.y=posy;
        position(npos);
        
    };
    void position(ofVec2f npos){
        pos=npos;
    };
    bool touch(ofVec2f touch,int n){
        if(ofDist(touch.x,touch.y,pos.x,pos.y)<radius){
            dragging=n;
            return true;
        }else{
            dragging=-1;
            return false;
        }

    };
    void touchup(ofVec2f touch, int n){
        if(dragging==n)
            dragging=-1;
    };
};
