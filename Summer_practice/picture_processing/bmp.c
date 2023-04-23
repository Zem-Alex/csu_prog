#include <windows.h>
#include <malloc.h>
#include "bmp.h"


//----------------------------------------

//
// ������� ����������� �������� �� ��������� ����������
//
void DrawBitmap (HDC hdc, HBITMAP hBitmap, int xStart, int yStart) { 

BITMAP bm; 
HDC hdcMem; 
POINT ptSize;
POINT ptOrg;

    // ������� ������� ������ (�������� ����������, ������������ ������ � ������),
    // ����������� � ������������ ��������� ���������� hdc
    // ����� �������� �������� ������ 1 ����������� �������
	hdcMem = CreateCompatibleDC (hdc);

    // �������� �������� � �������� ����������
    // ����� ����� ������ ����������� ��������� ������
    // ����� ����� ������� ��������
	SelectObject (hdcMem, hBitmap);

    // �������� ����� �����������
	SetMapMode(hdcMem, GetMapMode(hdc)); 

    // ��������� ��������� ����������� ��������
	GetObject (hBitmap, sizeof(BITMAP), (LPVOID) &bm); 

    // ����������� ���������� ���������� � ����������
	ptSize.x = bm.bmWidth; 
	ptSize.y = bm.bmHeight;
	DPtoLP (hdc, &ptSize, 1); 
	ptOrg.x = 0; 
	ptOrg.y = 0; 
	DPtoLP (hdcMem, &ptOrg, 1);

    // ������� ����� �������� �� ��������� ������ �� �������� ����������
	BitBlt (hdc, xStart, yStart, ptSize.x, ptSize.y, 
			hdcMem, ptOrg.x, ptOrg.y, SRCCOPY);

    // �������� ��������� ������
	DeleteDC (hdcMem);
	return;
} 

//--------------------

//
// ��������� �������� �� ����� � ������
//
HBITMAP LoadBmpFile (HWND MainWindow, HINSTANCE ins) {

OPENFILENAMEA ofn;
char szFile[MAX_PATH] = "";
HBITMAP bm = NULL;

	ZeroMemory (&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = MainWindow;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "bmp-�����\0*.bmp\0��� �����\0*.*\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileNameA (&ofn)) {
		bm = (HBITMAP)LoadImage (ins, szFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}

	return bm;
}

//--------------------

//
// ������ bmp-���� � ���������� ���������
//
void CreateBMPFile (LPTSTR pszFile, HBITMAP hBitmap, HWND MainWindow) { 

BITMAP bitmap; 
HANDLE hf;                  // ��������� �����
BITMAPFILEHEADER hdr;       //	��������� �� �������� ��������� ����� 
BITMAPINFOHEADER bmih;      // ��������� �� ��������� �������
unsigned char *bits;
unsigned int size_bitmap;
LPDWORD tmp;
HDC hdc;
 
    if (!GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bitmap)) 
        return; 

	if (bitmap.bmBitsPixel != 32)
		return;

	bmih.biSize = sizeof(BITMAPINFOHEADER); 
	bmih.biWidth = bitmap.bmWidth; 
	bmih.biHeight = bitmap.bmHeight; 
	bmih.biPlanes = bitmap.bmPlanes; 
	bmih.biBitCount = bitmap.bmBitsPixel;  
	bmih.biClrUsed = 0;
	bmih.biCompression = BI_RGB; 
	bmih.biSizeImage = 0;
	bmih.biClrImportant = 0; 

	size_bitmap = 4 * bitmap.bmHeight * bitmap.bmWidth;
    bits = (unsigned char*) malloc (size_bitmap);

    if(!bits) 
         return;

	hdc = GetDC(MainWindow);
	if (!GetDIBits (hdc, hBitmap, 0, (WORD) bmih.biHeight, bits, (LPBITMAPINFO) &bmih, DIB_RGB_COLORS))
		return;

    hf = CreateFile (pszFile, 
                   GENERIC_READ | GENERIC_WRITE, 
                   (DWORD) 0, 
                    NULL, 
                   CREATE_ALWAYS, 
                   FILE_ATTRIBUTE_NORMAL, 
                   (HANDLE) NULL); 
    if (hf == INVALID_HANDLE_VALUE) {
        return;
        }
	
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
	hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + bmih.biSize + size_bitmap); 
	hdr.bfReserved1 = 0; 
	hdr.bfReserved2 = 0; 

	hdr.bfOffBits = (DWORD) (sizeof(BITMAPFILEHEADER) + bmih.biSize); 

	if (WriteFile (hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), (LPDWORD) &tmp, NULL) &&
	    WriteFile (hf, (LPVOID) &bmih, sizeof(BITMAPINFOHEADER), (LPDWORD) &tmp, NULL) &&
	    WriteFile(hf, (LPSTR) bits, size_bitmap, (LPDWORD) &tmp, NULL));

	CloseHandle(hf);

    free (bits);

	return; 
}


