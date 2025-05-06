#ifndef REC_H
#define REC_H
#include <QString>
#include <QList>

struct Product {
    QString name;
    QString category;
    QString price;
    QString rating;
    QString url;
    QString imagePath;
};

QList<Product> getRecommendationsForCategory(const QString& category);
QString normalize(const QString& input);

#endif // REC_H
