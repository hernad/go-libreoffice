/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

//#include <unotest/filters-test.hxx>
//#include <test/bootstrapfixture.hxx>

#include <vcl/wrkwin.hxx>

#include <osl/file.hxx>
#include <osl/process.h>

class VclComplexTextTest 
{
public:
    VclComplexTextTest() {}

    void testArabic();

};

void VclComplexTextTest::testArabic()
{
    const unsigned char pOneTwoThreeUTF8[] = {
        0xd9, 0x88, 0xd8, 0xa7, 0xd8, 0xad, 0xd9, 0x90,
        0xd8, 0xaf, 0xd9, 0x92, 0x20, 0xd8, 0xa5, 0xd8,
        0xab, 0xd9, 0x8d, 0xd9, 0x86, 0xd9, 0x8a, 0xd9,
        0x86, 0x20, 0xd8, 0xab, 0xd9, 0x84, 0xd8, 0xa7,
        0xd8, 0xab, 0xd8, 0xa9, 0xd9, 0x8c, 0x00
    };
    OUString aOneTwoThree( (sal_Char *)pOneTwoThreeUTF8,
                           SAL_N_ELEMENTS( pOneTwoThreeUTF8 ) - 1,
                           RTL_TEXTENCODING_UTF8 );
    Window* pWin = new WorkWindow( (Window *)NULL );

    OutputDevice *pOutDev = static_cast< OutputDevice * >( pWin );

    Font aFont = OutputDevice::GetDefaultFont(
                        DEFAULTFONT_CTL_SPREADSHEET,
                        LANGUAGE_ARABIC_SAUDI_ARABIA,
                        DEFAULTFONT_FLAGS_ONLYONE, 0 );
    pOutDev->SetFont( aFont );

    // normal orientation
    Rectangle aInput;
    Rectangle aRect = pOutDev->GetTextRect( aInput, aOneTwoThree );

    // now rotate 270 degress
    Font aRotated( aFont );
    aRotated.SetOrientation( 2700 );
    pOutDev->SetFont( aRotated );
    Rectangle aRectRot = pOutDev->GetTextRect( aInput, aOneTwoThree );

    (void)aRect; (void)aRectRot;
}

extern "C" void vcl_1_test() {

   printf("start vcl_1_test - 1\n");
   VclComplexTextTest *t = new VclComplexTextTest();
   printf("start vcl_1_test - 2\n");
   t->testArabic();
   printf("start vcl_1_test - 3\n");
  
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
