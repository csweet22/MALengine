#include "FakeBoid.hpp"

float random(float LO, float HI){
    return LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
}

FakeBoid::FakeBoid(
    std::string _name,
    glm::vec3 _position, 
    glm::vec3 _rotation,
    glm::vec3 _scale){
        DEBUG_INFO("Created FakeBoid");
        this->name = _name;
        this->position =  glm::vec3(random(-1.0, 1.0), random(-1.0, 1.0), random(-1.0, 1.0));
        startPos = position;
        this->rotation = _rotation;
        this->scale = _scale;
        float distance = 1.0;
        this->velocity = glm::normalize(glm::vec3(random(-1.0, 1.0), random(-1.0, 1.0), random(-1.0, 1.0)));     
        this->goal = glm::vec3(random(-distance, distance), random(-distance, distance), random(-distance,distance));
        this->goal2 = glm::vec3(random(-distance, distance), random(-distance, distance), random(-distance,distance));
        this->amount = random(0.0, 1.0);
        color = glm::vec3(random(0.0, 1.0), random(0.0, 1.0), random(0.0, 1.0));
}

FakeBoid::~FakeBoid(){
    DEBUG_INFO("Destroyed FakeBoid");
}

void FakeBoid::Update(){
    
    // DEBUG_INFO(amount);
    amount += 0.003;

    // (1 − t)^2 + 2(1 − t)t + t^2

    position = glm::vec3( pow(1.0 - amount, 2) ) * startPos + glm::vec3( (1.0 - amount) * amount) * goal2 + glm::vec3(pow(amount, 2)) * goal;


    if ( amount > 1.0 ){
        startPos = goal;
        goal = goal2;


        goal2 = glm::vec3(random(-2.0, 2.0), random(-2.0, 2.0), random(-2.0, 2.0));
        amount = 0.0;
    }

    this->Draw();
}


void FakeBoid::Draw() {

    glm::vec3 point1 = glm::vec3( -1 * scale.x, -1 * scale.y, 0);
    glm::vec3 point2 = glm::vec3( scale.x, -1 * scale.y, 0);
    glm::vec3 point3 = glm::vec3(0, scale.y, 0);

    float lerpAmount = 0.01;

    look = look * glm::mat4(1.0 - lerpAmount) + glm::mat4(lerpAmount) * glm::lookAt( glm::vec3(0), goal - position, position);

    point1 = look * glm::vec4(point1.x, point1.y, point1.z, 1.0);
    point2 = look * glm::vec4(point2.x, point2.y, point2.z, 1.0);
    point3 = look * glm::vec4(point3.x, point3.y, point3.z, 1.0);


    glColor4f(color.x / 1.5, color.y / 1.5, color.z / 1.5, 1.0);
    glBegin(GL_LINES);
        glVertex3f(position.x + point1.x, position.y + point1.y, position.z + point1.z);
        glVertex3f(position.x + point2.x, position.y + point2.y, position.z + point2.z);
        glVertex3f(position.x + point3.x, position.y + point3.y, position.z + point3.z);
        glVertex3f(position.x + point1.x, position.y + point1.y, position.z + point1.z);
        glVertex3f(position.x + point3.x, position.y + point3.y, position.z + point3.z);
        glVertex3f(position.x + point2.x, position.y + point2.y, position.z + point2.z);
        
        // glColor4f(0.0, 0.0, 1.0, 0.05);
        // glVertex3f(position.x, position.y, position.z);
        // glVertex3f(goal.x, goal.y, goal.z);

        // glVertex3f(goal.x, goal.y, goal.z);
        // glVertex3f(goal2.x, goal2.y, goal2.z);
    
    glEnd();

    glBlendFunc(GL_ONE, GL_ONE);
    glColor4f(color.x, color.y, color.z, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex3f(position.x + point1.x, position.y + point1.y, position.z + point1.z);
        glVertex3f(position.x + point2.x, position.y + point2.y, position.z + point2.z);
        glVertex3f(position.x + point3.x, position.y + point3.y, position.z + point3.z);
    glEnd();

    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

std::string FakeBoid::ToString(){
    return std::string("(") + std::to_string(this->guid) + " / " + (this->name) +"): " +  glm::to_string(this->position); 
}