//--------------------

//
// ��������� �������� � ����
//
void SaveBMPFile (HBITMAP hBitmap, HWND MainWindow){

OPENFILENAMEA ofn;
char szFile[MAX_PATH]="";

	ZeroMemory(&ofn,sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.hwndOwner = MainWindow;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "bmp-�����\0*.bmp\0��� �����\0*.*\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetSaveFileNameA (&ofn))
		CreateBMPFile (szFile, hBitmap, MainWindow);
		
	return;
}

//--------------------

//
// ���������� �������� � �������, ����������������
// ������������ ���������
//
HBITMAP InvertBitmap (HBITMAP srcBitmap) {


BITMAP bitmap;
HBITMAP dstBitmap;
unsigned char *bits;
unsigned char *pBits;
unsigned int pixelCount;
int i, j;
unsigned int bytesPixel;


    if (!GetObject(srcBitmap,sizeof(BITMAP),&bitmap))
		return NULL;

    if( (bitmap.bmBitsPixel != 24) && (bitmap.bmBitsPixel != 32) ){
        //MessageBox (NULL, "", "����������� ������ ��������� 32 ��� 24 ���� �� �������", MB_OK);
        return NULL;
        }

    pixelCount = bitmap.bmHeight * bitmap.bmWidth;

    bytesPixel = bitmap.bmBitsPixel / 8;

    //bits = (unsigned char*) malloc (bytesPixel * pixelCount);
    bits = (unsigned char*) malloc (bitmap.bmWidthBytes * bitmap.bmHeight);
    if (!bits) {
        //MessageBox(HwndMainWindow,"","������ ��������� ������",MB_OK);
        return NULL;
        }

    //GetBitmapBits (srcBitmap, bitmap.bmBitsPixel * pixelCount, (void*)bits);
    GetBitmapBits (srcBitmap, bitmap.bmWidthBytes * bitmap.bmHeight, (void*)bits);

    //pBits = bits;

    for (i = 0; i < bitmap.bmHeight; ++i) {
        pBits = bits + i * bitmap.bmWidthBytes;
        for (j = 0; j < bitmap.bmWidth; ++j) {
            unsigned int pixel = 0;
            memcpy (&pixel, pBits, bytesPixel);

            pixel = ~pixel & 0x00FFFFFF;

            memcpy (pBits, &pixel, bytesPixel);
            pBits += bytesPixel;
            }
        }

    dstBitmap = CreateBitmap (bitmap.bmWidth, bitmap.bmHeight, 1, bitmap.bmBitsPixel, bits);

    free (bits);

    return dstBitmap;
}

//--------------------

//
// ���������� �������� �������� � �������� ������
//
HBITMAP GetGraystyleBitmap (HBITMAP srcBitmap) {


BITMAP bitmap;
HBITMAP dstBitmap;
unsigned char *bits;
unsigned char *pBits;
unsigned int pixelCount;
unsigned int bytesPixel;
int i, j;


    if (!GetObject(srcBitmap,sizeof(BITMAP),&bitmap)) {
		return NULL;
        }

    if( (bitmap.bmBitsPixel != 24) && (bitmap.bmBitsPixel != 32) ){
        //MessageBox (NULL, "", "����������� ������ ��������� 32 ��� 24 ���� �� �������", MB_OK);
        return NULL;
        }

    pixelCount = bitmap.bmHeight * bitmap.bmWidth;

    bytesPixel = bitmap.bmBitsPixel / 8;

    bits = (unsigned char*) malloc (bitmap.bmWidthBytes * bitmap.bmHeight);
    if (!bits) {
        //MessageBox(HwndMainWindow,"","������ ��������� ������",MB_OK);
        return NULL;
        }

    GetBitmapBits (srcBitmap, bitmap.bmBitsPixel * pixelCount, (void*)bits);

    pBits = bits;

    for (i = 0; i < bitmap.bmHeight; ++i) {
        pBits = bits + i * bitmap.bmWidthBytes;
        for (j = 0; j < bitmap.bmWidth; ++j) {
            unsigned int pixel = 0;
            unsigned int r, g, b;
            unsigned int gray;
            memcpy (&pixel, pBits, bytesPixel);

            r = pixel & 0xFF;
            g = (pixel >> 8) & 0xFF;
            b = (pixel >> 16) & 0xFF;
            gray = (r + g + b)/3;
            pixel = gray | (gray << 8) | (gray << 16);

            memcpy (pBits, &pixel, bytesPixel);
            pBits += bytesPixel;
            }
        }

    dstBitmap = CreateBitmap (bitmap.bmWidth, bitmap.bmHeight, 1, bitmap.bmBitsPixel, bits);

    free (bits);

    return dstBitmap;
}

HBITMAP changeBitmapL(HBITMAP srcBitmap) {
    BITMAP bitmap;
    HBITMAP dstBitmap;
    unsigned char* bits;
    unsigned char* pBits;
    unsigned int pixelCount;
    int i, j;
    unsigned int bytesPixel;
    if (!GetObject(srcBitmap, sizeof(BITMAP), &bitmap))
        return NULL;
    if ((bitmap.bmBitsPixel != 24) && (bitmap.bmBitsPixel != 32)) {
        //MessageBox (NULL, "", "����������� ������ ��������� 32 ��� 24 ���� �� �������", MB_OK);
        return NULL;
    }

    pixelCount = bitmap.bmHeight * bitmap.bmWidth;

    bytesPixel = bitmap.bmBitsPixel / 8;

    //bits = (unsigned char*) malloc (bytesPixel * pixelCount);
    bits = (unsigned char*)malloc(bitmap.bmWidthBytes * bitmap.bmHeight);
    if (!bits) {
        //MessageBox(HwndMainWindow,"","������ ��������� ������",MB_OK);
        return NULL;
    }

    //GetBitmapBits (srcBitmap, bitmap.bmBitsPixel * pixelCount, (void*)bits);
    GetBitmapBits(srcBitmap, bitmap.bmWidthBytes * bitmap.bmHeight, (void*)bits);

    //pBits = bits;

    for (i = 0; i < bitmap.bmHeight; ++i) {
        pBits = bits + i * bitmap.bmWidthBytes;
        for (j = 0; j < bitmap.bmWidth; ++j) {
            DWORD new_pixel = 0;
            DWORD temp = 0;
            memcpy(&temp, pBits, bytesPixel);
            for (int i = 0; i < 3; i++) {
                DWORD byte = ((temp >> (i * 8)) & 0xFF) + 30;
                if (byte > 0xFF)
                    byte = 0xFF;
                new_pixel |= byte << (8 * i);
            }
            memcpy(pBits, &new_pixel, bytesPixel);
            pBits += bytesPixel;
        }
    }

    dstBitmap = CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, 1, bitmap.bmBitsPixel, bits);

    free(bits);

    return dstBitmap;
}

