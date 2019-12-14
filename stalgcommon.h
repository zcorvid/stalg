#ifndef __ST_ALG_COMMON_H__
#define __ST_ALG_COMMON_H__

/* stalg common
 * last change: 13.03.2017
 *
 * Средства общего назначения.
 *
 */

namespace stalg
{
    const double COMPARISON_THRESHOLD = 1e-8;

    template<typename T>
    void swap(T& x, T& y)
    {
        T tmp = x;
        x = y;
        y = tmp;
    }

    /*
    template<class InputIterator>
    void reverse(InputIterator first, InputIterator last)
    {
        for (; first != last; ++first, --last)
        {
            //
        }
    }
    */

    struct CarInfo
    {
        float lat1, lon1;      //Для нарушителя - координаты зада; Для жертвы - координаты на первом кадре
                                // Для GetVictim2 координаты центра машины, lat2, lon2 не заполняются
        float lat2, lon2;
        float tBeg;            //Время начала остановки для нарушителя / Время 1-го(начального) кадра жертвы
        float tEnd;            //Время конца остановки для нарушителя / Время 2-го(нконечного) кадра жертвы
        float a, b, c;         //Коэф-ты уравнения прямой
        float vLat, vLon;      //Расчётная скорость по 2-м кадрам
        float radius;          // Радиус машины
        void MakeLine()         //Вычисляем уравнение прямой
        {
            a = lon1 - lon2;
            b = -(lat1 - lat2);
            c = lat1 * lon2 - lat2 * lon1;
        }
        float GetVal(float x, float y) const
        {
            return a * x + b * y + c;               //Подставляем точку в уравнение прямой
        }
        void MakeVelocity()
        {
            vLat = (lat2 - lat1) / (tEnd - tBeg);                   // Скорость по широте
            vLon = (lon2 - lon1) / (tEnd - tBeg);                   // Скорость по долготе
        }
    };

    inline bool qp_f(const QPair<float, int> &p1, const QPair<float, int> &p2)
    {
        return p1.first < p2.first;
    }

    inline int GetVictim(CarInfo &car0, QVector<CarInfo> &pot_vict)
    {
        QVector<QPair<float, int> > mp;
        car0.MakeLine();
        for (int i = 0; i < pot_vict.size(); ++i)
        {
            pot_vict[i].MakeVelocity();
//            float t = -car0.GetVal(pot_vict[i].lat1, pot_vict[i].lon1) / car0.a * pot_vict[i].vLat + car0.b * pot_vict[i].vLon;
            float t = -car0.GetVal(pot_vict[i].lat1, pot_vict[i].lon1);                    // Получение точки пересечения прямых (числитель)
            t /= car0.a * pot_vict[i].vLat + car0.b * pot_vict[i].vLon;                     // Получение точки пересечения прямых (чзнаменатель)
            if (t > car0.tBeg && t < car0.tEnd)
            {
                float d = t * std::sqrt(pot_vict[i].vLat * pot_vict[i].vLat + pot_vict[i].vLon * pot_vict[i].vLon);
                mp.append(QPair<float, int>(d, i));
            }
        }
        qSort(mp.begin(), mp.end(), qp_f);
        if (mp.empty())
        {
            return -1;
        }
        else
        {
            return mp[0].second;
        }
    }

