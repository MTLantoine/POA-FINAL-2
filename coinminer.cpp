#include <iostream>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include <algorithm>

using namespace std;

class ErrorException
{

public:
    string msg;

    ErrorException()
    {
        msg = "An error occured.";
    }
};

class Coincoin
{

private:
    string triOwn;

public:
    Coincoin(string tri)
    {
        triOwn = tri;
    }

    string generateNonce()
    {
        string nonce;
        for (int i = 0; i < 32; i++)
        {
            nonce += rand() % 95 + 32;
        }
        return nonce;
    }

    string generateTime()
    {
        time_t today;
        today = time(0);
        return to_string(today);
    }

    string generateToken()
    {
        string nonce;
        string newTriOwn;
        string proto;
        string mtime;
        string reserved;
        string count;

        nonce = generateNonce();
        newTriOwn = triOwn;
        transform(newTriOwn.begin(), newTriOwn.end(), newTriOwn.begin(), ::toupper);
        proto = "CC1.0";
        mtime = generateTime();
        reserved = "0f0f0f";

        return nonce + "-" + newTriOwn + "-" + proto + "-" + mtime + "-" + reserved;
    }

    string hashToken(string token)
    {
        unsigned char hash[SHA_DIGEST_LENGTH];
        char tokenArray[60];
        char result[SHA_DIGEST_LENGTH];
        strcpy(tokenArray, token.c_str());

        // unsigned char *SHA1(const unsigned char *d, size_t n, unsigned char *md);
        SHA1((unsigned char *)tokenArray, 60, hash);

        for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        {
            sprintf(&result[i * 2], "%02x", (unsigned int)hash[i]);
        }

        return result;
    }

    void miningProjections(int cmpt, int timer)
    {
        int projectionTime;
        int hour;
        int minute;

        cout << cmpt << " * 5c (miette) mined in " << timer << "s" << endl;
        cout << "*** Mining projections ***" << endl;

        projectionTime = timer / cmpt;
        minute = projectionTime / 60;
        hour = minute / 60;
        cout << "5c (miette)          " << projectionTime << "s     (" << hour << "." << minute % 60 << " h)" << endl;

        projectionTime *= 16;
        minute = projectionTime / 60;
        hour = minute / 60;
        cout << "6c (subcoin)         " << projectionTime << "s     (" << hour << "." << minute % 60 << " h)" << endl;

        projectionTime *= 16;
        minute = projectionTime / 60;
        hour = minute / 60;
        cout << "7c (coin)            " << projectionTime << "s     (" << hour << "." << minute % 60 << " h)" << endl;

        projectionTime *= 16;
        minute = projectionTime / 60;
        hour = minute / 60;
        cout << "8c (hexcoin)         " << projectionTime << "s     (" << hour << "." << minute % 60 << " h)" << endl;

        projectionTime *= 16;
        minute = projectionTime / 60;
        hour = minute / 60;
        cout << "9c (arkenstone)      " << projectionTime << "s     (" << hour << "." << minute % 60 << " h)" << endl;

        projectionTime *= 16;
        minute = projectionTime / 60;
        hour = minute / 60;
        cout << "10c (blackstar)      " << projectionTime << "s     (" << hour << "." << minute % 60 << " h)" << endl;

        projectionTime *= 16;
        minute = projectionTime / 60;
        hour = minute / 60;
        cout << "11c (grand cross)    " << projectionTime << "s     (" << hour << "." << minute % 60 << " h)" << endl;
    }

    void benchmark(int timer)
    {

        cout << "Starting benchmark..." << endl;

        string token;
        string hash;
        string tri = "AMO";

        time_t oldTime = time(0);
        time_t newTime = time(0);

        int cmpt = 0;
        int totalTime;

        while (newTime - oldTime < timer)
        {
            token = generateToken();
            hash = hashToken(token);
            newTime = time(0);

            if (hash.substr(0, 5) == "ccccc")
            {
                cmpt++;
                totalTime = newTime - oldTime;
            }
        }

        miningProjections(cmpt, totalTime);
    }

    void mining(int m)
    {
        string token;
        string hash;
        string c = "";

        for (int i = 0; i < m; i++)
        {
            c += "c";
        }

        while (1)
        {
            token = generateToken();
            hash = hashToken(token);

            if (hash.substr(0, m) == c)
            {
                cout << "\n"
                     << token << " : " << hash << endl;
            }
        }
    }
};

Coincoin *coincoin;

int main(int argc, char *argv[])
{
    coincoin = new Coincoin("AMO");
    string msg = "";
    srand(time(0));
    try
    {
        if (argc == 5)
        {
            string tri = (string)argv[2];
            if ((string)argv[1] == "-t" && (string)argv[3] == "-m" && tri.length() == 3)
            {
                coincoin = new Coincoin(tri);
                coincoin->mining(atoi(argv[4]));
            }
            else
            {
                throw ErrorException();
            }
        }
        else if (argc == 2)
        {
            if ((string)argv[1] == "-z")
            {
                // mine pendant 55 secondes avant d'afficher les prédictions
                coincoin->benchmark(55);
            }
            else
            {
                throw ErrorException();
            }
        }
        else
        {
            throw ErrorException();
        }
    }
    catch (ErrorException e)
    {
        cout << e.msg << endl;
    }
    return 0;
}