HBITMAP changeBitmapD(HBITMAP srcBitmap) {
    BITMAP bitmap;
    HBITMAP dstBitmap;
    unsigned char* bits;
    unsigned char* pBits;
    unsigned int pixelCount;
    int i, j;
    unsigned int bytesPixel;
    if (!GetObject(srcBitmap, sizeof(BITMAP), &bitmap))
        return NULL;
    if ((bitmap.bmBitsPixel != 24) && (bitmap.bmBitsPixel != 32)) {
        //MessageBox (NULL, "", "����������� ������ ��������� 32 ��� 24 ���� �� �������", MB_OK);
        return NULL;
    }

    pixelCount = bitmap.bmHeight * bitmap.bmWidth;

    bytesPixel = bitmap.bmBitsPixel / 8;

    //bits = (unsigned char*) malloc (bytesPixel * pixelCount);
    bits = (unsigned char*)malloc(bitmap.bmWidthBytes * bitmap.bmHeight);
    if (!bits) {
        //MessageBox(HwndMainWindow,"","������ ��������� ������",MB_OK);
        return NULL;
    }

    //GetBitmapBits (srcBitmap, bitmap.bmBitsPixel * pixelCount, (void*)bits);
    GetBitmapBits(srcBitmap, bitmap.bmWidthBytes * bitmap.bmHeight, (void*)bits);

    //pBits = bits;

    for (i = 0; i < bitmap.bmHeight; ++i) {
        pBits = bits + i * bitmap.bmWidthBytes;
        for (j = 0; j < bitmap.bmWidth; ++j) {
            DWORD new_pixel = 0;
            DWORD temp = 0;
            memcpy(&temp, pBits, bytesPixel);
            for (int i = 0; i < 3; i++) {
                DWORD byte = ((temp >> (i * 8)) & 0xFF) - 30;
                if (byte < 0)
                    byte = 0;
                new_pixel |= byte << (8 * i);
            }
            memcpy(pBits, &new_pixel, bytesPixel);
            pBits += bytesPixel;
        }
    }

    dstBitmap = CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, 1, bitmap.bmBitsPixel, bits);

    free(bits);

    return dstBitmap;
}

