#ifndef TEAMSCORE_H
#define TEAMSCORE_H

#include <QObject>
#include <QList>

class TeamScore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString teamName READ getTeamName WRITE setTeamName NOTIFY teamNameChanged FINAL)

    Q_PROPERTY(int wins READ getWins WRITE setWins NOTIFY winsChanged FINAL)
    Q_PROPERTY(int gainedMatchPoints READ getGainedMatchPoints WRITE setGainedMatchPoints NOTIFY gainedMatchPointsChanged FINAL)
    Q_PROPERTY(int competitionsWon READ getCompetitionsWon WRITE setCompetitionsWon NOTIFY competitionsWonChanged FINAL)
    Q_PROPERTY(int wonTriples READ getWonTriples WRITE setWonTriples NOTIFY wonTriplesChanged FINAL)
    Q_PROPERTY(int wonDoubles READ getWonDoubles WRITE setWonDoubles NOTIFY wonDoublesChanged FINAL)
    Q_PROPERTY(int wonSingles READ getWonSingles WRITE setWonSingles NOTIFY wonSinglesChanged FINAL)
    Q_PROPERTY(int gainedSmallPointsInTriples READ getGainedSmallPointsInTriples WRITE setGainedSmallPointsInTriples NOTIFY gainedSmallPointsInTriplesChanged FINAL)
    Q_PROPERTY(int lostSmallPointsInTriples READ getLostSmallPointsInTriples WRITE setLostSmallPointsInTriples NOTIFY lostSmallPointsInTriplesChanged FINAL)
    Q_PROPERTY(int diffSmallPointsInTriples READ getDiffSmallPointsInTriples WRITE setDiffSmallPointsInTriples NOTIFY diffSmallPointsInTriplesChanged FINAL)
    Q_PROPERTY(int gainedSmallPointsInDoubles READ getGainedSmallPointsInDoubles WRITE setGainedSmallPointsInDoubles NOTIFY gainedSmallPointsInDoublesChanged FINAL)
    Q_PROPERTY(int lostSmallPointsInDoubles READ getLostSmallPointsInDoubles WRITE setLostSmallPointsInDoubles NOTIFY lostSmallPointsInDoublesChanged FINAL)
    Q_PROPERTY(int diffSmallPointsInDoubles READ getDiffSmallPointsInDoubles WRITE setDiffSmallPointsInDoubles NOTIFY diffSmallPointsInDoublesChanged FINAL)
    Q_PROPERTY(int gainedSmallPointsInSingles READ getGainedSmallPointsInSingles WRITE setGainedSmallPointsInSingles NOTIFY gainedSmallPointsInSinglesChanged FINAL)
    Q_PROPERTY(int lostSmallPointsInSingles READ getLostSmallPointsInSingles WRITE setLostSmallPointsInSingles NOTIFY lostSmallPointsInSinglesChanged FINAL)
    Q_PROPERTY(int diffSmallPointsInSingles READ getDiffSmallPointsInSingles WRITE setDiffSmallPointsInSingles NOTIFY diffSmallPointsInSinglesChanged FINAL)

    Q_PROPERTY(QList<int> allParametersList READ getAllParametersList NOTIFY parametersChanged FINAL)


public:
    explicit TeamScore(QObject *parent = nullptr);

    /// GETTERS
    QString getTeamName() const;

    int getWins() const;
    int getGainedMatchPoints() const;
    int getCompetitionsWon() const;
    int getWonTriples() const;
    int getWonDoubles() const;
    int getWonSingles() const;
    int getGainedSmallPointsInTriples() const;
    int getLostSmallPointsInTriples() const;
    int getDiffSmallPointsInTriples() const;
    int getGainedSmallPointsInDoubles() const;
    int getLostSmallPointsInDoubles() const;
    int getDiffSmallPointsInDoubles() const;
    int getGainedSmallPointsInSingles() const;
    int getLostSmallPointsInSingles() const;
    int getDiffSmallPointsInSingles() const;

    QList<int> getAllParametersList() const;


    /// SETTERS
    void setTeamName(const QString &teamName);

    void setWins(int wins);
    void setGainedMatchPoints(int gainedMatchPoints);
    void setCompetitionsWon(int competitionsWon);
    void setWonTriples(int wonTriples);
    void setWonDoubles(int wonDoubles);
    void setWonSingles(int wonSingles);
    void setGainedSmallPointsInTriples(int gainedSmallPointsInTriples);
    void setLostSmallPointsInTriples(int lostSmallPointsInTriples);
    void setDiffSmallPointsInTriples(int diffSmallPointsInTriples);
    void setGainedSmallPointsInDoubles(int gainedSmallPointsInDoubles);
    void setLostSmallPointsInDoubles(int lostSmallPointsInDoubles);
    void setDiffSmallPointsInDoubles(int diffSmallPointsInDoubles);
    void setGainedSmallPointsInSingles(int gainedSmallPointsInSingles);
    void setLostSmallPointsInSingles(int lostSmallPointsInSingles);
    void setDiffSmallPointsInSingles(int diffSmallPointsInSingles);



signals:
    void teamNameChanged();

    void winsChanged();
    void gainedMatchPointsChanged();
    void competitionsWonChanged();
    void wonTriplesChanged();
    void wonDoublesChanged();
    void wonSinglesChanged();
    void gainedSmallPointsInTriplesChanged();
    void lostSmallPointsInTriplesChanged();
    void diffSmallPointsInTriplesChanged();
    void gainedSmallPointsInDoublesChanged();
    void lostSmallPointsInDoublesChanged();
    void diffSmallPointsInDoublesChanged();
    void gainedSmallPointsInSinglesChanged();
    void lostSmallPointsInSinglesChanged();
    void diffSmallPointsInSinglesChanged();

    void parametersChanged();

private:
    QString m_teamName;

    /// liczba zwycięstw (LZ)
    int m_wins;

    /// liczba zdobytych punktów w meczach (LZP) (5T+3D+2S)
    int m_gainedMatchPoints;

    /// liczba wygranych konkurencji (LWK) (T+D+S)
    int m_competitionsWon;

    /// liczba wygranych tripletów (T)
    int m_wonTriples;
    /// liczba wygranych dubletów (D)
    int m_wonDoubles;
    /// liczba wygranych singli (S)
    int m_wonSingles;


    struct SmallPoints{
        /// małe punkty zdobyte w [_] (PZ_)
        int gained;
        /// małe punkty stracone w [_] (PS_)
        int lost;
        /// różnica małych punktów zdobytych w [_] (R_)
        int diff;
    };

    /// (PZT), (PST), (RT)
    SmallPoints m_smallPointsTriples;
    /// (PZD), (PSD), (RD)
    SmallPoints m_smallPointsDoubles;
    /// (PZS), (PSS), (RS)
    SmallPoints m_smallPointsSingles;

    /// all parameters combained in to one vector
    const QList<const int *> m_allParametersList;

};

typedef QList<TeamScore*> TeamPtrScores;

#endif // TEAMSCORE_H
