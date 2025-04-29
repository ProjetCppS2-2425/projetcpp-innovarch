#include "rec.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegularExpression>

QString normalize(const QString& input)
{
    QString normalized = input.trimmed().toLower();
    // Remove accents (simple manual replacement)
    normalized.replace(QRegularExpression("[éèêë]"), "e");
    normalized.replace(QRegularExpression("[àâä]"), "a");
    normalized.replace(QRegularExpression("[îï]"), "i");
    normalized.replace(QRegularExpression("[ôö]"), "o");
    normalized.replace(QRegularExpression("[ùûü]"), "u");
    normalized.replace(QRegularExpression("[ç]"), "c");
    return normalized;
}

QList<Product> getRecommendationsForCategory(const QString& category)
{
    QList<Product> allProducts;
    QList<Product> filtered;
    qDebug() << "Exists in resource?" << QFile::exists(":/ressources/Recommandations/produits_recommandations.csv");
    QFile file(":/ressources/Recommandations/produits_recommandations.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Échec de l'ouverture du fichier de recommandations.";
        return allProducts;
    }
    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);
    bool firstLine = true;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (firstLine) { firstLine = false; continue; }
        QStringList fields = line.split(",");
        if (fields.size() < 6) continue;
        Product p;
        p.name = fields[0].trimmed();
        p.category = fields[1].trimmed();
        p.price = fields[2].trimmed();
        p.rating = fields[3].trimmed();
        p.url = fields[4].trimmed().remove('\"');
        p.imagePath = fields[5].trimmed().remove('\"');
        qDebug() << "Checking CSV product:" << p.name << "| category:" << normalize(p.category)
                 << "vs selected:" << normalize(category);
        allProducts.append(p);
        if (normalize(p.category) == normalize(category)){
            qDebug() << "✅ MATCHED:" << p.name;
            filtered.append(p);}
    }

    // Return only filtered if found, otherwise all
    qDebug() << "Filtered count:" << filtered.count();
    return filtered.isEmpty() ? allProducts : filtered;
}