HBITMAP changeBitmapBW(HBITMAP srcBitmap) {
    BITMAP bitmap;
    HBITMAP dstBitmap;
    unsigned char* bits;
    unsigned char* pBits;
    unsigned int pixelCount;
    int i, j;
    unsigned int bytesPixel;
    if (!GetObject(srcBitmap, sizeof(BITMAP), &bitmap))
        return NULL;
    if ((bitmap.bmBitsPixel != 24) && (bitmap.bmBitsPixel != 32)) {
        //MessageBox (NULL, "", "����������� ������ ��������� 32 ��� 24 ���� �� �������", MB_OK);
        return NULL;
    }

    pixelCount = bitmap.bmHeight * bitmap.bmWidth;

    bytesPixel = bitmap.bmBitsPixel / 8;

    //bits = (unsigned char*) malloc (bytesPixel * pixelCount);
    bits = (unsigned char*)malloc(bitmap.bmWidthBytes * bitmap.bmHeight);
    if (!bits) {
        //MessageBox(HwndMainWindow,"","������ ��������� ������",MB_OK);
        return NULL;
    }

    //GetBitmapBits (srcBitmap, bitmap.bmBitsPixel * pixelCount, (void*)bits);
    GetBitmapBits(srcBitmap, bitmap.bmWidthBytes * bitmap.bmHeight, (void*)bits);

    for (i = 0; i < bitmap.bmHeight; ++i) {
        pBits = bits + i * bitmap.bmWidthBytes;
        for (j = 0; j < bitmap.bmWidth; ++j) {
            DWORD new_pixel = 0;
            memcpy(&new_pixel, pBits, bytesPixel);
            if ((new_pixel & 0xFF) > 0x7F)
                new_pixel = 0xFFFFFF;
            else
                new_pixel = 0x000000;
            memcpy(pBits, &new_pixel, bytesPixel);
            pBits += bytesPixel;
        }
    }

    dstBitmap = CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, 1, bitmap.bmBitsPixel, bits);

    free(bits);

    return dstBitmap;
}

HBITMAP flipBitmap(HBITMAP srcBitmap) {
    BITMAP bitmap;
    HBITMAP dstBitmap;
    DWORD tempbit;
    unsigned char* bits;
    unsigned char* pBits;
    unsigned int pixelCount;
    int i, j;
    unsigned int bytesPixel;
    if (!GetObject(srcBitmap, sizeof(BITMAP), &bitmap))
        return NULL;
    if ((bitmap.bmBitsPixel != 24) && (bitmap.bmBitsPixel != 32)) {
        //MessageBox (NULL, "", "����������� ������ ��������� 32 ��� 24 ���� �� �������", MB_OK);
        return NULL;
    }

    pixelCount = bitmap.bmHeight * bitmap.bmWidth;

    bytesPixel = bitmap.bmBitsPixel / 8;

    bits = (unsigned char*)malloc(bitmap.bmWidthBytes * bitmap.bmHeight);
    if (!bits) {
        return NULL;
    }

    GetBitmapBits(srcBitmap, bitmap.bmWidthBytes * bitmap.bmHeight, (void*)bits);

    for (int i = 0; i < bitmap.bmHeight; i++) {
        byte* startbit = bits + i * bitmap.bmWidthBytes;
        byte* endbit = bits + i * bitmap.bmWidthBytes + bitmap.bmWidthBytes - bytesPixel;
        //������ ������ �����
        for (; startbit < endbit; startbit += bytesPixel, endbit -= bytesPixel) {
            memcpy(&tempbit, endbit, bytesPixel);
            memcpy(endbit, startbit, bytesPixel);
            memcpy(startbit, &tempbit, bytesPixel);
        }
    }
    dstBitmap = CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, 1, bitmap.bmBitsPixel, bits);

    free(bits);

    return dstBitmap;
}

