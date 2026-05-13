#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
class XucXac {
public:
    int tung() {
        return rand() % 6;
    }
};

class NhaCai {
private:
    XucXac xucxac;
    vector<int> ketqua;

public:
    void tungXucXac() {
        ketqua.clear();
        for (int i = 0; i < 3; i++) {
            ketqua.push_back(xucxac.tung());
        }
    }

    vector<int> layKetQua() {
        return ketqua;
    }
};

class NguoiChoi {
protected:
    int tongTienThang;

public:
    NguoiChoi() {
        tongTienThang = 0;
    }

    virtual void datCuoc() = 0;
    virtual void tinhTien(vector<int> ketqua) = 0;

    int layTienThang() {
        return tongTienThang;
    }
};

class NguoiChoi1 : public NguoiChoi {
private:
    int oChon;
    int tienCuoc;

public:
    void datCuoc() {
        oChon = rand() % 6;
        tienCuoc = 4;
    }

    void tinhTien(vector<int> ketqua) {
        int dem = 0;
        for (int k : ketqua) {
            if (k == oChon) dem++;
        }

        if (dem > 0) {
            tongTienThang += dem * tienCuoc;
        }
    }
};

class NguoiChoi2 : public NguoiChoi {
private:
    int o1, o2;
    int tienMoiO;

public:
    void datCuoc() {
        o1 = rand() % 6;
        do {
            o2 = rand() % 6;
        } while (o2 == o1);

        tienMoiO = 2;
    }

    void tinhTien(vector<int> ketqua) {
        int dem1 = 0, dem2 = 0;

        for (int k : ketqua) {
            if (k == o1) dem1++;
            if (k == o2) dem2++;
        }

        if (dem1 > 0) {
            tongTienThang += dem1 * tienMoiO;
        }
        if (dem2 > 0) {
            tongTienThang += dem2 * tienMoiO;
        }
    }
};
int main() {
    srand(time(0));

    NhaCai nhacai;
    NguoiChoi1 nc1;
    NguoiChoi2 nc2;

    int soVan = 1000;

    for (int i = 0; i < soVan; i++) {
        nhacai.tungXucXac();

        vector<int> kq = nhacai.layKetQua();

        nc1.datCuoc();
        nc2.datCuoc();

        nc1.tinhTien(kq);
        nc2.tinhTien(kq);
    }

    int tien1 = nc1.layTienThang();
    int tien2 = nc2.layTienThang();

    cout << "Nguoi choi 1 thang: " << tien1 << " dong\n";
    cout << "Nguoi choi 2 thang: " << tien2 << " dong\n";

    if (tien1 > tien2) {
        cout << "=> Chien thuat nguoi choi 1 tot hon (it lo hon)\n";
    }
    else if (tien2 > tien1) {
        cout << "=> Chien thuat nguoi choi 2 tot hon (it lo hon)\n";
    }
    else {
        cout << "=> Hai chien thuat bang nhau\n";
    }

    return 0;
}
