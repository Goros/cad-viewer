/*
 * model.h: Model class. Keeps loaded data
 *
 * This file is a part of the CAD Viewer project
 *
 * Copyright (C) 2012 Artemy Kolesnikov <artemy.kolesnikov@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef MODEL_HEADER
#define MODEL_HEADER

#include <QObject>
#include <QList>

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>
#include <memory>

class Shape {
};

namespace Gui {

class Model : public QObject {
    Q_OBJECT

public:
    typedef boost::shared_ptr<Model> SharedPtr;

    std::string getFileName() const {
        return fileName;
    }

    const std::list<Shape>& getShapes() const {
        return shapeList;
    }

    void removeShape(const Shape& shape);
    void addShape(const Shape& shape);

Q_SIGNALS:
    void shapeAdded(const Shape& shape);
    void shapeRemoved(const Shape& shape);
    void fileNameChanged(QString& newFileName);

public Q_SLOTS:
    void load(QString& fileName);
    void save(QString& fileName);

private:
    std::string fileName;
    std::list<Shape> shapeList;
};

}

#endif // MODEL_HEADER