HBITMAP Grid(HBITMAP srcBitmap) {
    BITMAP bitmap;
    HBITMAP dstBitmap;
    byte* newbits;
    byte* pBits;
    byte* bits;
    byte* tmp;

    int i, j;
    if (!GetObject(srcBitmap, sizeof(BITMAP), &bitmap))
        return NULL;
    if ((bitmap.bmBitsPixel != 24) && (bitmap.bmBitsPixel != 32)) {
        return NULL;
    }


    size_t bmpSize = bitmap.bmWidthBytes * bitmap.bmHeight;
    bits = (byte*)malloc(bmpSize);
    if (!bits) {
        return NULL;
    }
    newbits = (byte*)malloc(bmpSize * 4);
    if (!newbits) {
        free(newbits);
        return NULL;
    }

    GetBitmapBits(srcBitmap, bmpSize, bits);

    for (int i = 0; i < bitmap.bmHeight; i++) {
        pBits = bits + bitmap.bmWidthBytes * i;
        tmp = newbits + bitmap.bmWidthBytes * 2 * i;
        memcpy(tmp, pBits, bitmap.bmWidthBytes);
        memcpy(tmp + bitmap.bmWidthBytes, pBits, bitmap.bmWidthBytes);
    }
    memcpy(newbits + 2 * bmpSize, newbits, 2 * bmpSize);

    dstBitmap = CreateBitmap(bitmap.bmWidth * 2, bitmap.bmHeight * 2, 1, bitmap.bmBitsPixel, newbits);

    free(newbits);
    free(bits);
    return dstBitmap;
}



//--------------------


/*
HBITMAP ConvertTo24Bitmap (HBITMAP srcBitmap) {


BITMAP bitmap;
HBITMAP dstBitmap;
unsigned char *srcBits;
unsigned char *dstBits;
unsigned int dstBytesPixel;
unsigned int dstWidthBytes;
unsigned char *pSrcBits;
unsigned char *pDstBits;
unsigned int pixelCount;
unsigned int srcBytesPixel;
int i, j;


    if (!GetObject(srcBitmap,sizeof(BITMAP),&bitmap)) {
		return NULL;
        }

    if( (bitmap.bmBitsPixel != 24) && (bitmap.bmBitsPixel != 32) ){
        //MessageBox (NULL, "", "����������� ������ ��������� 32 ��� 24 ���� �� �������", MB_OK);
        return NULL;
        }

    pixelCount = bitmap.bmHeight * bitmap.bmWidth;

    srcBytesPixel = bitmap.bmBitsPixel / 8;

    srcBits = (unsigned char*) malloc (bitmap.bmWidthBytes * bitmap.bmHeight);
    if (!srcBits) {
        //MessageBox(HwndMainWindow,"","������ ��������� ������",MB_OK);
        return NULL;
        }

    GetBitmapBits (srcBitmap, bitmap.bmBitsPixel * pixelCount, (void*)srcBits);

    dstBytesPixel = 3;
    dstWidthBytes = dstBytesPixel * bitmap.bmWidth;
    if (dstWidthBytes % 4) {
        dstWidthBytes = 4 * (dstWidthBytes / 4) + 4;
    }

    dstBits = (unsigned char*) malloc (dstWidthBytes * bitmap.bmHeight);
    if (!dstBits) {
        free (srcBits);
        return NULL;
        }


    pSrcBits = srcBits;
    pDstBits = dstBits;

    for (i = 0; i < bitmap.bmHeight; ++i) {
        pSrcBits = srcBits + i * bitmap.bmWidthBytes;
        pDstBits = dstBits + i * dstWidthBytes;
        for (j = 0; j < bitmap.bmWidth; ++j) {
            memcpy (pDstBits, pSrcBits, dstBytesPixel);
            pSrcBits += srcBytesPixel;
            pDstBits += dstBytesPixel;
            }
        }

    dstBitmap = CreateBitmap (bitmap.bmWidth, bitmap.bmHeight, 1, 8 * dstBytesPixel, dstBits);

    free (srcBits);
    free (dstBits);

    return dstBitmap;
}
*/


//--------------------

