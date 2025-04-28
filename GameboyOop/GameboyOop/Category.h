#ifndef CATEGORY_H
#define CATEGORY_H

class Category {
private:
    char name[50];

public:
    Category() { }
    Category(const char* name) {
        // Copy name into `this->name`
        int i = 0;
        while (name[i] != '\0' && i < 49) {
            this->name[i] = name[i];
            i++;
        }
        this->name[i] = '\0';
    }

    const char* getName() const {
        return name;
    }
};

#endif
