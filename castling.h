#pragma once


class Castling {
    public:
        bool wkc;
        bool wqc;
        bool bkc;
        bool bqc;

        Castling();

        Castling(bool wk, bool wq, bool bk, bool bq);
};