    inline int GetVictim2(CarInfo &car0, QVector<CarInfo> &pot_vict)
    {
        QVector<QPair<float, int> > mp;
        for (int i = 0; i < pot_vict.size(); ++i)
        {
            pot_vict[i].MakeVelocity();
            pot_vict[i].MakeLine();
            float a = pot_vict[i].a;
            float b = pot_vict[i].b;
            float c = pot_vict[i].c;
            float dista = fabs(a * car0.lat1 + b * car0.lon1 + c);
            dista /= std::sqrt((a*a + b*b));
            float dl1 = car0.lat1 - pot_vict[i].lat1;
            float dl2 = car0.lon1 - pot_vict[i].lon1;
            if (dista < car0.radius)
            {
                float dista2 = std::sqrt((dl1 * dl1 + dl2 * dl2) - dista*dista);
                float velo = std::sqrt(pot_vict[i].vLat * pot_vict[i].vLat + pot_vict[i].vLon * pot_vict[i].vLon);
                float t = dista2 / velo;
                if (t > car0.tBeg && t < car0.tEnd)
                {
                    //                float d = t * std::sqrt(pot_vict[i].vLat * pot_vict[i].vLat + pot_vict[i].vLon * pot_vict[i].vLon);
                    float d = dista;
                    mp.append(QPair<float, int>(d, i));
                }
            }
        }
        qSort(mp.begin(), mp.end(), qp_f);
        if (mp.empty())
        {
            return -1;
        }
        else
        {
            return mp[0].second;
        }
    }

    //!!!!!!! Функция не отлажена
    //! camGeo  - геокоординаты комплекса в радианах
    //! camBear - курсовой угол комплекса в радианах
    //! carGeo  - геокоординаты объекта   в радианах
    //! dt      - DistTable
    inline QPoint GetPixPosition(  const QPointF &camGeo, float camBear, const QPointF &carGeo, const DistTable &dt)
    {
        // Создадаим считалку с параметрами эллипсоида Красовского
        stalg::Vincenty vinc(stalg::EarthEllipsoid::KrasovskyEllipsoid());
        float dist  = vinc.calculate_distance(camGeo.x(), camGeo.y(), carGeo.x(), carGeo.y());
        float azi   = atan2(camGeo.y() - carGeo.y(), camGeo.x() - carGeo.x());
        float angel = azi - camBear;
        float xm = dist * sin(angel);
        float ym = dist * cos(angel);
        float foca    = dt.focalLength;
        float camH    = dt.cameraH    ;
        float camBeta = dt.betaCnt    ;
        QPointF po = stalg::getCamPoint(xm, ym, foca / 1000., camH, camBeta);
//        float  X  = (p.x()*1000. + 0.5*sensorW) * width  / sensorW;
//        float  Y  = (p.y()*1000. + 0.5*sensorH) * height / sensorH;
//        QPointF rv = QPointF(X, Y);
        QPointF rv = dt.recalcToPix(po);
        return QPoint(rv.x(), rv.y());
    }


    inline QPoint GetPixPosition(  double dist, double angel, const CameraInfo &dt)
    {
        double xm = dist * sin(angel);
        double ym = dist * cos(angel);
        double foca    = dt.focalLength;
        double camH    = dt.cameraH    ;
        double camBeta = dt.betaCnt    ;
        QPointF po = stalg::getCamPoint(xm, ym, foca / 1000., camH, radian(camBeta));
        QPointF rv = dt.recalcToPix(po);
        return QPoint(rv.x(), rv.y());
    }

    template<typename T>
    void minFilter(T** src, T** dst, int W, int H, int W0, int H0)
    {
        int SW0 = W0 / 2;
        int SH0 = H0 / 2;
//        stalg::Heap<T> heap(std::less<T>(), observer);
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                if (i >= SW0 && i + SW0 < W && j >= SH0 && j + SH0 < H)
                {
                    T min_val = src[j][i];
                    for (int ii = i - SW0; ii <= i + SW0; ++ii)
                    {
                        for (int jj = j - SH0; jj <= j + SH0; ++jj)
                        {
                            min_val = std::min(min_val, src[jj][ii]);
                        }
                    }
                    dst[j][i] = min_val;
                }
                else
                {
                    dst[j][i] = src[j][i];
                }
            }
        }
    }



    class STreeNode
    {
    private:
        STreeNode *parent;
        std::vector<STreeNode*> children;
    public:
    };
    class STree
    {
    private:
        STreeNode *current_node;
    };
}

#endif // __ST_ALG_COMMON_H__
