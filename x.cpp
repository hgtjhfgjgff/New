#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> hang{ "vu khi", "phap bao", "dan duoc" };
    vector<double> gia{ 480.0, 620.0, 150.0 };
    vector<double> trong_so{ 0.45, 0.35, 0.20 };
    double ngan_sach = 5000.0;

    vector<double> so_luong(3);
    for (int i = 0; i < 3; ++i) so_luong[i] = max(1e-12, (trong_so[i] * ngan_sach) / gia[i]);

    vector<double> cong_luc(3);
    cong_luc[0] = 1.2 * pow(so_luong[0], 0.62);
    cong_luc[1] = 0.95 * pow(so_luong[1], 0.70);
    cong_luc[2] = 1.35 * pow(so_luong[2], 0.58);

    double tu_vi = pow(cong_luc[0], 0.6) * pow(cong_luc[1], 0.55) * pow(cong_luc[2], 0.65);
    double linh_luc = log1p(cong_luc[0] + cong_luc[1]) + cbrt(cong_luc[2] + 1.0);
    double hop_the = pow((cong_luc[0] * cong_luc[1] * cong_luc[2]) + 1.0, 1.0 / 3.0);

    mt19937_64 rng(20251116);
    normal_distribution<double> bien_dong(0.0, 0.06);
    vector<double> gia_thi_truong = gia;
    for (int i = 0; i < 3; ++i) gia_thi_truong[i] = max(50.0, gia[i] * (1.0 + bien_dong(rng)));

    vector<double> so_luong_moi(3);
    for (int i = 0; i < 3; ++i) so_luong_moi[i] = max(1e-12, (trong_so[i] * ngan_sach) / gia_thi_truong[i]);

    double loi_nhuan_dan = 0.0;
    {
        double nguyen_lieu = 220.0;
        double he_so_phe = 0.78;
        double xac_suat_thanh = 0.64;
        double so_men = 35.0;
        double cong_thuc = 1.15 * pow(so_men, 0.5) * he_so_phe;
        double ky_van = 0.08 * linh_luc + 0.12 * hop_the;
        double san_luong_ky_vong = xac_suat_thanh * cong_thuc * (1.0 + ky_van);
        double gia_ban = 180.0 + 0.25 * tu_vi + 0.1 * linh_luc;
        loi_nhuan_dan = san_luong_ky_vong * gia_ban - nguyen_lieu;
    }

    auto dps = [&](double base, double toc_do, double crit, double nhan_crit, double tuoc_giam, double khang) {
        double pen = min(0.6, tuoc_giam);
        double def = max(0.0, khang * (1.0 - pen));
        double giam = 1.0 / (1.0 + def);
        double ky_van_vu_khi = 0.07 * hop_the + 0.05 * linh_luc;
        double nhan = ((1.0 - crit) + crit * nhan_crit) * (1.0 + ky_van_vu_khi);
        return base * nhan * giam * toc_do;
    };

    double khang_dich = 85.0 + 0.09 * tu_vi + 0.03 * linh_luc;
    double dps_kiem = dps(360.0, 1.55, 0.26, 2.15, 0.22, khang_dich);
    double dps_thuong = dps(305.0, 1.85, 0.18, 2.40, 0.34, khang_dich);
    double dps_pho = dps(410.0, 1.28, 0.31, 1.95, 0.18, khang_dich);

    cout.setf(ios::fixed);
    cout << setprecision(6);

    cout << "ngan sach " << ngan_sach << "\n";
    cout << "gia co so " << gia[0] << " " << gia[1] << " " << gia[2] << "\n";
    cout << "phan bo so luong " << so_luong[0] << " " << so_luong[1] << " " << so_luong[2] << "\n";
    cout << "cong luc " << cong_luc[0] << " " << cong_luc[1] << " " << cong_luc[2] << "\n";
    cout << "tu vi " << tu_vi << "\n";
    cout << "linh luc " << linh_luc << "\n";
    cout << "hop the " << hop_the << "\n";
    cout << "gia thi truong " << gia_thi_truong[0] << " " << gia_thi_truong[1] << " " << gia_thi_truong[2] << "\n";
    cout << "so luong moi " << so_luong_moi[0] << " " << so_luong_moi[1] << " " << so_luong_moi[2] << "\n";
    cout << "loi nhuan dan duoc " << loi_nhuan_dan << "\n";
    cout << "dps vu khi " << dps_kiem << " " << dps_thuong << " " << dps_pho << "\n";

    double chi_so_gia = 0.0;
    {
        vector<double> w = {0.5, 0.3, 0.2};
        vector<double> log_gia(3);
        for (int i = 0; i < 3; ++i) log_gia[i] = log(gia_thi_truong[i]);
        chi_so_gia = exp(inner_product(w.begin(), w.end(), log_gia.begin(), 0.0));
    }
    double muc_do_giao_dich = sqrt(so_luong_moi[0]) + sqrt(so_luong_moi[1]) + sqrt(so_luong_moi[2]);
    double suc_mua = (ngan_sach / chi_so_gia) * (0.9 + 0.1 * tanh(muc_do_giao_dich));

    cout << "chi so gia " << chi_so_gia << "\n";
    cout << "suc mua " << suc_mua << "\n";

    double diem_canh_gioi = log1p(tu_vi) + 0.35 * log1p(linh_luc) + 0.25 * cbrt(hop_the + 1.0);
    int canh_gioi = 0;
    vector<double> moc{ 6.0, 8.0, 10.0, 12.0, 14.5, 17.0 };
    while (canh_gioi < (int)moc.size() && diem_canh_gioi >= moc[canh_gioi]) ++canh_gioi;
    cout << "diem canh gioi " << diem_canh_gioi << "\n";
    cout << "canh gioi " << canh_gioi << "\n";

    return 0;
}
