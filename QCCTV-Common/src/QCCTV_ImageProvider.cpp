/*
 * Copyright (c) 2016 Alex Spataru
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE
 */

#include "QCCTV_Station.h"
#include "QCCTV_LocalCamera.h"
#include "QCCTV_ImageProvider.h"

//------------------------------------------------------------------------------
// QCCTV_Station Image Provider
//------------------------------------------------------------------------------

QCCTV_StationImage::QCCTV_StationImage (QCCTV_Station* parent) :
    QQuickImageProvider (QQuickImageProvider::Image,
                         QQuickImageProvider::ForceAsynchronousImageLoading)
{
    m_station = parent;
    m_cameraError = QCCTV_GET_STATUS_IMAGE (QSize (640, 480), "CAMERA ERROR");
}

QImage QCCTV_StationImage::requestImage (const QString& id,
                                         QSize* size,
                                         const QSize& requestedSize)
{
    Q_UNUSED (size);
    Q_UNUSED (requestedSize);

    if (m_station && !id.isEmpty()) {
        QImage image = m_station->currentImage (id.toInt());
        if (!image.isNull())
            return image;
    }

    return m_cameraError;
}

//------------------------------------------------------------------------------
// QCCTV_LocalCamera Image Provider
//------------------------------------------------------------------------------

QCCTV_LocalCameraImage::QCCTV_LocalCameraImage (QCCTV_LocalCamera* parent) :
    QQuickImageProvider (QQuickImageProvider::Image)
{
    m_localCamera = parent;
    m_cameraError = QCCTV_GET_STATUS_IMAGE (QSize (640, 480), "IMAGE ERROR");
}

QImage QCCTV_LocalCameraImage::requestImage (const QString& id, QSize* size,
                                             const QSize& requestedSize)
{
    Q_UNUSED (id);
    Q_UNUSED (size);
    Q_UNUSED (requestedSize);

    if (m_localCamera)
        return m_localCamera->currentImage();

    return m_cameraError;
}