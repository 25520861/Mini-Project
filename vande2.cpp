#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

enum Mat { BAU, CUA, TOM, CA, GA, NAI };

class XucXac {
public:
    virtual int tung() {
        return rand() % 6;
    }
};


class XucXacBip : public XucXac {
public:
    int tung() override {
        int r = rand() % 100;

        if (r < 30) return 0;
        else if (r < 45) return 1;
        else if (r < 60) return 2;
        else if (r < 75) return 3;
        else if (r < 90) return 4;
        else return 5;
    }
};

class NguoiChoi {
private:
    int tien;
public:
    NguoiChoi(int t = 0) {
        tien = t;
    }

    vector<pair<int, int>> datCuoc() {
        vector<pair<int, int>> cuoc;

        int o1 = rand() % 6;
        int o2;
        do {
            o2 = rand() % 6;
        } while (o2 == o1);

        cuoc.push_back({ o1, 2 });
        cuoc.push_back({ o2, 2 });

        tien -= 4;
        return cuoc;
    }

    void capNhatTien(int soTien) {
        tien += soTien;
    }
};

class NhaCai {
private:
    int loi;
public:
    NhaCai() {
        loi = 0;
    }

    void capNhat(int soTien) {
        loi += soTien;
    }

    int getLoi() {
        return loi;
    }
};

class Game {
protected:
    XucXac* xucxac;
    NguoiChoi player;
    NhaCai dealer;

public:
    Game(XucXac* xx) : xucxac(xx), player(0) {}

    int choi1000Van() {
        for (int v = 1; v <= 1000; v++) {

            vector<pair<int, int>> cuoc = player.datCuoc();

            vector<int> ketQua(3);
            for (int i = 0; i < 3; i++) {
                ketQua[i] = xucxac->tung();
            }

            int tienTra = 0;

            for (auto& c : cuoc) {
                int mat = c.first;
                int tienCuoc = c.second;

                int dem = 0;
                for (int k : ketQua) {
                    if (k == mat) dem++;
                }

                if (dem > 0) {
                    tienTra += tienCuoc * dem + tienCuoc;
                }
            }

            player.capNhatTien(tienTra);

            int tienNhaCai = 4 - tienTra;
            dealer.capNhat(tienNhaCai);
        }

        return dealer.getLoi();
    }
};

int main() {
    srand(time(0));


    XucXac* xx1 = new XucXac();
    Game songCongBang(xx1);


    XucXac* xx2 = new XucXacBip();
    Game songBip(xx2);

    int loi1 = songCongBang.choi1000Van();
    int loi2 = songBip.choi1000Van();

    cout << "Nha cai (song cong bang): " << loi1 << endl;
    cout << "Nha cai (song bip): " << loi2 << endl;

    cout << "\nSo sanh:\n";
    if (loi2 > loi1)
        cout << "Song bip loi nhieu hon!" << endl;
    else if (loi2 < loi1)
        cout << "Song cong bang loi nhieu hon!" << endl;
    else
        cout << "Hai song loi bang nhau!" << endl;

    delete xx1;
    delete xx2;

    return 0;
}