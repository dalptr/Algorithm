#include <bits/stdc++.h>

using namespace std;

class Polygon {
private:
    int id;

public:
    Polygon() {
        id = 0;
    }

    virtual ~Polygon() = default;

    void setID(int ID) {
        this->id = ID;
    }

    int getID() const {
        return id;
    }

    virtual string toString() = 0;

    virtual void input() = 0;

    virtual double perimeter() = 0;

    virtual double area() = 0;

};


class Rectangle : public Polygon {
private:
    double width;
    double height;

public:

    Rectangle() : Polygon() {
        width = 0;
        height = 0;
    }

    double getWidth() const {
        return this->width;
    }

    double getHeight() const {
        return this->height;
    }

    ~Rectangle() override = default;

    void input() override {
        cout << "Enter Width: ";
        cin >> width;
        cout << "Enter Height: ";
        cin >> height;
    }

    double perimeter() override {
        return 2 * (width + height);
    }

    double area() override {
        return width * height;
    }

    string toString() override {
        return "Rectangle [id=" + to_string(getID()) + ", Width =" + to_string(getWidth()) + ", Height =" +
               to_string(getHeight()) + ", Area=" + to_string(area()) +
               ", Perimeter=" + to_string(perimeter()) + "]";
    }
};

class Circle : public Polygon {
private:
    double radius;

public:
    Circle() : Polygon() {
        radius = 0;
    }

    ~Circle() override = default;

    string toString() override {
        double area = M_PI * radius * radius;
        double perimeter = 2 * M_PI * radius;
        return "Circle    [id=" + to_string(getID()) + ", Radius=" + to_string(radius) + ", Area=" + to_string(area) +
               ", Perimeter=" + to_string(perimeter) + "]";
    }

    void input() override {
        cout << "Enter Radius: ";
        cin >> radius;
    }

    double area() override {
        return M_PI * radius * radius;
    };

    double perimeter() override {
        return 2 * M_PI * radius;
    }

};

void print_selection_list() {
    cout << "+-------------------------------------------------+" << endl;
    cout << "| 1. Add a polygon.                               |" << endl;
    cout << "| 2. Print all polygons.                          |" << endl;
    cout << "| 3. Print out Polygons with Area > 100           |" << endl;
    cout << "| 4. Print out Polygons with Perimeter > 50       |" << endl;
    cout << "| 5. Sort by id (increasing)                      |" << endl;
    cout << "| 6. Exit                                         |" << endl;
    cout << "+-------------------------------------------------+" << endl;
    cout << "Enter your chosen: " << endl;
}

vector<Polygon *> polygons;

bool isExistPolygonID(int id) {
    bool existedID = std::any_of(polygons.begin(), polygons.end(), [&](const auto &polygon) {
        return polygon->getID() == id;
    });
    return existedID;
}

bool increasingID(const Polygon *x, const Polygon *y) {
    return x->getID() < y->getID();
}

int main() {
    int chosen;
    do {
        print_selection_list();
        cin >> chosen;
        switch (chosen) {
            case 1: {
                int enter;
                cout << "Enter Polygon's type (1: Rectangle, 2: Circle): ";
                cin >> enter;
                Polygon *p;
                if (enter == 1) {
                    p = new Rectangle();
                } else if (enter == 2) {
                    p = new Circle();
                } else {
                    cout << "Invalid Polygon's type" << endl;
                    break;
                }
                int id;
                cout << "Enter Polygon's ID: ";
                cin >> id;
                if (isExistPolygonID(id)) {
                    cout << id << " already exists !";
                    break;
                }
                p->setID(id);
                p->input();
                polygons.push_back(p);
                cout << "Added polygon with id = " << id << endl;
                break;
            }

            case 2: {
                cout << "Polygon list: " << endl;
                for (auto const &polygon: polygons) {
                    cout << polygon->toString() << endl;
                }
                break;
            }
            case 3: {
                cout << "All Polygon have Area > 100: " << endl;
                for (auto const &polygon: polygons) {
                    if (polygon->area() > 100) {
                        cout << polygon->toString() << endl;
                    }
                }
                break;
            }

            case 4: {
                cout << "All Polygon have Perimeter > 50: " << endl;
                for (auto const &polygon: polygons) {
                    if (polygon->perimeter() > 50) {
                        cout << polygon->toString() << endl;
                    }
                }
                break;
            }

            case 5: {
                std::sort(polygons.begin(), polygons.end(), increasingID);
                break;
            }

            default:
                break;
        }
    } while (chosen != 6);

    return 0;
}


