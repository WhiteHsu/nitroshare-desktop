/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 **/

#ifndef NS_TRANSFER_H
#define NS_TRANSFER_H

#include <QHostAddress>
#include <QSharedPointer>
#include <QThread>

#include "../device/device.h"
#include "../filesystem/bundle.h"
#include "../socket/socket.h"

class Transfer : public QObject
{
    Q_OBJECT

public:

    enum Direction {
        Send,
        Receive
    };

    Transfer(qintptr socketDescriptor);
    Transfer(DevicePointer device, BundlePointer bundle);

    virtual ~Transfer();

    QString deviceName() const;
    int progress() const;
    Direction direction() const;

    void start();
    void cancel();

signals:

    void statusChanged();

    void error(const QString &message);
    void completed();
    void finished();

private slots:

    void setDeviceName(const QString &deviceName);
    void setProgress(int progress);

private:

    void initialize();

    QSharedPointer<Socket> mConnection;
    QThread mThread;

    QString mDeviceName;
    int mProgress;
    Direction mDirection;
};

typedef QSharedPointer<Transfer> TransferPointer;
Q_DECLARE_METATYPE(TransferPointer)

#endif // NS_TRANSFER_H
