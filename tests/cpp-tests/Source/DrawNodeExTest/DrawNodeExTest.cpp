/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "DrawNodeExTest.h"
#include "renderer/Renderer.h"
#include "renderer/CustomCommand.h"

#include "clipper2/clipper.h"
#include "base/any_buffer.h"

USING_NS_AX;
USING_NS_AX_EXT;

using namespace std;
using namespace Clipper2Lib;



DrawNodeExTests::DrawNodeExTests()
{
    ADD_TEST_CASE(DrawNodePart1Test);
    ADD_TEST_CASE(DrawNodePart2Test);
    ADD_TEST_CASE(DrawNode2Test);
    ADD_TEST_CASE(IndividualThicknessTest);
    ADD_TEST_CASE(DrawPieTest);
    ADD_TEST_CASE(DrawNode2PolygonTest);
    ADD_TEST_CASE(DrawNode2FilledPolygonTest);
}

Vec2* DrawNodeExBaseTest::makePolygons()
{
    bool isReal = false;
    do
    {
        PathsD solution, clip, subject;
        PathD p, c;
        for (int i = 0; i < 5; i++)
        {
            p.push_back(PointD(200 + AXRANDOM_0_1() * VisibleRect::rightTop().x - 300,
                               200 + AXRANDOM_0_1() * VisibleRect::rightTop().y - 300));
            c.push_back(PointD(200 + AXRANDOM_0_1() * VisibleRect::rightTop().x - 300,
                               200 + AXRANDOM_0_1() * VisibleRect::rightTop().y - 300));
        }
        subject.push_back(p);
        clip.push_back(c);
        solution = Intersect(subject, clip, FillRule::EvenOdd);

        if (solution.size() > 0)
        {

            int verCount = 0;
            ax::any_buffer myBuf;
            for (auto&& p : solution)
            {
                int i          = 0;
                verCount       = p.size();
                Vec2* vertices = myBuf.get<Vec2>(verCount);
                for (auto&& pt : p)
                {
                    vertices[i] = Vec2(pt.x * 2, pt.y * 2);
                    i++;
                }
                if (verCount > 4)
                {
                    isReal = true;
                    // draw->drawPoly(vertices, verCount, true,
                    //                Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f), thickness);
                    return vertices;
                }
            }
        }
    } while (!isReal);
}

string DrawNodeExBaseTest::title() const
{
    return "No title";
}

// DrawNodeTest
DrawNode2Test::DrawNode2Test()
{
    auto s = Director::getInstance()->getWinSize();

    auto draw = DrawNodeEx::create();
    addChild(draw, 10);

    // draw->drawPoint(Vec2(s.width / 2 - 120, s.height / 2 - 120), 10,
    //                 Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1));

    // draw->drawPoint(Vec2(s.width / 2 + 120, s.height / 2 + 120), 10,
    //                 Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1));

    //// draw 4 small points
    // Vec2 position[] = {Vec2(60, 60), Vec2(70, 70), Vec2(60, 70), Vec2(70, 60)};
    // draw->drawPoints(position, 4, 5, Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1));

    float thickness = 1.0f;

    //// draw a line
    draw->drawLine(Vec2(200, 200), Vec2(s.width - 200, s.height - 200), Color4F(1.0, 0.0, 0.0, 1.0), thickness);
    draw->drawLine(Vec2(300, 3200), Vec2(s.width - 200, s.height - 200), Color4F(1.0, 1.0, 0.0, 1.0), thickness);

    // draw a rectangle
    draw->drawRect(Vec2(23, 23), Vec2(7, 7), Color4F(1, 1, 0, 1), thickness);

    draw->drawRect(Vec2(15, 30), Vec2(30, 15), Vec2(15, 0), Vec2(0, 15),
                   Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1), thickness);

    //// draw a circle
    // draw->drawCircle(VisibleRect::center() + Vec2(140, 0), 100, AX_DEGREES_TO_RADIANS(90), 50, true, 1.0f, 2.0f,
    //                  Color4F(1.0f, 0.0f, 0.0f, 0.5f));

    // draw->drawCircle(VisibleRect::center() - Vec2(140, 0), 50, AX_DEGREES_TO_RADIANS(90), 30, false,
    //                  Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f),80);

    // draw->setOpacity(50);

    // Draw some beziers
    draw->drawQuadBezier(Vec2(s.width - 150, s.height - 150), Vec2(s.width - 70, s.height - 10),
                         Vec2(s.width - 10, s.height - 10), 10, Color4F::BLUE, thickness);

    draw->drawQuadBezier(Vec2(0.0f + 100, s.height - 100), Vec2(s.width / 2, s.height / 2),
                         Vec2(s.width - 100, s.height - 100), 50, Color4F::RED, thickness);

    draw->drawCubicBezier(VisibleRect::center(), Vec2(VisibleRect::center().x + 30, VisibleRect::center().y + 50),
                          Vec2(VisibleRect::center().x + 60, VisibleRect::center().y - 50), VisibleRect::right(), 100,
                          Color4F::WHITE, thickness);

    draw->drawCubicBezier(Vec2(s.width - 250, 40.0f), Vec2(s.width - 70, 100.0f), Vec2(s.width - 30, 250.0f),
                          Vec2(s.width - 10, s.height - 50), 10, Color4F::GRAY, thickness);

    auto array = ax::PointArray::create(20);
    array->addControlPoint(Vec2(0.0f, 0.0f));
    array->addControlPoint(Vec2(80.0f, 80.0f));
    array->addControlPoint(Vec2(s.width - 80, 80.0f));
    array->addControlPoint(Vec2(s.width - 80, s.height - 80));
    array->addControlPoint(Vec2(80.0f, s.height - 80));
    array->addControlPoint(Vec2(80.0f, 80.0f));
    array->addControlPoint(Vec2(s.width / 2, s.height / 2));
    draw->drawCardinalSpline(array, 0.5f, 50, Color4F::MAGENTA, thickness);

    auto array2 = ax::PointArray::create(20);
    array2->addControlPoint(Vec2(s.width / 2, 30.0f));
    array2->addControlPoint(Vec2(s.width - 80, 30.0f));
    array2->addControlPoint(Vec2(s.width - 80, s.height - 80));
    array2->addControlPoint(Vec2(s.width / 2, s.height - 80));
    array2->addControlPoint(Vec2(s.width / 2, 30.0f));
    draw->drawCatmullRom(array2, 50, Color4F::ORANGE, thickness);

    //// open random color poly
    // Vec2 vertices[] = {Vec2(0.0f, 0.0f), Vec2(50.0f, 50.0f), Vec2(100.0f, 50.0f), Vec2(100.0f, 100.0f),
    //                    Vec2(50.0f, 100.0f)};
    // draw->drawPoly(vertices, 5, false, Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f));

    //// closed random color poly
    // Vec2 vertices2[] = {Vec2(30.0f, 130.0f), Vec2(30.0f, 230.0f), Vec2(50.0f, 200.0f)};
    // draw->drawPoly(vertices2, 3, true, Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f));

    //// Draw 10 circles
    // for (int i = 0; i < 10; i++)
    //{
    //     draw->drawDot(Vec2(s.width / 2, s.height / 2), 10.f * (10 - i),
    //                   Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f));
    // }

    //// Draw polygons
    // Vec2 points[] = {Vec2(s.height / 4, 0.0f), Vec2(s.width, s.height / 5), Vec2(s.width / 3 * 2, s.height)};
    // draw->drawPolygon(points, sizeof(points) / sizeof(points[0]), Color4F(1.0f, 0.0f, 0.0f, 0.5f), 4,
    //                   Color4F(0.0f, 0.0f, 1.0f, 0.5f));

    //// star poly (triggers buggs)
    //{
    //    const float o = 80;
    //    const float w = 20;
    //    const float h = 50;
    //    Vec2 star[]   = {
    //        Vec2(o + w, o - h), Vec2(o + w * 2, o),                  // lower spike
    //        Vec2(o + w * 2 + h, o + w), Vec2(o + w * 2, o + w * 2),  // right spike
    //        //              {o +w, o+w*2+h}, {o,o+w*2},                 // top spike
    //        //              {o -h, o+w}, {o,o},                         // left spike
    //    };

    //    draw->drawPolygon(star, sizeof(star) / sizeof(star[0]), Color4F(1.0f, 0.0f, 0.0f, 0.5f), 1,
    //                      Color4F(0.0f, 0.0f, 1.0f, 1.0f));
    //}

    //// star poly (doesn't trigger bug... order is important un tesselation is supported.
    //{
    //    const float o = 180;
    //    const float w = 20;
    //    const float h = 50;
    //    Vec2 star[]   = {
    //        Vec2(o, o),
    //        Vec2(o + w, o - h),
    //        Vec2(o + w * 2, o),  // lower spike
    //        Vec2(o + w * 2 + h, o + w),
    //        Vec2(o + w * 2, o + w * 2),  // right spike
    //        Vec2(o + w, o + w * 2 + h),
    //        Vec2(o, o + w * 2),  // top spike
    //        Vec2(o - h, o + w),  // left spike
    //    };

    //    draw->drawPolygon(star, sizeof(star) / sizeof(star[0]), Color4F(1.0f, 0.0f, 0.0f, 0.5f), 1,
    //                      Color4F(0.0f, 0.0f, 1.0f, 1.0f));
    //}

    //// draw a solid polygon
    // Vec2 vertices3[] = {Vec2(60.0f, 160.0f), Vec2(70.0f, 190.0f), Vec2(100.0f, 190.0f), Vec2(90.0f, 160.0f)};
    // draw->drawSolidPoly(vertices3, 4, Color4F(1.0f, 1.0f, 0.0f, 1.0f));

    //// draw a solid rectangle
    // draw->drawSolidRect(Vec2(10.0f, 10.0f), Vec2(20.0f, 20.0f), Color4F(1.0f, 1.0f, 0.0f, 1.0f));

    //// draw a solid circle
    // draw->drawSolidCircle(VisibleRect::center() + Vec2(140.0f, 0.0f), 40, AX_DEGREES_TO_RADIANS(90), 50, 2.0f, 2.0f,
    //                       Color4F(0.0f, 1.0f, 0.0f, 1.0f));

    //// Draw segment
    // draw->drawSegment(Vec2(20.0f, s.height), Vec2(20.0f, s.height / 2), 10, Color4F(0.0f, 1.0f, 0.0f, 1.0f));

    // draw->drawSegment(Vec2(10.0f, s.height / 2), Vec2(s.width / 2, s.height / 2), 40, Color4F(1.0f, 0.0f, 1.0f,
    // 0.5f));

    //// Draw triangle
    // draw->drawTriangle(Vec2(10.0f, 10.0f), Vec2(70.0f, 30.0f), Vec2(100.0f, 140.0f),
    //                    Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 0.5f));

    // for (int i = 0; i < 100; i++)
    //{
    //     draw->drawPoint(Vec2(i * 7.0f, 5.0f), (float)i / 5 + 1,
    //                     Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f));
    // }

    auto draw1 = DrawNodeEx::create();
    this->addChild(draw1, 10);
    // draw1->setLineWidth(4);
    draw1->drawLine(Vec2(0.0f, s.height), Vec2(s.width, s.height - 20), Color4F::YELLOW);
    draw1->drawLine(Vec2(0.0f, 0.0f), Vec2(s.width, s.height - 20), Color4F::YELLOW);

    //  draw->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.2f), FadeOut::create(1.2f), NULL)));
    // draw1->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.2f), FadeOut::create(1.2f), NULL)));
}

string DrawNode2Test::title() const
{
    return "Test DrawNodeExt";
}

string DrawNode2Test::subtitle() const
{
    return "Testing DrawNodeExt - batched draws.";
}

//
//
//
IndividualThicknessTest::IndividualThicknessTest()
{
    // Add lines to see the correct "scale of the 'rings'" changing the window size

    auto draw = DrawNodeEx::create();
    draw->setLineWidth(1);
    addChild(draw, 10);

    for (float y = 0; y < VisibleRect::top().y; y += 10)
    {
        draw->drawLine({VisibleRect::left().x, y}, {VisibleRect::right().x, y}, Color4B::GRAY);
    }
    initSliders();

    drawNode = DrawNodeEx::create();
    addChild(drawNode, 10);

    auto s = Director::getInstance()->getWinSize();
    // auto draw1 = DrawNodeExt::create();
    // this->addChild(draw1, 10);
    //// draw1->setLineWidth(4);
    // draw1->drawLine(Vec2(0.0f, s.height), Vec2(s.width, s.height - 20), Color4F::YELLOW);
    // draw1->drawLine(Vec2(0.0f, 0.0f), Vec2(s.width, s.height - 20), Color4F::YELLOW);

    scheduleUpdate();
}

void IndividualThicknessTest::changeThickness(ax::Ref* pSender, ax::ui::Slider::EventType type)
{
    if (type == ax::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ax::ui::Slider* sliderthickness = dynamic_cast<ax::ui::Slider*>(pSender);
        thickness                       = static_cast<float>(sliderthickness->getPercent()) / 10.0f;
        _thicknessLabel->setString("Thickness " + Value(thickness).asString());
    }
}

void IndividualThicknessTest::initSliders()
{

    // Layer => LayerRadialGradientTest   ############################################# Peter Eismann

    auto vsize             = Director::getInstance()->getVisibleSize();
    ax::ui::Slider* slider = ax::ui::Slider::create();
    slider->setPercent(0);
    slider->loadBarTexture("cocosui/sliderTrack.png");
    slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider->setPosition(Vec2(vsize.width / 2, vsize.height / 6));

    slider->addEventListener(AX_CALLBACK_2(IndividualThicknessTest::changeThickness, this));

    auto ttfConfig  = TTFConfig("fonts/arial.ttf", 8);
    _thicknessLabel = Label::createWithTTF(ttfConfig, "Thickness ");
    addChild(_thicknessLabel, 20);
    _thicknessLabel->setPosition(Vec2(vsize.width / 2, vsize.height / 6 + 15));

    addChild(slider, 20);
}

void IndividualThicknessTest::update(float dt)
{
    auto s = Director::getInstance()->getWinSize();

    drawNode->clear();
    auto color = Color4F::GREEN;
    drawNode->drawCircle(VisibleRect::center() /*- Vec2(120.0f, 0.0f)*/, 60, AX_DEGREES_TO_RADIANS(77), 36, false,
                         color, thickness);

    // drawNode->drawCircle(VisibleRect::center() /*- Vec2(120.0f, 0.0f)*/, 60, AX_DEGREES_TO_RADIANS(77), 36, false,
    //                      Color4F::BLACK, 1);

    // drawNode->drawLine(Vec2(0.0f, s.height), Vec2(s.width, s.height - 20), Color4F::YELLOW, thickness);
    // drawNode->drawLine(Vec2(0.0f, 0.0f), Vec2(s.width, s.height - 20), Color4F::YELLOW, thickness);

    // draw a rectangles
    drawNode->drawRect(Vec2(123, 123), Vec2(227, 227), Color4F(1, 1, 0, 1), thickness);
    // drawNode->drawRect(Vec2(123, 123), Vec2(227, 227), Color4F::BLACK, 1);

    drawNode->drawRect(Vec2(115, 130), Vec2(130, 115), Vec2(115, 100), Vec2(100, 115), Color4F::MAGENTA, thickness);
    // drawNode->drawRect(Vec2(115, 130), Vec2(130, 115), Vec2(115, 100), Vec2(100, 115), Color4F::BLACK, 1);

    drawNode->drawLine(Vec2(200.0f, s.height - 20), Vec2(s.width - 100, s.height - 20), Color4F::YELLOW, thickness);
    drawNode->drawLine(Vec2(300.0f, 100.0f), Vec2(s.width - 200, s.height - 120), Color4F::GREEN, thickness);

    Vec2 vertices24[] = {
        {45.750000f, 144.375000f},  {75.500000f, 136.875000f},  {75.500000f, 159.125000f},  {100.250000f, 161.375000f},
        {65.500000f, 181.375000f},  {102.250000f, 179.125000f}, {95.000000f, 215.125000f},  {129.331467f, 189.926208f},
        {131.371460f, 206.366196f}, {139.651474f, 192.446198f}, {161.851471f, 200.606201f}, {151.000000f, 220.375000f},
        {110.500000f, 244.375000f}, {153.750000f, 238.125000f}, {142.500000f, 253.875000f}, {220.750000f, 259.375000f},
        {250.500000f, 244.375000f}, {168.750000f, 241.875000f}, {182.250000f, 154.125000f}, {190.250000f, 227.375000f},
        {196.500000f, 197.375000f}, {208.750000f, 210.625000f}, {220.750000f, 194.375000f}, {208.750000f, 176.375000f},
        {253.250000f, 173.875000f}, {243.750000f, 154.125000f}, {213.750000f, 161.375000f}, {202.250000f, 139.875000f},
        {236.000000f, 131.875000f}, {218.500000f, 120.875000f}, {206.500000f, 125.625000f}, {184.500000f, 110.375000f},
        {157.000000f, 108.625000f}, {147.500000f, 96.625000f},  {153.750000f, 85.125000f},  {147.500000f, 75.375000f},
        {126.500000f, 74.125000f},  {110.500000f, 86.625000f},  {127.750000f, 85.125000f},  {135.250000f, 91.125000f},
        {135.250000f, 97.875000f},  {124.000000f, 93.875000f},  {115.500000f, 100.875000f}, {115.500000f, 111.875000f},
        {135.250000f, 108.625000f}, {151.000000f, 124.125000f}, {90.500000f, 131.875000f},  {113.250000f, 120.875000f},
        {88.000000f, 116.875000f},  {106.000000f, 103.875000f}, {88.000000f, 97.875000f},
    };
    drawNode->drawPolygon(vertices24, sizeof(vertices24) / sizeof(vertices24[0]), Color4B::AX_TRANSPARENT, thickness,
                          Color4F::RED);
    // drawNode->drawPolygon(vertices24, sizeof(vertices24) / sizeof(vertices24[0]), Color4B::AX_TRANSPARENT, 0.5f,
    //                       Color4F::BLACK);

    // open random color poly
    Vec2 vertices[] = {Vec2(0.0f, 0.0f), Vec2(50.0f, 50.0f), Vec2(100.0f, 50.0f), Vec2(100.0f, 100.0f),
                       Vec2(50.0f, 100.0f)};
    drawNode->drawPoly(vertices, 5, false, Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f), thickness);

    // closed random color poly
    Vec2 vertices2[] = {Vec2(30.0f, 130.0f), Vec2(30.0f, 230.0f), Vec2(50.0f, 200.0f)};
    drawNode->drawPoly(vertices2, 3, true, Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f), thickness);

    // Draw some beziers
    // Draw some beziers
    drawNode->drawQuadBezier(Vec2(s.width - 150, s.height - 150), Vec2(s.width - 70, s.height - 10),
                             Vec2(s.width - 10, s.height - 10), 10, Color4F::BLUE, thickness);

    drawNode->drawQuadBezier(Vec2(0.0f + 100, s.height - 100), Vec2(s.width / 2, s.height / 2),
                             Vec2(s.width - 100, s.height - 100), 50, Color4F::RED, thickness);

    drawNode->drawCubicBezier(VisibleRect::center(), Vec2(VisibleRect::center().x + 30, VisibleRect::center().y + 50),
                              Vec2(VisibleRect::center().x + 60, VisibleRect::center().y - 50), VisibleRect::right(),
                              100, Color4F::WHITE, thickness);

    drawNode->drawCubicBezier(Vec2(s.width - 250, 40.0f), Vec2(s.width - 70, 100.0f), Vec2(s.width - 30, 250.0f),
                              Vec2(s.width - 10, s.height - 50), 10, Color4F::GRAY, thickness);

    auto array = ax::PointArray::create(20);
    array->addControlPoint(Vec2(0.0f, 0.0f));
    array->addControlPoint(Vec2(80.0f, 80.0f));
    array->addControlPoint(Vec2(s.width - 80, 80.0f));
    array->addControlPoint(Vec2(s.width - 80, s.height - 80));
    array->addControlPoint(Vec2(80.0f, s.height - 80));
    array->addControlPoint(Vec2(80.0f, 80.0f));
    array->addControlPoint(Vec2(s.width / 2, s.height / 2));
    drawNode->drawCardinalSpline(array, 0.5f, 50, Color4F::MAGENTA, thickness);

    auto array2 = ax::PointArray::create(20);
    array2->addControlPoint(Vec2(s.width / 2, 30.0f));
    array2->addControlPoint(Vec2(s.width - 80, 30.0f));
    array2->addControlPoint(Vec2(s.width - 80, s.height - 80));
    array2->addControlPoint(Vec2(s.width / 2, s.height - 80));
    array2->addControlPoint(Vec2(s.width / 2, 30.0f));
    drawNode->drawCatmullRom(array2, 50, Color4F::ORANGE, thickness);
}

string IndividualThicknessTest::title() const
{
    return "Individual Thickness";
}

string IndividualThicknessTest::subtitle() const
{
    return "";
}

DrawPieTest::DrawPieTest()
{
    drawNode = DrawNodeEx::create();
    addChild(drawNode, 10);

    initSliders();

    scheduleUpdate();
}

void DrawPieTest::changeEndAngle(ax::Ref* pSender, ax::ui::Slider::EventType type)
{
    if (type == ax::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ax::ui::Slider* sEndAngle = dynamic_cast<ax::ui::Slider*>(pSender);
        endAngle                  = sEndAngle->getPercent() * 3.6;
        _EndAngleLabel->setString("endAngle: (" + Value(endAngle).asString() + ")");
    }
}

void DrawPieTest::changeStartAngle(ax::Ref* pSender, ax::ui::Slider::EventType type)
{
    if (type == ax::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ax::ui::Slider* sStartAngle = dynamic_cast<ax::ui::Slider*>(pSender);
        startAngle                  = sStartAngle->getPercent() * 3.6;
        _StartAngleLabel->setString("startAngle: (" + Value(startAngle).asString() + ")");
    }
}

void DrawPieTest::changeRotation(ax::Ref* pSender, ax::ui::Slider::EventType type)
{
    if (type == ax::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ax::ui::Slider* sStartAngle = dynamic_cast<ax::ui::Slider*>(pSender);
        rotation                    = sStartAngle->getPercent() * 3.6;
        _RotationLabel->setString("Rotation: (" + Value(rotation).asString() + ")");
    }
}

void DrawPieTest::changeThickness(ax::Ref* pSender, ax::ui::Slider::EventType type)
{
    if (type == ax::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ax::ui::Slider* sStartAngle = dynamic_cast<ax::ui::Slider*>(pSender);
        thickness                   = sStartAngle->getPercent() * 0.1;
        _ThicknessLabel->setString("Thickness: (" + Value(thickness).asString() + ")");
    }
}

void DrawPieTest::initSliders()
{
    rotation   = 324;
    endAngle   = 30;
    startAngle = 0;
    thickness  = 1;

    auto vsize                       = Director::getInstance()->getVisibleSize();
    ax::ui::Slider* sliderStartAngle = ax::ui::Slider::create();
    sliderStartAngle->setPercent(startAngle);
    sliderStartAngle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    sliderStartAngle->loadBarTexture("cocosui/sliderTrack.png");
    sliderStartAngle->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    sliderStartAngle->loadProgressBarTexture("cocosui/sliderProgress.png");
    sliderStartAngle->setPosition(Vec2(20, vsize.height / 6));

    sliderStartAngle->addEventListener(AX_CALLBACK_2(DrawPieTest::changeStartAngle, this));

    auto ttfConfig   = TTFConfig("fonts/arial.ttf", 8);
    _StartAngleLabel = Label::createWithTTF(ttfConfig, "StartAngle (" + Value(startAngle).asString() + ")");
    _StartAngleLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    addChild(_StartAngleLabel, 20);
    _StartAngleLabel->setPosition(sliderStartAngle->getPosition() + Vec2(sliderStartAngle->getContentSize().x + 20, 0));

    addChild(sliderStartAngle, 20);

    ax::ui::Slider* sliderEndAngle = ax::ui::Slider::create();
    sliderEndAngle->setPercent(endAngle);
    sliderEndAngle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    sliderEndAngle->loadBarTexture("cocosui/sliderTrack.png");
    sliderEndAngle->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    sliderEndAngle->loadProgressBarTexture("cocosui/sliderProgress.png");
    sliderEndAngle->setPosition(Vec2(20, vsize.height / 6 + 25));
    sliderEndAngle->addEventListener(AX_CALLBACK_2(DrawPieTest::changeEndAngle, this));

    _EndAngleLabel = Label::createWithTTF(ttfConfig, "endAngle (" + Value(endAngle).asString() + ")");
    _EndAngleLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    addChild(_EndAngleLabel, 20);
    _EndAngleLabel->setPosition(sliderEndAngle->getPosition() + Vec2(sliderEndAngle->getContentSize().x + 20, 0));
    addChild(sliderEndAngle, 20);

    ax::ui::Slider* sliderRotation = ax::ui::Slider::create();
    sliderRotation->setPercent(rotation);
    sliderRotation->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    sliderRotation->loadBarTexture("cocosui/sliderTrack.png");
    sliderRotation->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    sliderRotation->loadProgressBarTexture("cocosui/sliderProgress.png");
    sliderRotation->setPosition(Vec2(20, vsize.height / 6 + 50));
    sliderRotation->addEventListener(AX_CALLBACK_2(DrawPieTest::changeRotation, this));

    _RotationLabel = Label::createWithTTF(ttfConfig, "Rotation (" + Value(rotation).asString() + ")");
    _RotationLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    addChild(_RotationLabel, 20);
    _RotationLabel->setPosition(sliderRotation->getPosition() + Vec2(sliderRotation->getContentSize().x + 20, 0));
    addChild(sliderRotation, 20);

    ax::ui::Slider* sliderThickness = ax::ui::Slider::create();
    sliderThickness->setPercent(thickness);
    sliderThickness->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    sliderThickness->loadBarTexture("cocosui/sliderTrack.png");
    sliderThickness->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    sliderThickness->loadProgressBarTexture("cocosui/sliderProgress.png");
    sliderThickness->setPosition(Vec2(20, vsize.height / 6 + 75));
    sliderThickness->addEventListener(AX_CALLBACK_2(DrawPieTest::changeThickness, this));

    _ThicknessLabel = Label::createWithTTF(ttfConfig, "Thickness (" + Value(thickness).asString() + ")");
    _ThicknessLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    addChild(_ThicknessLabel, 20);
    _ThicknessLabel->setPosition(sliderThickness->getPosition() + Vec2(sliderThickness->getContentSize().x + 20, 0));
    addChild(sliderThickness, 20);
}

void DrawPieTest::update(float dt)
{
    drawNode->clear();
    drawNode->drawPie(VisibleRect::center() - Vec2(170.0f, -35.0f), 50, rotation, startAngle, endAngle, 1.0f, 1.0f,
                      Color4F::RED, Color4F::BLUE, drawNode->DrawMode::Fill, thickness);
    drawNode->drawPie(VisibleRect::center() - Vec2(60.0f, -35.0f), 50, rotation, startAngle, endAngle, 1.0f, 1.0f,
                      Color4F::AX_TRANSPARENT, Color4F::BLUE, drawNode->DrawMode::Outline, thickness);
    drawNode->drawPie(VisibleRect::center() + Vec2(60.0f, 35.0f), 50, rotation, startAngle, endAngle, 1.0f, 1.0f,
                      Color4F::RED, Color4F::BLUE, drawNode->DrawMode::Line, thickness);
    drawNode->drawPie(VisibleRect::center() + Vec2(170.0f, 35.0f), 50, rotation, startAngle, endAngle, 1.0f, 1.0f,
                      Color4F::RED, Color4F::BLUE, drawNode->DrawMode::Semi, thickness);
}

string DrawPieTest::title() const
{
    return "DrawNodeExt::drawPie";
}

string DrawPieTest::subtitle() const
{
    return "Filled, Outlined, Line, Semi";
}

DrawNode2PolygonTest::DrawNode2PolygonTest()
{
    // Vec2 vertices0[] = {{50.0, 20.0}, {100.0, 0.0}, {80.0, 50.0}, {100.0, 100.0},
    //                     {50.0, 80.0}, {0.0, 100.0}, {20.0, 50.0}, {0, 0}};

    // Vec2 vertices4[] = {{362, 148}, {326, 241}, {295, 219}, {258, 88}, {440, 129},
    //                     {370, 196}, {372, 275}, {348, 257}, {364, 148}};

    // Vec2* ver[] = {vertices0, vertices4};

    // DrawNodeExt* drawNode[sizeof(ver) + 1];
    // for (int i = 0; i < sizeof(ver); i++)
    //{
    //     drawNode[i] = DrawNodeExt::create();
    //     addChild(drawNode[i]);
    // }

    // drawNode[0]->drawPolygon(vertices0, sizeof(vertices0) / sizeof(vertices0[0]), Color4F(0.0f, 0.0f, 0.7f, 0.5f), 3,
    //                          Color4F(0.0f, 0.0f, 1.0f, 1.0f));
    // drawNode[0]->setPosition({20, 200});
    // drawDirection(vertices0, sizeof(vertices0) / sizeof(vertices0[0]), drawNode[0]->getPosition());

    // drawNode[4]->drawPolygon(vertices4, sizeof(vertices4) / sizeof(vertices4[0]), Color4F(0.0f, 0.0f, 0.7f, 0.5f), 3,
    //                          Color4F(0.0f, 0.0f, 1.0f, 1.0f));
    // drawNode[4]->setPosition({-70, -20});
    // drawDirection(vertices4, sizeof(vertices4) / sizeof(vertices4[0]), drawNode[4]->getPosition());

    {
        float o = 80;
        float w = 20;
        float h = 50;

        //{  // star
        //    auto drawNode1 = DrawNodeExt::create();
        //    addChild(drawNode1);
        //    drawNode1->setPosition(300, 100);
        //    Vec2 star[] = {
        //        Vec2(o, o),
        //        Vec2(o + w, o - h),
        //        Vec2(o + w * 2, o),  // lower spike
        //        Vec2(o + w * 2 + h, o + w),
        //        Vec2(o + w * 2, o + w * 2),  // right spike
        //        Vec2(o + w, o + w * 2 + h),
        //        Vec2(o, o + w * 2),  // top spike
        //        Vec2(o - h, o + w),  // left spike
        //    };

        //    drawNode1->drawPolygon(star, sizeof(star) / sizeof(star[0]), Color4F(0.0f, 0.0f, 0.7f, 0.5f), 1,
        //                           Color4F(0.0f, 0.0f, 1.0f, 1.0f));

        //    drawDirection(star, sizeof(star) / sizeof(star[0]), drawNode1->getPosition());
        //}

        {  // wrong order
            auto drawNode1 = DrawNodeEx::create();
            addChild(drawNode1);
            drawNode1->setPosition(-40, 20);

            int x = 0;
            int y = 0;
            Vec2 vertices[4];
            drawNode1->setScale(0.5);
            Color4F color;
            for (int iy = 0; iy < 5; iy++)
            {
                x = 0;
                for (int ix = 0; ix < 13; ix++)
                {
                    vertices[0] = Vec2(x + o + w, y + o - h);
                    vertices[1] = Vec2(x + o + w * 2, y + o);
                    vertices[2] = Vec2(x + o + w * 2 + h, y + o + w);
                    vertices[3] = Vec2(x + o + w * 2, y + o + w * 2);

                    if (AXRANDOM_0_1() > 0.5f)
                    {
                        drawNode1->setDNVersion(DrawNodeEx::Version::v1);
                        color = Color4F::YELLOW;
                    }
                    else
                    {
                        drawNode1->setDNVersion(DrawNodeEx::Version::v2);
                        color = Color4F::ORANGE;
                    }
                    drawNode1->drawPolygon(vertices, 4, Color4F(0.7f, 0.7f, 0.7f, 0.5f), 1, color);
                    x += 70;
                }
                y += 80;
            }
        }

        //{  // wrong order
        //    auto drawNode1 = DrawNodeExt::create();
        //    drawNode1->setDNVersion(DrawNodeExt::DrawNodeVersion::v1);
        //    addChild(drawNode1);
        //    drawNode1->setPosition(70, 20);
        //    Vec2 wrongOrder[] = {Vec2(o + w, o - h), Vec2(o + w * 2, o), Vec2(o + w * 2 + h, o + w),
        //                         Vec2(o + w * 2, o + w * 2)};

        //    drawNode1->drawPolygon(wrongOrder, sizeof(wrongOrder) / sizeof(wrongOrder[0]),
        //                           Color4F(0.0f, 0.0f, 0.7f, 0.5f), 1, Color4F::RED);
        //    drawDirection(wrongOrder, sizeof(wrongOrder) / sizeof(wrongOrder[0]), drawNode1->getPosition());
        //}

        //{  // correct order
        //    Vec2 correctOrder[] = {Vec2(o + w * 2, o), Vec2(o + w * 2 + h, o + w), Vec2(o + w * 2, o + w * 2),
        //                           Vec2(o + w, o - h)};
        //    auto drawNode2      = DrawNodeExt::create();
        //    drawNode2->setDNVersion(DrawNodeExt::DrawNodeVersion::v1);
        //    addChild(drawNode2);
        //    drawNode2->setPosition({-10, 20});
        //    drawNode2->drawPolygon(correctOrder, sizeof(correctOrder) / sizeof(correctOrder[0]),
        //                           Color4F(0.0f, 0.0f, 0.7f, 0.5f), 1, Color4F::GREEN);

        //    drawDirection(correctOrder, sizeof(correctOrder) / sizeof(correctOrder[0]), drawNode2->getPosition());
        //}
    }
}

void DrawNode2PolygonTest::drawDirection(const Vec2* vec, const int size, Vec2 offset)
{
    for (size_t i = 0; i < size; i++)
    {
        auto label = Label::createWithTTF(std::to_string(i).c_str(), "fonts/Marker Felt.ttf", 10);
        this->addChild(label);
        label->setPosition(vec[i] + offset);
    }
}

string DrawNode2PolygonTest::title() const
{
    return "DrawNodeExt::DrawNodeVersion";
}

string DrawNode2PolygonTest::subtitle() const
{
    return "YELLOW=v1 ORANGE=v2";
}

DrawNode2FilledPolygonTest::DrawNode2FilledPolygonTest()
{
    Vec2 vertices1[] = {
        {305.890625f, 204.082520f}, {305.834961f, 203.959229f}, {305.789062f, 203.841553f}, {305.755371f, 203.728516f},
        {305.735352f, 203.618164f}, {305.730957f, 203.508789f}, {305.745117f, 203.399414f}, {305.778320f, 203.288086f},
        {305.833496f, 203.173584f}, {305.912109f, 203.054443f}, {306.175293f, 202.782227f}, {306.441406f, 202.547852f},
        {306.708496f, 202.348389f}, {306.978516f, 202.180908f}, {307.250977f, 202.042480f}, {307.527344f, 201.930176f},
        {307.806641f, 201.841064f}, {308.090332f, 201.772217f}, {308.377930f, 201.720703f}, {308.524902f, 201.706299f},
        {308.656738f, 201.698730f}, {308.774902f, 201.695557f}, {308.881836f, 201.695312f}, {308.977051f, 201.695801f},
        {309.062988f, 201.695801f}, {309.141113f, 201.693115f}, {309.212402f, 201.686279f}, {309.278320f, 201.673340f},
        {309.464844f, 201.603760f}, {309.659180f, 201.539307f}, {309.853516f, 201.475342f}, {310.042969f, 201.406006f},
        {310.219727f, 201.324707f}, {310.379395f, 201.226562f}, {310.513672f, 201.105713f}, {310.617676f, 200.956299f},
        {310.684570f, 200.772461f}, {310.669922f, 200.526367f}, {310.615234f, 200.327148f}, {310.526367f, 200.168945f},
        {310.409668f, 200.046631f}, {310.270996f, 199.954834f}, {310.115234f, 199.887695f}, {309.948730f, 199.839844f},
        {309.777832f, 199.805420f}, {309.607422f, 199.779053f}, {309.453613f, 199.754883f}, {309.306152f, 199.727539f},
        {309.166992f, 199.694336f}, {309.039551f, 199.651367f}, {308.926758f, 199.595459f}, {308.829102f, 199.524414f},
        {308.750977f, 199.434082f}, {308.693359f, 199.321777f}, {308.660156f, 199.184082f}, {308.676270f, 198.985107f},
        {308.715820f, 198.816895f}, {308.774414f, 198.676025f}, {308.849609f, 198.559814f}, {308.937988f, 198.465332f},
        {309.035645f, 198.389404f}, {309.140625f, 198.328857f}, {309.248535f, 198.281250f}, {309.356934f, 198.243164f},
        {309.735352f, 198.155762f}, {310.109375f, 198.104004f}, {310.479980f, 198.078857f}, {310.847656f, 198.071045f},
        {311.212402f, 198.072754f}, {311.575195f, 198.074463f}, {311.935547f, 198.067627f}, {312.293945f, 198.043213f},
        {312.651855f, 197.992432f}, {313.232422f, 197.815918f}, {313.792969f, 197.630859f}, {314.334473f, 197.444824f},
        {314.862793f, 197.265137f}, {315.380371f, 197.099609f}, {315.890625f, 196.954590f}, {316.397461f, 196.838623f},
        {316.903809f, 196.758301f}, {317.413574f, 196.721436f}, {317.691406f, 196.719727f}, {317.931152f, 196.686523f},
        {318.134277f, 196.624512f}, {318.303711f, 196.536621f}, {318.440430f, 196.424805f}, {318.545410f, 196.292480f},
        {318.621582f, 196.142090f}, {318.670410f, 195.976318f}, {318.693359f, 195.798096f}, {318.669434f, 195.563232f},
        {318.624023f, 195.371582f}, {318.561035f, 195.218750f}, {318.480957f, 195.100342f}, {318.387207f, 195.012451f},
        {318.281250f, 194.951416f}, {318.166504f, 194.913086f}, {318.043945f, 194.892578f}, {317.916016f, 194.886963f},
        {317.769531f, 194.895752f}, {317.629883f, 194.906006f}, {317.496582f, 194.917480f}, {317.368652f, 194.930420f},
        {317.246094f, 194.944580f}, {317.126953f, 194.959717f}, {317.011719f, 194.976074f}, {316.898926f, 194.993652f},
        {316.787109f, 195.012207f}, {316.445801f, 195.069092f}, {316.115234f, 195.110352f}, {315.793945f, 195.132812f},
        {315.479980f, 195.133789f}, {315.172363f, 195.109375f}, {314.868652f, 195.056885f}, {314.568359f, 194.972656f},
        {314.270020f, 194.854248f}, {313.971191f, 194.697754f}, {313.591309f, 194.431396f}, {313.215332f, 194.177246f},
        {312.844238f, 193.939697f}, {312.478027f, 193.723633f}, {312.118652f, 193.534180f}, {311.765625f, 193.376465f},
        {311.421875f, 193.254395f}, {311.085938f, 193.173340f}, {310.760254f, 193.137939f}, {310.194336f, 193.207764f},
        {309.637695f, 193.283691f}, {309.094238f, 193.376709f}, {308.566895f, 193.496582f}, {308.058594f, 193.653564f},
        {307.573242f, 193.858398f}, {307.114258f, 194.120361f}, {306.685059f, 194.449951f}, {306.288574f, 194.857666f},
        {306.136230f, 195.078125f}, {306.003906f, 195.270752f}, {305.887695f, 195.439941f}, {305.787109f, 195.587646f},
        {305.698242f, 195.717529f}, {305.621094f, 195.832275f}, {305.551758f, 195.934326f}, {305.487793f, 196.027588f},
        {305.428711f, 196.114746f}, {305.317871f, 196.266113f}, {305.206055f, 196.402832f}, {305.091797f, 196.522217f},
        {304.974609f, 196.622559f}, {304.854492f, 196.702637f}, {304.731445f, 196.760742f}, {304.603516f, 196.794434f},
        {304.471191f, 196.802490f}, {304.333984f, 196.783203f}, {304.172363f, 196.698730f}, {304.043457f, 196.595947f},
        {303.944336f, 196.478271f}, {303.869629f, 196.348145f}, {303.814453f, 196.209229f}, {303.773926f, 196.064209f},
        {303.744141f, 195.915527f}, {303.718750f, 195.766846f}, {303.694824f, 195.620361f}, {303.673828f, 195.518311f},
        {303.659668f, 195.422363f}, {303.649902f, 195.332031f}, {303.644531f, 195.246094f}, {303.642578f, 195.165039f},
        {303.642578f, 195.087402f}, {303.643555f, 195.013184f}, {303.646484f, 194.941406f}, {303.648926f, 194.871582f},
        {303.656250f, 194.674805f}, {303.671875f, 194.469238f}, {303.690430f, 194.260254f}, {303.710938f, 194.053467f},
        {303.727539f, 193.854492f}, {303.737305f, 193.668945f}, {303.737305f, 193.502197f}, {303.722168f, 193.359375f},
        {303.689941f, 193.246338f}, {303.547363f, 193.125977f}, {303.395020f, 193.025146f}, {303.234863f, 192.942871f},
        {303.068848f, 192.876953f}, {302.897949f, 192.826660f}, {302.725098f, 192.789551f}, {302.551270f, 192.764160f},
        {302.378418f, 192.749023f}, {302.208008f, 192.742432f}, {301.778809f, 192.740234f}, {301.357422f, 192.725342f},
        {300.944336f, 192.708984f}, {300.538574f, 192.701172f}, {300.140137f, 192.713379f}, {299.749023f, 192.756348f},
        {299.364746f, 192.840332f}, {298.986328f, 192.976318f}, {298.614258f, 193.175293f}, {298.273438f, 193.423584f},
        {297.938965f, 193.608398f}, {297.610352f, 193.738037f}, {297.288086f, 193.820312f}, {296.972168f, 193.863770f},
        {296.663574f, 193.875977f}, {296.361328f, 193.865234f}, {296.066406f, 193.839355f}, {295.778809f, 193.806641f},
        {295.231934f, 193.772461f}, {294.711914f, 193.784424f}, {294.214844f, 193.839355f}, {293.738770f, 193.932861f},
        {293.280762f, 194.061523f}, {292.838379f, 194.221436f}, {292.408203f, 194.408691f}, {291.988281f, 194.619629f},
        {291.574707f, 194.850586f}, {291.403320f, 194.954346f}, {291.252930f, 195.044678f}, {291.123047f, 195.124512f},
        {291.012207f, 195.196777f}, {290.920410f, 195.264160f}, {290.846191f, 195.330078f}, {290.788086f, 195.396240f},
        {290.745605f, 195.466309f}, {290.717773f, 195.543213f}, {290.715820f, 195.662109f}, {290.729980f, 195.760742f},
        {290.758301f, 195.842529f}, {290.798828f, 195.909668f}, {290.848145f, 195.965088f}, {290.904297f, 196.011230f},
        {290.964844f, 196.051514f}, {291.026855f, 196.087891f}, {291.086914f, 196.123535f}, {291.170898f, 196.180908f},
        {291.252441f, 196.234131f}, {291.332520f, 196.283447f}, {291.410156f, 196.330322f}, {291.486328f, 196.375732f},
        {291.560547f, 196.420654f}, {291.632324f, 196.465576f}, {291.702148f, 196.511719f}, {291.770020f, 196.560059f},
        {291.819824f, 196.603760f}, {291.866699f, 196.649414f}, {291.909180f, 196.696289f}, {291.946289f, 196.744629f},
        {291.979492f, 196.793457f}, {292.007812f, 196.842773f}, {292.030273f, 196.891602f}, {292.047852f, 196.939941f},
        {292.059570f, 196.987061f}, {292.060059f, 197.056885f}, {292.050293f, 197.116699f}, {292.030762f, 197.167236f},
        {292.003906f, 197.209229f}, {291.970215f, 197.243408f}, {291.931152f, 197.270020f}, {291.889160f, 197.290527f},
        {291.842773f, 197.305176f}, {291.795898f, 197.314209f}, {291.500000f, 197.338623f}, {291.207520f, 197.366699f},
        {290.918945f, 197.389648f}, {290.635254f, 197.397461f}, {290.357422f, 197.380371f}, {290.086426f, 197.328369f},
        {289.822754f, 197.231934f}, {289.566406f, 197.081543f}, {289.319824f, 196.867188f}, {289.150391f, 196.635010f},
        {289.010742f, 196.428223f}, {288.902832f, 196.244141f}, {288.826172f, 196.078125f}, {288.781250f, 195.927246f},
        {288.769531f, 195.787109f}, {288.790039f, 195.654785f}, {288.843750f, 195.526611f}, {288.932129f, 195.398193f},
        {289.075684f, 195.242920f}, {289.193848f, 195.087646f}, {289.288574f, 194.931641f}, {289.361816f, 194.774658f},
        {289.415527f, 194.616455f}, {289.453125f, 194.457031f}, {289.476074f, 194.295898f}, {289.486328f, 194.132568f},
        {289.486328f, 193.967285f}, {289.494141f, 193.839844f}, {289.490723f, 193.730957f}, {289.477051f, 193.638672f},
        {289.454102f, 193.561035f}, {289.423828f, 193.496094f}, {289.386719f, 193.441650f}, {289.344238f, 193.395752f},
        {289.297363f, 193.356445f}, {289.248047f, 193.321289f}, {288.519043f, 193.154053f}, {287.794434f, 193.023438f},
        {287.074707f, 192.933594f}, {286.358887f, 192.888184f}, {285.647461f, 192.891357f}, {284.939453f, 192.947021f},
        {284.235352f, 193.059326f}, {283.534668f, 193.231445f}, {282.836426f, 193.468262f}, {282.314941f, 193.689209f},
        {281.824707f, 193.852051f}, {281.363770f, 193.966797f}, {280.928711f, 194.044922f}, {280.516602f, 194.096680f},
        {280.125488f, 194.132568f}, {279.752441f, 194.163818f}, {279.395020f, 194.200439f}, {279.049805f, 194.253418f},
        {278.381836f, 194.449707f}, {277.736816f, 194.645264f}, {277.109863f, 194.825928f}, {276.498047f, 194.979004f},
        {275.897461f, 195.091553f}, {275.304688f, 195.150146f}, {274.715332f, 195.141357f}, {274.126465f, 195.052734f},
        {273.533203f, 194.870850f}, {273.151855f, 194.694824f}, {272.792969f, 194.580566f}, {272.456055f, 194.522949f},
        {272.140137f, 194.516602f}, {271.844238f, 194.557129f}, {271.567383f, 194.638916f}, {271.308594f, 194.757080f},
        {271.066406f, 194.906738f}, {270.839844f, 195.082275f}, {270.684082f, 195.230469f}, {270.536621f, 195.361572f},
        {270.396484f, 195.476074f}, {270.262207f, 195.574707f}, {270.132324f, 195.657715f}, {270.006348f, 195.725098f},
        {269.881836f, 195.777588f}, {269.758301f, 195.815918f}, {269.633789f, 195.839355f}, {269.225586f, 195.882080f},
        {268.869629f, 195.982910f}, {268.563477f, 196.136475f}, {268.302246f, 196.337891f}, {268.083008f, 196.583008f},
        {267.902344f, 196.866211f}, {267.757324f, 197.183594f}, {267.644043f, 197.529541f}, {267.559570f, 197.899658f},
        {267.503418f, 198.256104f}, {267.437500f, 198.554443f}, {267.359375f, 198.799072f}, {267.269043f, 198.994873f},
        {267.165039f, 199.146729f}, {267.046387f, 199.259033f}, {266.912109f, 199.336670f}, {266.760742f, 199.384277f},
        {266.591797f, 199.406494f}, {266.395508f, 199.402100f}, {266.208984f, 199.398438f}, {266.030762f, 199.395996f},
        {265.861328f, 199.395752f}, {265.697754f, 199.398438f}, {265.540527f, 199.404541f}, {265.388184f, 199.414551f},
        {265.238770f, 199.429688f}, {265.092285f, 199.450684f}, {264.925293f, 199.489746f}, {264.771973f, 199.537354f},
        {264.630859f, 199.593750f}, {264.502930f, 199.660645f}, {264.386719f, 199.738525f}, {264.284180f, 199.827637f},
        {264.193359f, 199.929932f}, {264.116211f, 200.045654f}, {264.049805f, 200.175781f}, {263.997070f, 200.378418f},
        {263.973145f, 200.563232f}, {263.974121f, 200.732422f}, {263.997559f, 200.886963f}, {264.040039f, 201.029297f},
        {264.098145f, 201.161133f}, {264.169434f, 201.283936f}, {264.249512f, 201.399902f}, {264.336914f, 201.510498f},
        {264.701660f, 201.885986f}, {265.079590f, 202.179443f}, {265.467773f, 202.390381f}, {265.861328f, 202.520020f},
        {266.257324f, 202.568848f}, {266.651855f, 202.537842f}, {267.041016f, 202.427002f}, {267.420410f, 202.237549f},
        {267.787109f, 201.970215f}, {268.233398f, 201.529297f}, {268.676270f, 201.184082f}, {269.113281f, 200.932617f},
        {269.542480f, 200.773193f}, {269.960938f, 200.704346f}, {270.366699f, 200.724121f}, {270.756348f, 200.831055f},
        {271.128906f, 201.023193f}, {271.480469f, 201.298584f}, {271.678223f, 201.526367f}, {271.860840f, 201.724121f},
        {272.030273f, 201.893799f}, {272.188965f, 202.036621f}, {272.339844f, 202.155029f}, {272.485840f, 202.250000f},
        {272.628906f, 202.323242f}, {272.771484f, 202.376709f}, {272.916992f, 202.412354f}, {273.141113f, 202.439697f},
        {273.352539f, 202.482178f}, {273.551270f, 202.538574f}, {273.738770f, 202.608398f}, {273.916992f, 202.689941f},
        {274.085938f, 202.782715f}, {274.248535f, 202.885254f}, {274.405273f, 202.997314f}, {274.557617f, 203.116943f},
        {275.376465f, 203.208740f}, {276.188477f, 203.302734f}, {276.992676f, 203.387939f}, {277.791016f, 203.455322f},
        {278.583496f, 203.494629f}, {279.369629f, 203.496094f}, {280.151367f, 203.449951f}, {280.929199f, 203.345947f},
        {281.703125f, 203.174561f}, {281.956055f, 203.090088f}, {282.168457f, 203.018311f}, {282.343750f, 202.959229f},
        {282.486328f, 202.911865f}, {282.602051f, 202.876709f}, {282.692871f, 202.853271f}, {282.764648f, 202.840820f},
        {282.821777f, 202.839844f}, {282.868164f, 202.849121f}, {283.348633f, 203.116211f}, {283.833008f, 203.300537f},
        {284.320801f, 203.416016f}, {284.811035f, 203.476074f}, {285.303711f, 203.493896f}, {285.796387f, 203.482910f},
        {286.289551f, 203.456787f}, {286.781738f, 203.428467f}, {287.272461f, 203.411621f}, {287.908691f, 203.435303f},
        {288.520020f, 203.450439f}, {289.107422f, 203.458496f}, {289.674316f, 203.461182f}, {290.224121f, 203.459473f},
        {290.759766f, 203.455078f}, {291.283203f, 203.449707f}, {291.798340f, 203.444336f}, {292.307129f, 203.441162f},
        {292.692383f, 203.442139f}, {293.048828f, 203.440186f}, {293.379395f, 203.430664f}, {293.686523f, 203.409180f},
        {293.972656f, 203.371338f}, {294.238770f, 203.312256f}, {294.488281f, 203.227539f}, {294.723145f, 203.113037f},
        {294.946777f, 202.963623f}, {295.091797f, 202.837402f}, {295.229004f, 202.740967f}, {295.359375f, 202.671387f},
        {295.483398f, 202.624756f}, {295.601562f, 202.598877f}, {295.714355f, 202.590088f}, {295.823242f, 202.595215f},
        {295.928223f, 202.611572f}, {296.030762f, 202.635498f}, {296.245605f, 202.696533f}, {296.455566f, 202.748779f},
        {296.661621f, 202.791504f}, {296.863281f, 202.824219f}, {297.061035f, 202.845947f}, {297.256836f, 202.856445f},
        {297.450195f, 202.854980f}, {297.641602f, 202.840820f}, {297.832031f, 202.813721f}, {298.143066f, 202.754150f},
        {298.408203f, 202.740723f}, {298.628906f, 202.771973f}, {298.807617f, 202.845459f}, {298.948242f, 202.960205f},
        {299.052246f, 203.113770f}, {299.123047f, 203.305176f}, {299.162598f, 203.531982f}, {299.173340f, 203.793213f},
        {299.842773f, 203.872559f}, {300.513184f, 203.936035f}, {301.184082f, 203.985596f}, {301.855469f, 204.022949f},
        {302.527344f, 204.049805f}, {303.199707f, 204.067383f}, {303.872559f, 204.078369f}, {304.545898f, 204.083740f},
        {305.219238f, 204.085938f},
    };  // data size = 505

    Vec2 vertices2[] = {
        {47.014648f, 191.154297f},  {47.002930f, 191.477295f},  {47.031250f, 191.753418f},  {47.094727f, 191.984619f},
        {47.191406f, 192.172363f},  {47.316895f, 192.318848f},  {47.468262f, 192.425293f},  {47.641602f, 192.494141f},
        {47.833496f, 192.526855f},  {48.041016f, 192.524902f},  {48.824707f, 192.388672f},  {49.601562f, 192.312500f},
        {50.370117f, 192.277344f},  {51.131836f, 192.263184f},  {51.886230f, 192.250488f},  {52.632812f, 192.219727f},
        {53.372559f, 192.151123f},  {54.104980f, 192.025635f},  {54.830078f, 191.822998f},  {55.458496f, 191.556396f},
        {56.056152f, 191.357178f},  {56.625488f, 191.219971f},  {57.169922f, 191.138428f},  {57.691895f, 191.106689f},
        {58.195312f, 191.118652f},  {58.682129f, 191.168213f},  {59.154785f, 191.250000f},  {59.618164f, 191.357422f},
        {59.849121f, 191.426514f},  {60.053711f, 191.494629f},  {60.235352f, 191.563721f},  {60.393555f, 191.635498f},
        {60.530762f, 191.712402f},  {60.648438f, 191.796143f},  {60.749023f, 191.888916f},  {60.832520f, 191.993164f},
        {60.902344f, 192.110107f},  {60.939941f, 192.173096f},  {60.975098f, 192.229004f},  {61.006836f, 192.278564f},
        {61.036621f, 192.322510f},  {61.063965f, 192.361572f},  {61.090332f, 192.396973f},  {61.114746f, 192.428711f},
        {61.138672f, 192.458496f},  {61.161133f, 192.486816f},  {61.297852f, 192.679932f},  {61.429199f, 192.832764f},
        {61.557129f, 192.946289f},  {61.685547f, 193.019775f},  {61.816895f, 193.053223f},  {61.954102f, 193.047607f},
        {62.100098f, 193.002197f},  {62.256836f, 192.917480f},  {62.427734f, 192.793457f},  {62.896973f, 192.368408f},
        {63.362793f, 191.964111f},  {63.829590f, 191.587891f},  {64.300293f, 191.246582f},  {64.777344f, 190.947998f},
        {65.265137f, 190.698486f},  {65.765625f, 190.505615f},  {66.282227f, 190.376465f},  {66.818359f, 190.318115f},
        {67.003906f, 190.325439f},  {67.160156f, 190.328613f},  {67.290527f, 190.328613f},  {67.397461f, 190.327393f},
        {67.483887f, 190.325684f},  {67.553223f, 190.324707f},  {67.606934f, 190.326172f},  {67.649414f, 190.330566f},
        {67.682617f, 190.339844f},  {68.156250f, 190.619873f},  {68.625000f, 190.791748f},  {69.090332f, 190.870361f},
        {69.550293f, 190.870117f},  {70.006836f, 190.806152f},  {70.458496f, 190.693115f},  {70.906250f, 190.545410f},
        {71.349121f, 190.378174f},  {71.788574f, 190.206055f},  {72.229492f, 190.073242f},  {72.634277f, 189.998535f},
        {73.009277f, 189.972656f},  {73.357910f, 189.987549f},  {73.684082f, 190.034180f},  {73.993164f, 190.103516f},
        {74.289062f, 190.187012f},  {74.576660f, 190.276123f},  {74.859863f, 190.361572f},  {75.089844f, 190.438477f},
        {75.276367f, 190.546875f},  {75.424805f, 190.682373f},  {75.539062f, 190.840088f},  {75.625488f, 191.015381f},
        {75.689941f, 191.203857f},  {75.736328f, 191.401367f},  {75.771484f, 191.602783f},  {75.799805f, 191.803711f},
        {75.828613f, 192.025879f},  {75.854492f, 192.245361f},  {75.880371f, 192.458984f},  {75.910645f, 192.662598f},
        {75.950195f, 192.852539f},  {76.003418f, 193.025879f},  {76.073242f, 193.178467f},  {76.165039f, 193.306396f},
        {76.282715f, 193.406494f},  {76.455078f, 193.447021f},  {76.611816f, 193.446045f},  {76.755371f, 193.410645f},
        {76.887695f, 193.346924f},  {77.010742f, 193.260742f},  {77.125977f, 193.159180f},  {77.236816f, 193.048340f},
        {77.344238f, 192.934814f},  {77.450195f, 192.824707f},  {77.785645f, 192.519531f},  {78.105957f, 192.201416f},
        {78.416992f, 191.880127f},  {78.724121f, 191.563477f},  {79.033203f, 191.261230f},  {79.349121f, 190.981445f},
        {79.677734f, 190.732910f},  {80.024902f, 190.524658f},  {80.395996f, 190.364746f},  {80.552246f, 190.323486f},
        {80.686035f, 190.277832f},  {80.799316f, 190.228760f},  {80.895996f, 190.177246f},  {80.977051f, 190.124512f},
        {81.044922f, 190.071289f},  {81.103516f, 190.018799f},  {81.154785f, 189.968018f},  {81.200684f, 189.920166f},
        {81.471191f, 189.663086f},  {81.700684f, 189.465576f},  {81.896484f, 189.329346f},  {82.066406f, 189.255371f},
        {82.216797f, 189.245117f},  {82.355469f, 189.299316f},  {82.489258f, 189.419922f},  {82.625488f, 189.607910f},
        {82.770508f, 189.864258f},  {82.886230f, 190.096436f},  {82.996582f, 190.301758f},  {83.103516f, 190.482666f},
        {83.208496f, 190.640869f},  {83.313965f, 190.777588f},  {83.421387f, 190.895264f},  {83.533203f, 190.995605f},
        {83.651367f, 191.079834f},  {83.777832f, 191.150391f},  {84.356934f, 191.365479f},  {84.937500f, 191.567383f},
        {85.516113f, 191.749756f},  {86.090820f, 191.905762f},  {86.661133f, 192.029297f},  {87.223633f, 192.113037f},
        {87.777832f, 192.150635f},  {88.321777f, 192.135498f},  {88.852539f, 192.061035f},  {89.364258f, 191.907227f},
        {89.843262f, 191.785889f},  {90.292969f, 191.692383f},  {90.718750f, 191.621338f},  {91.122070f, 191.568848f},
        {91.509277f, 191.529785f},  {91.883301f, 191.499512f},  {92.248047f, 191.473145f},  {92.607910f, 191.445801f},
        {92.800293f, 191.419434f},  {92.966309f, 191.380615f},  {93.107422f, 191.331787f},  {93.229004f, 191.274414f},
        {93.333008f, 191.210693f},  {93.423340f, 191.141846f},  {93.502930f, 191.070068f},  {93.575684f, 190.997314f},
        {93.644043f, 190.924561f},  {93.905273f, 190.688232f},  {94.156738f, 190.510742f},  {94.398926f, 190.392090f},
        {94.633789f, 190.331055f},  {94.860840f, 190.327637f},  {95.081543f, 190.381592f},  {95.295410f, 190.492188f},
        {95.504883f, 190.658936f},  {95.709473f, 190.881348f},  {96.061035f, 191.409424f},  {96.356445f, 191.829590f},
        {96.610840f, 192.147217f},  {96.842773f, 192.368408f},  {97.067871f, 192.499756f},  {97.303711f, 192.546387f},
        {97.567871f, 192.514648f},  {97.875977f, 192.410400f},  {98.245605f, 192.239990f},  {98.704590f, 192.012695f},
        {99.134277f, 191.826660f},  {99.540039f, 191.681641f},  {99.926758f, 191.578369f},  {100.298828f, 191.515869f},
        {100.661133f, 191.494385f}, {101.017578f, 191.514160f}, {101.374023f, 191.574463f}, {101.733887f, 191.676025f},
        {102.099609f, 191.833496f}, {102.449219f, 191.991455f}, {102.783691f, 192.145508f}, {103.103516f, 192.292725f},
        {103.409180f, 192.429443f}, {103.702637f, 192.552490f}, {103.983398f, 192.657959f}, {104.252441f, 192.742920f},
        {104.510742f, 192.804199f}, {104.870605f, 192.835205f}, {105.233398f, 192.860107f}, {105.596191f, 192.871094f},
        {105.955078f, 192.858887f}, {106.306152f, 192.815918f}, {106.645508f, 192.733154f}, {106.969727f, 192.602783f},
        {107.275391f, 192.415771f}, {107.557129f, 192.164062f}, {107.672363f, 192.008545f}, {107.773926f, 191.874756f},
        {107.864746f, 191.762695f}, {107.946289f, 191.671875f}, {108.020996f, 191.603271f}, {108.090820f, 191.556396f},
        {108.158203f, 191.531250f}, {108.225098f, 191.527832f}, {108.293457f, 191.546631f}, {108.362793f, 191.596436f},
        {108.423828f, 191.649658f}, {108.474121f, 191.705566f}, {108.515625f, 191.764160f}, {108.546387f, 191.825195f},
        {108.567383f, 191.888672f}, {108.577148f, 191.954346f}, {108.576172f, 192.021729f}, {108.564453f, 192.091309f},
        {108.397461f, 192.595703f}, {108.345215f, 192.974365f}, {108.388184f, 193.244141f}, {108.506836f, 193.422363f},
        {108.682129f, 193.526611f}, {108.894043f, 193.574219f}, {109.122070f, 193.582275f}, {109.348633f, 193.568115f},
        {109.552734f, 193.549561f}, {110.361328f, 193.565186f}, {111.159180f, 193.551514f}, {111.946289f, 193.506836f},
        {112.724121f, 193.430420f}, {113.492188f, 193.321045f}, {114.251953f, 193.177734f}, {115.004395f, 193.000000f},
        {115.749023f, 192.785889f}, {116.487793f, 192.534912f}, {116.766113f, 192.417236f}, {116.996582f, 192.308350f},
        {117.185059f, 192.207275f}, {117.337891f, 192.113770f}, {117.459473f, 192.026855f}, {117.557129f, 191.946533f},
        {117.635254f, 191.872314f}, {117.700684f, 191.802734f}, {117.759277f, 191.738037f}, {117.855957f, 191.645508f},
        {117.951172f, 191.568848f}, {118.044434f, 191.510986f}, {118.132812f, 191.473877f}, {118.215820f, 191.460449f},
        {118.292480f, 191.472412f}, {118.359863f, 191.512939f}, {118.417969f, 191.584229f}, {118.464355f, 191.688721f},
        {118.572754f, 192.115723f}, {118.721680f, 192.445801f}, {118.902832f, 192.689941f}, {119.108887f, 192.858643f},
        {119.333008f, 192.962891f}, {119.566406f, 193.013184f}, {119.802246f, 193.020508f}, {120.032715f, 192.995850f},
        {120.249512f, 192.949463f}, {120.774414f, 192.786865f}, {121.285645f, 192.640381f}, {121.786133f, 192.513184f},
        {122.278809f, 192.409424f}, {122.763672f, 192.333740f}, {123.244629f, 192.289062f}, {123.722656f, 192.279541f},
        {124.199707f, 192.309082f}, {124.678223f, 192.381592f}, {124.958008f, 192.440918f}, {125.207031f, 192.460693f},
        {125.429688f, 192.448486f}, {125.629395f, 192.411621f}, {125.809082f, 192.357422f}, {125.974121f, 192.292480f},
        {126.125977f, 192.224365f}, {126.270020f, 192.160400f}, {126.409180f, 192.107666f}, {127.127441f, 192.003906f},
        {127.839844f, 191.935791f}, {128.545898f, 191.896729f}, {129.247070f, 191.881592f}, {129.942871f, 191.884277f},
        {130.635254f, 191.899658f}, {131.324219f, 191.921631f}, {132.011230f, 191.944580f}, {132.695801f, 191.963379f},
        {133.379883f, 191.971191f}, {133.435059f, 191.706055f}, {133.446777f, 191.474854f}, {133.418457f, 191.275391f},
        {133.356445f, 191.105957f}, {133.265137f, 190.965088f}, {133.149414f, 190.850830f}, {133.013672f, 190.761230f},
        {132.864258f, 190.694580f}, {132.704102f, 190.648926f}, {132.122559f, 190.591797f}, {131.549805f, 190.546875f},
        {130.983887f, 190.514893f}, {130.424805f, 190.495117f}, {129.872070f, 190.487305f}, {129.323242f, 190.491455f},
        {128.778809f, 190.507324f}, {128.237793f, 190.534912f}, {127.698242f, 190.573730f}, {127.463379f, 190.602539f},
        {127.260742f, 190.640869f}, {127.086914f, 190.686035f}, {126.938477f, 190.737793f}, {126.810059f, 190.793945f},
        {126.700684f, 190.854004f}, {126.604980f, 190.916260f}, {126.519043f, 190.979492f}, {126.439941f, 191.042236f},
        {126.095703f, 191.267578f}, {125.745117f, 191.406738f}, {125.396484f, 191.463867f}, {125.058594f, 191.442627f},
        {124.737793f, 191.347168f}, {124.442383f, 191.180664f}, {124.180664f, 190.947266f}, {123.960449f, 190.650635f},
        {123.790039f, 190.294434f}, {123.695801f, 189.897217f}, {123.594238f, 189.550293f}, {123.482422f, 189.253174f},
        {123.356934f, 189.005615f}, {123.216309f, 188.806885f}, {123.058105f, 188.656738f}, {122.879395f, 188.554688f},
        {122.678711f, 188.500000f}, {122.452148f, 188.492676f}, {122.236328f, 188.525146f}, {122.035156f, 188.534180f},
        {121.847656f, 188.525635f}, {121.671387f, 188.504883f}, {121.504883f, 188.477539f}, {121.345703f, 188.448975f},
        {121.192871f, 188.425293f}, {121.043457f, 188.411621f}, {120.896973f, 188.413330f}, {120.765137f, 188.444824f},
        {120.644043f, 188.480225f}, {120.533691f, 188.520752f}, {120.433594f, 188.567871f}, {120.344727f, 188.622314f},
        {120.266602f, 188.685059f}, {120.199707f, 188.757568f}, {120.142578f, 188.840576f}, {120.096191f, 188.935303f},
        {120.062500f, 189.093018f}, {120.052246f, 189.229736f}, {120.063477f, 189.347412f}, {120.093262f, 189.448730f},
        {120.138672f, 189.535889f}, {120.196777f, 189.611572f}, {120.265625f, 189.678467f}, {120.340820f, 189.738525f},
        {120.421387f, 189.794189f}, {120.541504f, 189.864258f}, {120.669922f, 189.925049f}, {120.798828f, 189.982178f},
        {120.922852f, 190.039551f}, {121.035156f, 190.102295f}, {121.130859f, 190.174805f}, {121.201660f, 190.261719f},
        {121.242676f, 190.367920f}, {121.246582f, 190.497559f}, {121.160156f, 190.717529f}, {121.057129f, 190.914062f},
        {120.938965f, 191.087891f}, {120.807617f, 191.239258f}, {120.665039f, 191.367676f}, {120.513184f, 191.474609f},
        {120.353027f, 191.559570f}, {120.186523f, 191.623291f}, {120.015625f, 191.665283f}, {119.828613f, 191.663574f},
        {119.680176f, 191.628174f}, {119.564453f, 191.563721f}, {119.477539f, 191.475342f}, {119.414062f, 191.367432f},
        {119.369141f, 191.244873f}, {119.338867f, 191.112061f}, {119.316895f, 190.973877f}, {119.299805f, 190.835449f},
        {119.189941f, 190.263428f}, {119.047852f, 189.775879f}, {118.872070f, 189.372559f}, {118.662598f, 189.052246f},
        {118.417969f, 188.814941f}, {118.137695f, 188.659668f}, {117.820801f, 188.585938f}, {117.467285f, 188.592773f},
        {117.076172f, 188.679688f}, {116.661621f, 188.864014f}, {116.276367f, 189.045898f}, {115.920410f, 189.231689f},
        {115.593262f, 189.428711f}, {115.294922f, 189.643555f}, {115.025391f, 189.882568f}, {114.782715f, 190.152832f},
        {114.568848f, 190.461182f}, {114.382324f, 190.814209f}, {114.125488f, 191.406494f}, {113.817871f, 191.867432f},
        {113.467773f, 192.200928f}, {113.083496f, 192.410156f}, {112.671875f, 192.499268f}, {112.241699f, 192.471924f},
        {111.801758f, 192.331543f}, {111.358398f, 192.081787f}, {110.920410f, 191.726562f}, {110.288574f, 191.010742f},
        {109.705566f, 190.437012f}, {109.159180f, 190.000732f}, {108.637207f, 189.697266f}, {108.126465f, 189.521240f},
        {107.614746f, 189.467773f}, {107.089844f, 189.532715f}, {106.538574f, 189.709961f}, {105.949219f, 189.995850f},
        {105.447754f, 190.281250f}, {104.979004f, 190.481201f}, {104.541504f, 190.605957f}, {104.130371f, 190.665283f},
        {103.743652f, 190.667725f}, {103.377930f, 190.623535f}, {103.029297f, 190.541992f}, {102.696289f, 190.432617f},
        {102.375000f, 190.305420f}, {101.848145f, 190.091553f}, {101.338867f, 189.923828f}, {100.845215f, 189.800781f},
        {100.364746f, 189.719482f}, {99.896484f, 189.678223f},  {99.437988f, 189.674316f},  {98.987305f, 189.705078f},
        {98.541992f, 189.768799f},  {98.101074f, 189.863281f},  {97.800781f, 189.947998f},  {97.534668f, 190.010742f},
        {97.298340f, 190.051025f},  {97.087891f, 190.067139f},  {96.900391f, 190.057861f},  {96.730957f, 190.022217f},
        {96.576660f, 189.958496f},  {96.432617f, 189.866211f},  {96.295410f, 189.743652f},  {96.023926f, 189.432373f},
        {95.753418f, 189.178223f},  {95.482422f, 188.981201f},  {95.210938f, 188.840820f},  {94.938477f, 188.757080f},
        {94.663574f, 188.729736f},  {94.385742f, 188.758789f},  {94.104980f, 188.843994f},  {93.819824f, 188.984863f},
        {93.693359f, 189.075439f},  {93.581543f, 189.156982f},  {93.482910f, 189.228760f},  {93.395020f, 189.290771f},
        {93.316895f, 189.343018f},  {93.247559f, 189.385254f},  {93.184570f, 189.417236f},  {93.126953f, 189.439209f},
        {93.073242f, 189.450684f},  {92.439941f, 189.450439f},  {91.818848f, 189.543701f},  {91.207520f, 189.703857f},
        {90.603516f, 189.904053f},  {90.004395f, 190.117920f},  {89.406738f, 190.318848f},  {88.809570f, 190.479736f},
        {88.208496f, 190.573975f},  {87.601562f, 190.575195f},  {87.040039f, 190.441162f},  {86.499512f, 190.335205f},
        {85.983887f, 190.240967f},  {85.494629f, 190.143555f},  {85.033691f, 190.026123f},  {84.604004f, 189.873047f},
        {84.207031f, 189.668701f},  {83.846680f, 189.397217f},  {83.523438f, 189.042725f},  {83.430176f, 188.881592f},
        {83.350586f, 188.745850f},  {83.284668f, 188.632324f},  {83.229004f, 188.538818f},  {83.183105f, 188.462402f},
        {83.144531f, 188.400879f},  {83.111816f, 188.350342f},  {83.083496f, 188.309082f},  {83.058105f, 188.273926f},
        {82.910156f, 188.136230f},  {82.761719f, 188.035400f},  {82.613281f, 187.968262f},  {82.465332f, 187.930908f},
        {82.315918f, 187.920410f},  {82.166504f, 187.933105f},  {82.017090f, 187.965088f},  {81.866699f, 188.013672f},
        {81.715332f, 188.074707f},  {81.442383f, 188.203369f},  {81.176758f, 188.319092f},  {80.916504f, 188.419189f},
        {80.661621f, 188.501221f},  {80.410156f, 188.562744f},  {80.161133f, 188.600586f},  {79.913574f, 188.612549f},
        {79.666992f, 188.596191f},  {79.418457f, 188.548584f},  {79.280273f, 188.510498f},  {79.155762f, 188.479248f},
        {79.042480f, 188.455078f},  {78.939941f, 188.436768f},  {78.846191f, 188.424316f},  {78.759277f, 188.417236f},
        {78.679199f, 188.414795f},  {78.603516f, 188.416504f},  {78.530273f, 188.422119f},  {78.115723f, 188.470215f},
        {77.703125f, 188.508057f},  {77.294922f, 188.537354f},  {76.888184f, 188.559326f},  {76.484375f, 188.575928f},
        {76.082520f, 188.588623f},  {75.682129f, 188.598877f},  {75.284180f, 188.608643f},  {74.887207f, 188.619873f},
        {74.342773f, 188.643799f},  {73.822266f, 188.675293f},  {73.323730f, 188.715332f},  {72.844727f, 188.765381f},
        {72.381836f, 188.826416f},  {71.932617f, 188.900635f},  {71.495117f, 188.989258f},  {71.065918f, 189.093018f},
        {70.642578f, 189.214111f},  {70.389648f, 189.308105f},  {70.156250f, 189.402588f},  {69.940430f, 189.489746f},
        {69.742188f, 189.559814f},  {69.560059f, 189.604736f},  {69.393555f, 189.615479f},  {69.241211f, 189.583252f},
        {69.101562f, 189.499512f},  {68.974121f, 189.355713f},  {68.923828f, 189.261719f},  {68.878906f, 189.180176f},
        {68.838867f, 189.109863f},  {68.803223f, 189.049072f},  {68.770508f, 188.996338f},  {68.741211f, 188.950928f},
        {68.713379f, 188.911133f},  {68.687988f, 188.875732f},  {68.662598f, 188.843750f},  {68.495117f, 188.675537f},
        {68.322754f, 188.541992f},  {68.146973f, 188.440674f},  {67.967773f, 188.368896f},  {67.786133f, 188.323975f},
        {67.601074f, 188.303467f},  {67.414551f, 188.304932f},  {67.225586f, 188.325439f},  {67.036621f, 188.363037f},
        {66.501465f, 188.507324f},  {65.980957f, 188.614258f},  {65.473633f, 188.681396f},  {64.977539f, 188.706055f},
        {64.492676f, 188.685791f},  {64.016602f, 188.617432f},  {63.549805f, 188.498779f},  {63.090332f, 188.326660f},
        {62.636719f, 188.099121f},  {62.344238f, 187.918457f},  {62.075195f, 187.787598f},  {61.828125f, 187.701660f},
        {61.599609f, 187.656250f},  {61.387207f, 187.646973f},  {61.188477f, 187.668701f},  {61.000977f, 187.716797f},
        {60.822266f, 187.787109f},  {60.649414f, 187.874512f},  {60.102539f, 188.177002f},  {59.562500f, 188.405029f},
        {59.028320f, 188.564209f},  {58.499023f, 188.658936f},  {57.974121f, 188.694580f},  {57.453613f, 188.676270f},
        {56.935547f, 188.609375f},  {56.419922f, 188.499023f},  {55.905762f, 188.349609f},  {55.681641f, 188.263916f},
        {55.485352f, 188.182373f},  {55.314453f, 188.107178f},  {55.164551f, 188.039551f},  {55.033691f, 187.981445f},
        {54.916992f, 187.934082f},  {54.812988f, 187.899414f},  {54.717285f, 187.878662f},  {54.626953f, 187.873779f},
        {54.109863f, 188.000000f},  {53.597656f, 188.124512f},  {53.089844f, 188.243896f},  {52.584473f, 188.354980f},
        {52.081543f, 188.453613f},  {51.579102f, 188.536377f},  {51.076660f, 188.599121f},  {50.573242f, 188.638428f},
        {50.067383f, 188.650879f},  {49.844238f, 188.647461f},  {49.647461f, 188.659424f},  {49.477051f, 188.686768f},
        {49.332520f, 188.729492f},  {49.212891f, 188.786865f},  {49.117676f, 188.859375f},  {49.046387f, 188.946289f},
        {48.997559f, 189.047607f},  {48.972656f, 189.163330f},  {48.985840f, 189.315918f},  {49.014160f, 189.447021f},
        {49.056152f, 189.558838f},  {49.110352f, 189.653564f},  {49.174316f, 189.733643f},  {49.246094f, 189.801514f},
        {49.324219f, 189.859375f},  {49.406738f, 189.909180f},  {49.492676f, 189.953613f},  {49.657715f, 190.014648f},
        {49.824219f, 190.047852f},  {49.990234f, 190.063721f},  {50.154297f, 190.071777f},  {50.315430f, 190.082031f},
        {50.472168f, 190.104736f},  {50.624512f, 190.149414f},  {50.769531f, 190.226562f},  {50.906738f, 190.345947f},
        {50.533691f, 190.424316f},  {50.161133f, 190.552490f},  {49.788574f, 190.711670f},  {49.413086f, 190.884277f},
        {49.033691f, 191.051025f},  {48.648926f, 191.193604f},  {48.256348f, 191.293701f},  {47.854492f, 191.333008f},
        {47.440918f, 191.293213f},
    };  // data size = 677

    Vec2 vertices3[] = {
        {208.474121f, 72.837158f},  {208.191895f, 73.396729f},  {207.958008f, 73.996094f},  {207.753418f, 74.618164f},
        {207.555664f, 75.247070f},  {207.346191f, 75.866699f},  {207.104492f, 76.460449f},  {206.810059f, 77.011963f},
        {206.443359f, 77.505615f},  {205.982910f, 77.924316f},  {205.663086f, 78.083008f},  {205.385254f, 78.211182f},
        {205.144531f, 78.306641f},  {204.937012f, 78.367188f},  {204.757324f, 78.390381f},  {204.601074f, 78.373779f},
        {204.462891f, 78.315186f},  {204.338867f, 78.212158f},  {204.224121f, 78.062500f},  {204.072754f, 77.785645f},
        {203.927246f, 77.567139f},  {203.788086f, 77.407715f},  {203.655762f, 77.309326f},  {203.529785f, 77.272949f},
        {203.412109f, 77.299561f},  {203.302246f, 77.390625f},  {203.199707f, 77.547363f},  {203.107422f, 77.770752f},
        {203.042969f, 78.017578f},  {202.980957f, 78.249512f},  {202.920410f, 78.466797f},  {202.859863f, 78.670898f},
        {202.798828f, 78.862549f},  {202.734863f, 79.042725f},  {202.669434f, 79.212402f},  {202.599609f, 79.372070f},
        {202.525391f, 79.522949f},  {202.167480f, 80.107178f},  {201.847168f, 80.575439f},  {201.549805f, 80.932373f},
        {201.262207f, 81.184570f},  {200.969238f, 81.338135f},  {200.658203f, 81.398193f},  {200.314453f, 81.370850f},
        {199.923340f, 81.262207f},  {199.471191f, 81.077637f},  {199.173340f, 80.931152f},  {198.903809f, 80.800049f},
        {198.657715f, 80.682617f},  {198.434570f, 80.577637f},  {198.229004f, 80.483154f},  {198.039062f, 80.398193f},
        {197.861328f, 80.320801f},  {197.692383f, 80.249512f},  {197.529297f, 80.183105f},  {197.204590f, 80.076904f},
        {196.910645f, 80.024658f},  {196.646484f, 80.024902f},  {196.413574f, 80.077637f},  {196.210938f, 80.181641f},
        {196.040039f, 80.335938f},  {195.900391f, 80.540283f},  {195.791992f, 80.793457f},  {195.715332f, 81.094971f},
        {195.686523f, 81.382568f},  {195.654297f, 81.647461f},  {195.617188f, 81.888672f},  {195.570801f, 82.104736f},
        {195.514160f, 82.294678f},  {195.444336f, 82.457520f},  {195.357422f, 82.591797f},  {195.252441f, 82.696777f},
        {195.125000f, 82.770752f},  {194.867188f, 82.820801f},  {194.614258f, 82.871826f},  {194.365723f, 82.917969f},
        {194.123047f, 82.952148f},  {193.886230f, 82.968506f},  {193.656738f, 82.960205f},  {193.434570f, 82.920654f},
        {193.220215f, 82.843750f},  {193.014648f, 82.722900f},  {192.823730f, 82.513672f},  {192.686523f, 82.318848f},
        {192.599121f, 82.137695f},  {192.557617f, 81.969482f},  {192.558105f, 81.813965f},  {192.597168f, 81.670898f},
        {192.671387f, 81.538818f},  {192.776855f, 81.418213f},  {192.910156f, 81.308350f},  {192.993164f, 81.258789f},
        {193.067871f, 81.214844f},  {193.136230f, 81.176270f},  {193.197754f, 81.143066f},  {193.253906f, 81.114258f},
        {193.305664f, 81.089600f},  {193.353027f, 81.068359f},  {193.398926f, 81.050293f},  {193.442871f, 81.034912f},
        {193.590820f, 81.006592f},  {193.743652f, 80.996338f},  {193.896484f, 80.994873f},  {194.047852f, 80.991943f},
        {194.192383f, 80.978271f},  {194.327148f, 80.943848f},  {194.449219f, 80.878906f},  {194.555176f, 80.774170f},
        {194.640137f, 80.619873f},  {194.673828f, 80.418457f},  {194.679688f, 80.244385f},  {194.661621f, 80.095215f},
        {194.622070f, 79.968262f},  {194.564941f, 79.861816f},  {194.493652f, 79.772949f},  {194.410645f, 79.699463f},
        {194.319824f, 79.638672f},  {194.224121f, 79.588623f},  {194.011719f, 79.504395f},  {193.797363f, 79.425537f},
        {193.585449f, 79.359375f},  {193.378418f, 79.312256f},  {193.178711f, 79.290283f},  {192.989258f, 79.300049f},
        {192.812988f, 79.347656f},  {192.653320f, 79.439941f},  {192.512207f, 79.583496f},  {192.344727f, 79.906738f},
        {192.175293f, 80.190186f},  {192.002441f, 80.435791f},  {191.825195f, 80.646240f},  {191.641113f, 80.823486f},
        {191.448242f, 80.970215f},  {191.246094f, 81.088379f},  {191.032715f, 81.180664f},  {190.805664f, 81.248535f},
        {190.655762f, 81.280029f},  {190.527344f, 81.319824f},  {190.416992f, 81.367676f},  {190.324707f, 81.424316f},
        {190.248535f, 81.488525f},  {190.186523f, 81.560303f},  {190.137207f, 81.640137f},  {190.099121f, 81.726807f},
        {190.071289f, 81.820801f},  {190.058105f, 81.901611f},  {190.046387f, 81.977295f},

        {190.036621f, 82.048096f},  {190.027344f, 82.114990f},  {190.019043f, 82.178223f},  {190.010742f, 82.237793f},
        {190.002441f, 82.294922f},  {189.992676f, 82.349609f},  {189.980957f, 82.402344f},  {189.901367f, 82.650391f},
        {189.805664f, 82.884766f},  {189.695312f, 83.102295f},  {189.570801f, 83.298340f},  {189.434570f, 83.469727f},
        {189.287598f, 83.611816f},  {189.130859f, 83.720703f},  {188.966309f, 83.793213f},  {188.794434f, 83.824707f},
        {188.603516f, 83.768066f},  {188.435059f, 83.672363f},  {188.289551f, 83.542236f},  {188.163574f, 83.383057f},
        {188.057129f, 83.198730f},  {187.967285f, 82.994873f},  {187.893555f, 82.776367f},  {187.833008f, 82.547607f},
        {187.785645f, 82.313721f},  {187.773926f, 82.096924f},  {187.793457f, 81.878662f},  {187.831543f, 81.663574f},
        {187.874512f, 81.457031f},  {187.910156f, 81.263672f},  {187.925293f, 81.088379f},  {187.908203f, 80.936279f},
        {187.845703f, 80.812744f},  {187.725098f, 80.721680f},  {187.481934f, 80.691895f},  {187.247559f, 80.687744f},
        {187.024414f, 80.711670f},  {186.812988f, 80.764404f},  {186.615234f, 80.847412f},  {186.432617f, 80.962158f},
        {186.266113f, 81.110107f},  {186.117676f, 81.292480f},  {185.987793f, 81.510986f},  {185.912598f, 81.752930f},
        {185.857422f, 82.003662f},  {185.813477f, 82.252197f},  {185.770020f, 82.488770f},  {185.717285f, 82.701904f},
        {185.645996f, 82.881348f},  {185.545898f, 83.016602f},  {185.406250f, 83.097168f},  {185.218750f, 83.112061f},
        {184.932617f, 82.999023f},  {184.679688f, 82.864502f},  {184.458984f, 82.708496f},  {184.271484f, 82.531250f},
        {184.116211f, 82.332275f},  {183.992676f, 82.112305f},  {183.901367f, 81.870850f},  {183.841797f, 81.607910f},
        {183.813477f, 81.323730f},  {183.815430f, 81.205078f},  {183.813965f, 81.101318f},  {183.810059f, 81.010498f},
        {183.804199f, 80.929443f},  {183.796387f, 80.856201f},  {183.787109f, 80.787598f},  {183.776855f, 80.721191f},
        {183.765137f, 80.654053f},  {183.752441f, 80.583740f},  {183.577148f, 80.744385f},  {183.434082f, 80.923096f},
        {183.318848f, 81.116699f},  {183.225098f, 81.321289f},  {183.148438f, 81.534180f},  {183.081543f, 81.751465f},
        {183.019531f, 81.969482f},  {182.956543f, 82.185547f},  {182.887207f, 82.395996f},  {182.763672f, 82.706543f},
        {182.657227f, 83.024658f},  {182.557129f, 83.337402f},  {182.453125f, 83.631836f},  {182.333496f, 83.895508f},
        {182.189453f, 84.115234f},  {182.009277f, 84.277588f},  {181.782227f, 84.370605f},  {181.498047f, 84.380615f},
        {181.328125f, 84.342529f},  {181.180176f, 84.330566f},  {181.052246f, 84.342529f},  {180.942383f, 84.375488f},
        {180.851074f, 84.427002f},  {180.776367f, 84.494873f},  {180.716797f, 84.575439f},  {180.670898f, 84.666992f},
        {180.637695f, 84.766846f},  {180.618652f, 84.895752f},  {180.606445f, 85.019775f},  {180.602051f, 85.137695f},
        {180.605957f, 85.248535f},  {180.619141f, 85.351318f},  {180.642090f, 85.444824f},  {180.676270f, 85.528320f},
        {180.722168f, 85.600830f},  {180.780762f, 85.661377f},  {180.922363f, 85.732422f},  {181.058105f, 85.796387f},
        {181.184570f, 85.858887f},  {181.298340f, 85.926025f},  {181.394531f, 86.003418f},  {181.470703f, 86.097412f},
        {181.521484f, 86.213623f},  {181.544434f, 86.357910f},  {181.536133f, 86.536133f},  {181.464355f, 86.832031f},
        {181.395508f, 87.114258f},  {181.325195f, 87.379639f},  {181.247559f, 87.626221f},  {181.158691f, 87.850830f},
        {181.052734f, 88.051758f},  {180.924805f, 88.225342f},  {180.769043f, 88.369873f},  {180.581543f, 88.482178f},
        {180.477051f, 88.512695f},  {180.383789f, 88.536865f},  {180.301270f, 88.555664f},  {180.228516f, 88.569824f},
        {180.163086f, 88.580078f},  {180.104492f, 88.587646f},  {180.050781f, 88.593018f},  {180.001465f, 88.596924f},
        {179.955078f, 88.600342f},  {179.795410f, 88.739990f},  {179.683594f, 88.876221f},  {179.614746f, 89.009766f},
        {179.584473f, 89.140625f},  {179.588379f, 89.270020f},  {179.621582f, 89.398193f},  {179.680176f, 89.525635f},
        {179.758789f, 89.652344f},  {179.853516f, 89.779785f},  {180.164551f, 90.222412f},  {180.381836f, 90.699219f},
        {180.509277f, 91.196289f},  {180.550293f, 91.698730f},  {180.509277f, 92.191406f},  {180.389648f, 92.659668f},
        {180.194336f, 93.088867f},  {179.928711f, 93.463867f},  {179.595215f, 93.770752f},  {179.391113f, 93.863770f},
        {179.218750f, 93.927246f},  {179.074219f, 93.962402f},  {178.955078f, 93.972656f},  {178.858398f, 93.959473f},
        {178.780762f, 93.925537f},  {178.718750f, 93.872314f},  {178.669922f, 93.802979f},  {178.630859f, 93.718994f},
        {178.567871f, 93.527344f},  {178.498535f, 93.346436f},  {178.424316f, 93.174561f},  {178.346191f, 93.010254f},
        {178.266602f, 92.851562f},  {178.186035f, 92.697021f},  {178.106445f, 92.544922f},  {178.028809f, 92.393799f},
        {177.954102f, 92.241455f},  {177.859375f, 92.024658f},  {177.764648f, 91.822998f},  {177.667969f, 91.638672f},
        {177.566406f, 91.474854f},  {177.457031f, 91.333984f},  {177.337891f, 91.218506f},  {177.206543f, 91.131592f},
        {177.059570f, 91.075684f},  {176.894531f, 91.053223f},  {176.652344f, 91.102051f},  {176.433594f, 91.171631f},
        {176.237305f, 91.262451f},  {176.063477f, 91.372559f},  {175.911621f, 91.502686f},  {175.779297f, 91.651367f},
        {175.667480f, 91.818115f},  {175.573730f, 92.002197f},  {175.498535f, 92.203369f},  {175.431641f, 92.477051f},
        {175.359375f, 92.729736f},  {175.282227f, 92.964355f},  {175.199219f, 93.182129f},  {175.109375f, 93.385010f},
        {175.012695f, 93.574951f},  {174.908203f, 93.754150f},  {174.794434f, 93.923584f},  {174.671387f, 94.086182f},
        {174.467285f, 94.300049f},  {174.275879f, 94.465332f},  {174.095215f, 94.583252f},  {173.923828f, 94.654297f},
        {173.760742f, 94.680176f},  {173.604004f, 94.661621f},  {173.452637f, 94.599609f},  {173.304199f, 94.495117f},
        {173.158691f, 94.349609f},  {172.985840f, 94.115967f},  {172.816406f, 93.903564f},  {172.649414f, 93.717041f},
        {172.482422f, 93.561768f},  {172.313477f, 93.442139f},  {172.141602f, 93.363281f},  {171.963867f, 93.329834f},
        {171.779785f, 93.347168f},  {171.586426f, 93.419922f},  {171.322754f, 93.620605f},  {171.072266f, 93.820312f},
        {170.837402f, 94.023193f},  {170.624512f, 94.233154f},  {170.437500f, 94.454346f},  {170.281250f, 94.690186f},
        {170.160645f, 94.945312f},  {170.080078f, 95.223389f},  {170.045410f, 95.528564f},  {170.091797f, 95.918701f},
        {170.154785f, 96.284424f},  {170.235840f, 96.625244f},  {170.335449f, 96.939453f},  {170.455566f, 97.225830f},
        {170.596680f, 97.483887f},  {170.761230f, 97.711914f},  {170.949219f, 97.909180f},  {171.163574f, 98.073975f},
        {171.419434f, 98.170898f},  {171.650879f, 98.208984f},  {171.860352f, 98.196533f},  {172.050293f, 98.141113f},
        {172.224121f, 98.051514f},  {172.384766f, 97.935303f},  {172.535156f, 97.800781f},  {172.678711f, 97.655518f},
        {172.818359f, 97.508545f},  {172.925293f, 97.392090f},  {173.022461f, 97.272217f},  {173.112305f, 97.155029f},
        {173.196289f, 97.045410f},  {173.279785f, 96.948242f},  {173.364258f, 96.869873f},  {173.451660f, 96.815186f},
        {173.547363f, 96.789551f},  {173.651855f, 96.798340f},  {173.744141f, 96.855713f},  {173.816406f, 96.921387f},
        {173.872070f, 96.994141f},  {173.912109f, 97.072266f},  {173.938965f, 97.155029f},  {173.955078f, 97.240234f},
        {173.962891f, 97.327148f},  {173.963867f, 97.413818f},  {173.960449f, 97.499268f},  {173.942383f, 97.663574f},
        {173.917969f, 97.816406f},  {173.883301f, 97.958252f},  {173.839844f, 98.087891f},  {173.786133f, 98.205566f},
        {173.720703f, 98.311035f},  {173.643066f, 98.403320f},  {173.552246f, 98.482666f},  {173.448242f, 98.548584f},
        {173.381836f, 98.576416f},  {173.336914f, 98.598633f},  {173.309570f, 98.615234f},  {173.293945f, 98.626953f},
        {173.287109f, 98.633789f},  {173.283691f, 98.636719f},  {173.280273f, 98.635742f},  {173.270996f, 98.632080f},
        {173.253418f, 98.625244f},  {172.600586f, 98.535400f},  {172.059570f, 98.599121f},  {171.615234f, 98.794922f},
        {171.252930f, 99.101807f},  {170.958496f, 99.499023f},  {170.716797f, 99.965088f},  {170.512695f, 100.479004f},
        {170.332031f, 101.019287f}, {170.160156f, 101.565186f}, {170.023438f, 101.914795f}, {169.883789f, 102.206299f},
        {169.741699f, 102.447754f}, {169.598145f, 102.647217f}, {169.454590f, 102.812500f}, {169.311035f, 102.951660f},
        {169.169922f, 103.072998f}, {169.031250f, 103.184082f}, {168.896484f, 103.292969f}, {168.767090f, 103.431396f},
        {168.650879f, 103.586182f}, {168.545898f, 103.749023f}, {168.450195f, 103.911621f}, {168.361816f, 104.066162f},
        {168.278320f, 104.203857f}, {168.198730f, 104.316406f}, {168.120605f, 104.395508f}, {168.041992f, 104.433350f},
        {167.830078f, 104.349121f}, {167.620117f, 104.278809f}, {167.411133f, 104.217773f}, {167.205078f, 104.162109f},
        {167.001953f, 104.107178f}, {166.802734f, 104.047363f}, {166.607422f, 103.978760f}, {166.417480f, 103.896729f},
        {166.233887f, 103.796387f}, {165.754883f, 103.454102f}, {165.306641f, 103.195801f}, {164.884766f, 103.020996f},
        {164.483887f, 102.929199f}, {164.099121f, 102.919434f}, {163.726074f, 102.991943f}, {163.359375f, 103.145264f},
        {162.993164f, 103.379883f}, {162.624023f, 103.694580f}, {162.472168f, 103.857422f}, {162.341309f, 103.999512f},
        {162.229492f, 104.123047f}, {162.133301f, 104.230713f}, {162.051758f, 104.324951f}, {161.982422f, 104.407959f},
        {161.922852f, 104.482178f}, {161.870605f, 104.550537f}, {161.823242f, 104.614746f}, {161.695312f, 104.796631f},
        {161.566406f, 104.974365f}, {161.441406f, 105.150879f}, {161.325195f, 105.328125f}, {161.222656f, 105.509521f},
        {161.138672f, 105.697510f}, {161.078613f, 105.894531f}, {161.046387f, 106.103516f}, {161.048340f, 106.326660f},
        {161.138672f, 106.634033f}, {161.250977f, 106.875977f}, {161.382812f, 107.060547f}, {161.530273f, 107.196289f},
        {161.690430f, 107.291504f}, {161.860352f, 107.354980f}, {162.036621f, 107.395264f}, {162.216797f, 107.420410f},
        {162.396973f, 107.438965f}, {162.512695f, 107.454102f}, {162.619629f, 107.468018f}, {162.717285f, 107.482178f},
        {162.807129f, 107.497070f}, {162.890625f, 107.513916f}, {162.966797f, 107.533447f}, {163.038086f, 107.556396f},
        {163.104492f, 107.583984f}, {163.166504f, 107.616455f}, {163.424316f, 107.795410f}, {163.683105f, 107.964355f},
        {163.944336f, 108.125488f}, {164.207031f, 108.282471f}, {164.473145f, 108.438477f}, {164.741211f, 108.595703f},
        {165.011719f, 108.758057f}, {165.285645f, 108.927979f}, {165.562988f, 109.108643f}, {165.125000f, 109.434570f},
        {164.675781f, 109.676514f}, {164.215332f, 109.844971f}, {163.746094f, 109.949707f}, {163.269531f, 110.000488f},
        {162.786133f, 110.007568f}, {162.298340f, 109.981201f}, {161.806152f, 109.930664f}, {161.312012f, 109.866699f},
        {160.913086f, 109.899414f}, {160.546875f, 109.959961f}, {160.208984f, 110.041748f}, {159.895020f, 110.139648f},
        {159.599609f, 110.247314f}, {159.319824f, 110.359131f}, {159.049805f, 110.468994f}, {158.786621f, 110.571045f},
        {158.523438f, 110.659424f}, {158.261719f, 110.738037f}, {158.035645f, 110.845703f}, {157.846191f, 110.979492f},
        {157.694824f, 111.135742f}, {157.582031f, 111.312744f}, {157.508789f, 111.506592f}, {157.475098f, 111.715332f},
        {157.482422f, 111.935303f}, {157.531738f, 112.164062f}, {157.645508f, 112.430176f}, {157.729004f, 112.667236f},
        {157.782715f, 112.879150f}, {157.806641f, 113.068848f}, {157.802246f, 113.240479f}, {157.769043f, 113.397461f},
        {157.707031f, 113.543213f}, {157.617188f, 113.681396f}, {157.500000f, 113.815674f}, {157.250977f, 114.050537f},
        {157.046387f, 114.285889f}, {156.885254f, 114.522949f}, {156.770020f, 114.763184f}, {156.700684f, 115.008301f},
        {156.677734f, 115.259033f}, {156.701172f, 115.517334f}, {156.773438f, 115.784180f}, {156.894043f, 116.061279f},
        {157.056152f, 116.340088f}, {157.181152f, 116.611084f}, {157.270996f, 116.874023f}, {157.328613f, 117.129395f},
        {157.354004f, 117.376709f}, {157.349121f, 117.616699f}, {157.315918f, 117.849121f}, {157.255859f, 118.074463f},
        {157.169922f, 118.292236f}, {157.026855f, 118.551758f}, {156.895996f, 118.801270f}, {156.776855f, 119.042725f},
        {156.670410f, 119.278076f}, {156.574219f, 119.510010f}, {156.489258f, 119.740479f}, {156.414551f, 119.971191f},
        {156.349121f, 120.204590f}, {156.294434f, 120.442871f}, {156.211426f, 120.775879f}, {156.096680f, 121.038330f},
        {155.957520f, 121.234863f}, {155.798340f, 121.372070f}, {155.626465f, 121.455811f}, {155.448730f, 121.491455f},
        {155.270996f, 121.485352f}, {155.099121f, 121.442871f}, {154.940430f, 121.370361f}, {154.654785f, 121.155029f},
        {154.361816f, 120.957520f}, {154.069336f, 120.767334f}, {153.786621f, 120.574463f}, {153.520020f, 120.367920f},
        {153.279785f, 120.137695f}, {153.073730f, 119.873291f}, {152.908691f, 119.564453f}, {152.794434f, 119.200928f},
        {152.681641f, 119.048340f}, {152.578613f, 118.943604f}, {152.485352f, 118.880615f}, {152.400391f, 118.854004f},
        {152.322266f, 118.857422f}, {152.249512f, 118.885254f}, {152.180664f, 118.931396f}, {152.113770f, 118.990479f},
        {152.048340f, 119.056396f}, {151.668945f, 119.252197f}, {151.292480f, 119.398193f}, {150.918945f, 119.496826f},
        {150.547363f, 119.552002f}, {150.178223f, 119.566650f}, {149.812012f, 119.543701f}, {149.447266f, 119.486328f},
        {149.083984f, 119.397705f}, {148.722168f, 119.281494f}, {148.470215f, 119.172607f}, {148.240234f, 119.062988f},
        {148.028809f, 118.954590f}, {147.833496f, 118.849121f}, {147.651367f, 118.748047f}, {147.479004f, 118.653320f},
        {147.314453f, 118.566406f}, {147.153320f, 118.488525f}, {146.994141f, 118.422119f}, {146.804688f, 118.368164f},
        {146.625488f, 118.325684f}, {146.458008f, 118.299316f}, {146.302246f, 118.292969f}, {146.160156f, 118.311523f},
        {146.030762f, 118.359131f}, {145.916504f, 118.440186f}, {145.817383f, 118.558838f}, {145.733398f, 118.719971f},
        {145.847168f, 118.963135f}, {145.981445f, 119.151611f}, {146.132812f, 119.295410f}, {146.297852f, 119.404053f},
        {146.471191f, 119.488037f}, {146.650879f, 119.557129f}, {146.831543f, 119.621338f}, {147.009766f, 119.690430f},
        {147.182129f, 119.774902f}, {147.292969f, 119.854492f}, {147.397461f, 119.925537f}, {147.495117f, 119.991943f},
        {147.583008f, 120.055420f}, {147.661133f, 120.119141f}, {147.727539f, 120.185547f}, {147.780273f, 120.258545f},
        {147.818359f, 120.339844f}, {147.839844f, 120.432373f}, {147.827148f, 120.567139f}, {147.799316f, 120.679443f},
        {147.757812f, 120.772705f}, {147.705566f, 120.849365f}, {147.644043f, 120.912354f}, {147.576660f, 120.964600f},
        {147.504883f, 121.008301f}, {147.430664f, 121.047363f}, {147.355957f, 121.083984f}, {147.263672f, 121.130127f},
        {147.173828f, 121.168213f}, {147.086426f, 121.199219f}, {147.000977f, 121.224121f}, {146.917480f, 121.244141f},
        {146.835449f, 121.260498f}, {146.755371f, 121.273926f}, {146.675293f, 121.285645f}, {146.596680f, 121.296875f},
        {146.259277f, 121.365723f}, {145.977051f, 121.459473f}, {145.748535f, 121.580566f}, {145.570801f, 121.732422f},
        {145.443359f, 121.917725f}, {145.363770f, 122.138428f}, {145.330078f, 122.398438f}, {145.340332f, 122.699707f},
        {145.392578f, 123.045410f}, {145.730469f, 122.801025f}, {146.083984f, 122.593018f}, {146.450195f, 122.415527f},
        {146.827637f, 122.263184f}, {147.213379f, 122.129883f}, {147.604004f, 122.010010f}, {147.999512f, 121.897217f},
        {148.395508f, 121.786133f}, {148.791016f, 121.670410f}, {148.928711f, 121.629150f}, {149.044922f, 121.593506f},
        {149.141602f, 121.563232f}, {149.222168f, 121.537354f}, {149.288574f, 121.515137f}, {149.342773f, 121.496094f},
        {149.387695f, 121.479492f}, {149.425293f, 121.464111f}, {149.457520f, 121.449707f}, {149.631836f, 121.272461f},
        {149.805176f, 121.131836f}, {149.977539f, 121.028320f}, {150.148926f, 120.962402f}, {150.320312f, 120.935791f},
        {150.490723f, 120.948730f}, {150.660645f, 121.001709f}, {150.830566f, 121.095947f}, {151.000488f, 121.232178f},
        {151.237793f, 121.332764f}, {151.465332f, 121.424805f}, {151.677734f, 121.516602f}, {151.871094f, 121.615967f},
        {152.041504f, 121.730469f}, {152.184570f, 121.868652f}, {152.295898f, 122.037598f}, {152.371094f, 122.245605f},
        {152.406250f, 122.500488f}, {152.407227f, 122.729248f}, {152.407715f, 122.940918f}, {152.409668f, 123.137939f},
        {152.414551f, 123.321045f}, {152.423828f, 123.491943f}, {152.439453f, 123.652832f}, {152.462402f, 123.804199f},
        {152.494629f, 123.948486f}, {152.538086f, 124.086670f}, {152.892090f, 124.395752f}, {153.256348f, 124.637451f},
        {153.625977f, 124.815674f}, {153.997559f, 124.933350f}, {154.369141f, 124.993896f}, {154.735840f, 125.000732f},
        {155.095215f, 124.957275f}, {155.442871f, 124.866455f}, {155.776855f, 124.732422f}, {156.134766f, 124.477783f},
        {156.449219f, 124.184570f}, {156.721680f, 123.857178f}, {156.956055f, 123.500732f}, {157.154785f, 123.119873f},
        {157.319336f, 122.719727f}, {157.453125f, 122.305420f}, {157.559082f, 121.881348f}, {157.639160f, 121.453369f},
        {157.679199f, 121.133057f}, {157.720215f, 120.840820f}, {157.763184f, 120.573730f}, {157.809082f, 120.327881f},
        {157.859863f, 120.101318f}, {157.916992f, 119.889893f}, {157.980469f, 119.691650f}, {158.052246f, 119.502686f},
        {158.133301f, 119.320068f}, {158.317383f, 118.946045f}, {158.461426f, 118.576904f}, {158.565918f, 118.213623f},
        {158.630371f, 117.856445f}, {158.654297f, 117.505127f}, {158.638184f, 117.160400f}, {158.582031f, 116.822510f},
        {158.485840f, 116.492188f}, {158.349121f, 116.169678f}, {158.191895f, 115.899170f}, {158.073242f, 115.662109f},
        {157.991699f, 115.454590f}, {157.946777f, 115.273193f}, {157.937012f, 115.113281f}, {157.960938f, 114.970947f},
        {158.019043f, 114.842285f}, {158.109375f, 114.723145f}, {158.230469f, 114.609619f}, {158.427246f, 114.465820f},
        {158.606445f, 114.318115f}, {158.769043f, 114.165039f}, {158.915527f, 114.005859f}, {159.045898f, 113.839111f},
        {159.161133f, 113.664307f}, {159.261719f, 113.479736f}, {159.348633f, 113.284912f}, {159.420898f, 113.078613f},
        {159.603516f, 112.446777f}, {159.821289f, 111.927979f}, {160.073730f, 111.520996f}, {160.361328f, 111.226318f},
        {160.682617f, 111.042969f}, {161.037598f, 110.971191f}, {161.425781f, 111.009766f}, {161.847168f, 111.159424f},
        {162.300293f, 111.419434f}, {162.154785f, 111.573975f}, {161.990723f, 111.717773f}, {161.811035f, 111.854492f},
        {161.618164f, 111.987061f}, {161.415527f, 112.118164f}, {161.205078f, 112.251953f}, {160.991211f, 112.390869f},
        {160.774902f, 112.538330f}, {160.559570f, 112.697754f}, {160.401855f, 112.836182f}, {160.258789f, 112.970215f},
        {160.132324f, 113.101074f}, {160.024414f, 113.231445f}, {159.935547f, 113.363037f}, {159.867188f, 113.497559f},
        {159.821289f, 113.637451f}, {159.798828f, 113.784424f}, {159.801270f, 113.940918f}, {159.854004f, 114.138184f},
        {159.917969f, 114.311035f}, {159.992676f, 114.460938f}, {160.076660f, 114.589600f}, {160.169922f, 114.697754f},
        {160.271484f, 114.786865f}, {160.380371f, 114.859131f}, {160.496582f, 114.914795f}, {160.618164f, 114.955811f},
        {160.921387f, 115.001465f}, {161.216797f, 115.033447f}, {161.507324f, 115.054688f}, {161.792480f, 115.066406f},
        {162.073242f, 115.070557f}, {162.349609f, 115.069092f}, {162.623535f, 115.063232f}, {162.895508f, 115.055908f},
        {163.165527f, 115.048096f}, {163.290039f, 115.041504f}, {163.398926f, 115.033203f}, {163.495605f, 115.023926f},
        {163.580078f, 115.013428f}, {163.654297f, 115.001953f}, {163.721191f, 114.989014f}, {163.780762f, 114.974609f},
        {163.835449f, 114.959229f}, {163.886230f, 114.942627f}, {163.963379f, 114.911621f}, {164.036133f, 114.878906f},
        {164.106934f, 114.845215f}, {164.174316f, 114.810547f}, {164.239258f, 114.774902f}, {164.303223f, 114.738281f},
        {164.364746f, 114.701172f}, {164.424805f, 114.663330f}, {164.484375f, 114.625000f}, {164.818359f, 114.386719f},
        {165.088379f, 114.150391f}, {165.294434f, 113.912109f}, {165.438477f, 113.667725f}, {165.520996f, 113.412842f},
        {165.543945f, 113.143066f}, {165.507812f, 112.854004f}, {165.413574f, 112.541504f}, {165.263184f, 112.201416f},
        {165.263184f, 112.030762f}, {165.277832f, 111.882080f}, {165.304688f, 111.754639f}, {165.343262f, 111.646973f},
        {165.390625f, 111.557373f}, {165.445801f, 111.484863f}, {165.506836f, 111.427979f}, {165.572266f, 111.385498f},
        {165.640625f, 111.356201f}, {166.054688f, 111.241699f}, {166.418457f, 111.065918f}, {166.737793f, 110.837158f},
        {167.020508f, 110.564209f}, {167.272949f, 110.255859f}, {167.501953f, 109.920898f}, {167.715332f, 109.568359f},
        {167.919434f, 109.206299f}, {168.120117f, 108.843994f}, {168.386230f, 108.446045f}, {168.666016f, 108.110352f},
        {168.956543f, 107.837646f}, {169.252930f, 107.629395f}, {169.553711f, 107.486328f}, {169.854492f, 107.409912f},
        {170.151367f, 107.401123f}, {170.441895f, 107.461182f}, {170.721191f, 107.591309f}, {171.030762f, 107.860596f},
        {171.322754f, 108.103271f}, {171.600586f, 108.311523f}, {171.869141f, 108.478760f}, {172.131348f, 108.597656f},
        {172.390137f, 108.660889f}, {172.649902f, 108.661377f}, {172.914062f, 108.592041f}, {173.186523f, 108.445312f},
        {173.350098f, 108.314941f}, {173.490723f, 108.230957f}, {173.610352f, 108.187500f}, {173.710938f, 108.179932f},
        {173.794434f, 108.202148f}, {173.863281f, 108.249268f}, {173.920410f, 108.316406f}, {173.966797f, 108.397949f},
        {174.004395f, 108.488281f}, {174.062988f, 108.663330f}, {174.127441f, 108.829590f}, {174.196777f, 108.984375f},
        {174.273438f, 109.123047f}, {174.356934f, 109.243408f}, {174.448242f, 109.341309f}, {174.548828f, 109.413574f},
        {174.658203f, 109.456299f}, {174.777832f, 109.466309f}, {175.158203f, 109.369385f}, {175.537109f, 109.312500f},
        {175.913574f, 109.282471f}, {176.286133f, 109.265137f}, {176.653320f, 109.246338f}, {177.014160f, 109.212402f},
        {177.367188f, 109.149170f}, {177.710449f, 109.043457f}, {178.042969f, 108.880371f}, {178.213867f, 108.738281f},
        {178.362793f, 108.606201f}, {178.491699f, 108.481934f}, {178.600586f, 108.362549f}, {178.690430f, 108.246338f},
        {178.761719f, 108.130615f}, {178.816406f, 108.013428f}, {178.853027f, 107.891846f}, {178.874512f, 107.764160f},
        {178.813965f, 107.513184f}, {178.733887f, 107.311279f}, {178.635742f, 107.152344f}, {178.521973f, 107.030518f},
        {178.395020f, 106.939209f}, {178.256836f, 106.872559f}, {178.110352f, 106.824707f}, {177.957520f, 106.789307f},
        {177.801758f, 106.760254f}, {177.527832f, 106.714600f}, {177.260254f, 106.681641f}, {176.997559f, 106.657715f},
        {176.736816f, 106.638672f}, {176.476074f, 106.621338f}, {176.214355f, 106.602539f}, {175.948242f, 106.577881f},
        {175.676758f, 106.544189f}, {175.396973f, 106.498047f}, {175.585449f, 106.295654f}, {175.772949f, 106.093750f},
        {175.959473f, 105.890869f}, {176.145020f, 105.685791f}, {176.327637f, 105.478271f}, {176.507324f, 105.266846f},
        {176.684082f, 105.050781f}, {176.855957f, 104.828857f}, {177.023926f, 104.600342f}, {177.147949f, 104.429199f},
        {177.271973f, 104.284180f}, {177.394531f, 104.165527f}, {177.516602f, 104.073242f}, {177.636719f, 104.006592f},
        {177.755859f, 103.965576f}, {177.871582f, 103.949707f}, {177.985352f, 103.959473f}, {178.096191f, 103.993896f},
        {178.377930f, 104.183594f}, {178.652832f, 104.372559f}, {178.921387f, 104.561768f}, {179.184082f, 104.750732f},
        {179.441895f, 104.940430f}, {179.695312f, 105.130859f}, {179.944336f, 105.322510f}, {180.190430f, 105.515625f},
        {180.434082f, 105.710449f}, {180.571777f, 105.833740f}, {180.680664f, 105.952393f}, {180.762207f, 106.066650f},
        {180.817871f, 106.175049f}, {180.847656f, 106.277832f}, {180.853516f, 106.374023f}, {180.836426f, 106.463135f},
        {180.797363f, 106.543945f}, {180.736816f, 106.616943f}, {180.474121f, 106.823242f}, {180.271484f, 107.043701f},
        {180.123535f, 107.276855f}, {180.022949f, 107.521729f}, {179.964355f, 107.777100f}, {179.940918f, 108.041260f},
        {179.945801f, 108.313232f}, {179.973633f, 108.592041f}, {180.017578f, 108.875732f}, {180.069336f, 109.152100f},
        {180.115723f, 109.413330f}, {180.156738f, 109.661865f}, {180.193359f, 109.898438f}, {180.225586f, 110.125244f},
        {180.254883f, 110.343994f}, {180.281738f, 110.556152f}, {180.305664f, 110.762939f}, {180.328613f, 110.967041f},
        {180.352539f, 111.147949f}, {180.381836f, 111.313477f}, {180.417969f, 111.463623f}, {180.461426f, 111.598145f},
        {180.513672f, 111.717285f}, {180.575684f, 111.820557f}, {180.646973f, 111.908203f}, {180.729492f, 111.979980f},
        {180.823730f, 112.035889f}, {180.951172f, 112.064209f}, {181.065918f, 112.070068f}, {181.168945f, 112.055908f},
        {181.262207f, 112.024170f}, {181.345215f, 111.976562f}, {181.420898f, 111.915527f}, {181.489258f, 111.843750f},
        {181.551758f, 111.763184f}, {181.610352f, 111.676025f}, {181.829590f, 111.290039f}, {182.038574f, 110.904785f},
        {182.232910f, 110.519043f}, {182.409668f, 110.129639f}, {182.564453f, 109.735107f}, {182.695312f, 109.332764f},
        {182.798828f, 108.920166f}, {182.871094f, 108.495850f}, {182.908691f, 108.056885f}, {182.913086f, 107.658447f},
        {182.907227f, 107.286621f}, {182.891113f, 106.939453f}, {182.864746f, 106.613037f}, {182.828613f, 106.305664f},
        {182.782715f, 106.014404f}, {182.725586f, 105.736084f}, {182.659668f, 105.468506f}, {182.583496f, 105.208496f},
        {182.463867f, 104.846191f}, {182.371582f, 104.499756f}, {182.306152f, 104.167725f}, {182.268066f, 103.848877f},
        {182.259766f, 103.541504f}, {182.280273f, 103.243896f}, {182.331543f, 102.955078f}, {182.413574f, 102.673340f},
        {182.527832f, 102.396973f}, {182.622070f, 102.233643f}, {182.708984f, 102.081787f}, {182.787109f, 101.940186f},
        {182.856445f, 101.807861f}, {182.915527f, 101.684082f}, {182.963867f, 101.566650f}, {183.000000f, 101.455322f},
        {183.022949f, 101.347900f}, {183.032227f, 101.244141f}, {182.991699f, 100.753174f}, {182.999023f, 100.293213f},
        {183.050781f, 99.860840f},  {183.142090f, 99.452637f},  {183.268066f, 99.064941f},  {183.424316f, 98.695068f},
        {183.606445f, 98.338867f},  {183.810059f, 97.993164f},  {184.030273f, 97.655518f},  {184.195801f, 97.410889f},
        {184.339355f, 97.177979f},  {184.461914f, 96.954102f},  {184.565918f, 96.737305f},  {184.652832f, 96.526123f},
        {184.723633f, 96.318115f},  {184.781738f, 96.111328f},  {184.827637f, 95.904541f},  {184.862793f, 95.694824f},
        {184.932617f, 95.311035f},  {185.046875f, 94.980713f},  {185.197754f, 94.701416f},  {185.378906f, 94.471680f},
        {185.580566f, 94.289062f},  {185.797852f, 94.151611f},  {186.020508f, 94.057373f},  {186.242676f, 94.004395f},
        {186.456055f, 93.990234f},  {187.046387f, 94.060059f},  {187.551758f, 94.010254f},  {187.983398f, 93.858887f},
        {188.353027f, 93.621582f},  {188.670898f, 93.315674f},  {188.950195f, 92.957275f},  {189.200195f, 92.563965f},
        {189.434082f, 92.151855f},  {189.662598f, 91.737549f},  {189.905273f, 91.329834f},  {190.120605f, 90.937256f},
        {190.303711f, 90.555908f},  {190.451172f, 90.180908f},  {190.559570f, 89.809082f},  {190.624023f, 89.436035f},
        {190.641113f, 89.057617f},  {190.606445f, 88.669678f},  {190.517090f, 88.268555f},  {190.390625f, 87.901367f},
        {190.302246f, 87.539551f},  {190.248047f, 87.183350f},  {190.222168f, 86.833740f},  {190.220703f, 86.491455f},
        {190.239746f, 86.156738f},  {190.274414f, 85.830566f},  {190.320312f, 85.513672f},  {190.372559f, 85.206787f},
        {190.468262f, 84.788330f},  {190.584473f, 84.445801f},  {190.719727f, 84.176758f},  {190.874512f, 83.979736f},
        {191.047363f, 83.852783f},  {191.237793f, 83.793945f},  {191.444824f, 83.801270f},  {191.667480f, 83.872559f},
        {191.904297f, 84.006348f},  {192.361328f, 84.367676f},  {192.787109f, 84.645264f},  {193.186523f, 84.839844f},
        {193.564941f, 84.952637f},  {193.925781f, 84.985107f},  {194.275879f, 84.937988f},  {194.619141f, 84.812744f},
        {194.960938f, 84.610352f},  {195.304688f, 84.332275f},  {195.528320f, 84.088623f},  {195.720703f, 83.859863f},
        {195.882812f, 83.643066f},  {196.015625f, 83.435059f},  {196.121094f, 83.232666f},  {196.200195f, 83.032471f},
        {196.253906f, 82.832031f},  {196.284668f, 82.627686f},  {196.292480f, 82.416504f},  {196.275879f, 82.107422f},
        {196.289062f, 81.847900f},  {196.329102f, 81.635986f},  {196.395508f, 81.468750f},  {196.485840f, 81.343994f},
        {196.599121f, 81.258301f},  {196.732910f, 81.209717f},  {196.886719f, 81.195068f},  {197.058105f, 81.212158f},
        {197.363770f, 81.303955f},  {197.652344f, 81.399658f},  {197.919434f, 81.506592f},  {198.160156f, 81.633301f},
        {198.369629f, 81.787354f},  {198.544434f, 81.976562f},  {198.678711f, 82.208740f},  {198.768066f, 82.491699f},
        {198.809082f, 82.833496f},  {198.794922f, 83.169189f},  {198.804688f, 83.476318f},  {198.836914f, 83.755615f},
        {198.892578f, 84.006104f},  {198.971191f, 84.228271f},  {199.073730f, 84.422119f},  {199.198242f, 84.587402f},
        {199.345703f, 84.724365f},  {199.516113f, 84.832520f},  {199.760742f, 84.895996f},  {199.977539f, 84.912842f},
        {200.169922f, 84.888672f},  {200.339844f, 84.827637f},  {200.490723f, 84.735352f},  {200.625488f, 84.615967f},
        {200.746094f, 84.475098f},  {200.855957f, 84.316895f},  {200.957520f, 84.146484f},  {201.002441f, 84.062256f},
        {201.036133f, 84.004639f},  {201.058105f, 83.968262f},  {201.072754f, 83.947510f},  {201.081543f, 83.937256f},
        {201.085449f, 83.932129f},  {201.088379f, 83.926025f},  {201.091797f, 83.914551f},  {201.097168f, 83.891602f},
        {201.277832f, 83.334229f},  {201.488281f, 82.844238f},  {201.730469f, 82.423584f},  {202.005371f, 82.073486f},
        {202.314453f, 81.795410f},  {202.656738f, 81.591309f},  {203.035156f, 81.462646f},  {203.450195f, 81.411377f},
        {203.902344f, 81.438232f},  {204.236328f, 81.403564f},  {204.530273f, 81.343262f},  {204.785645f, 81.258057f},
        {205.004883f, 81.148682f},  {205.190430f, 81.016113f},  {205.343750f, 80.860840f},  {205.467285f, 80.683838f},
        {205.562988f, 80.485596f},  {205.632324f, 80.267090f},  {205.697266f, 79.920166f},  {205.782227f, 79.615723f},
        {205.884766f, 79.349609f},  {206.005371f, 79.118896f},  {206.142090f, 78.919434f},  {206.294922f, 78.747314f},
        {206.461426f, 78.599121f},  {206.641602f, 78.471191f},  {206.834473f, 78.359375f},  {207.095703f, 78.117188f},
        {207.333008f, 77.872314f},  {207.547363f, 77.622559f},  {207.736816f, 77.365967f},  {207.901855f, 77.100098f},
        {208.041992f, 76.823730f},  {208.157227f, 76.534180f},  {208.247070f, 76.229736f},  {208.310059f, 75.907959f},
        {208.343750f, 75.598877f},  {208.392090f, 75.313965f},  {208.452637f, 75.050537f},  {208.523438f, 74.807129f},
        {208.604004f, 74.581299f},  {208.692871f, 74.370850f},  {208.788086f, 74.174072f},  {208.889160f, 73.988281f},
        {208.993652f, 73.812012f},  {209.208984f, 73.434082f},  {209.382812f, 73.044434f},  {209.525879f, 72.648193f},
        {209.649902f, 72.250488f},  {209.764648f, 71.856689f},  {209.881836f, 71.471680f},  {210.011230f, 71.100586f},
        {210.165039f, 70.748291f},  {210.353516f, 70.420654f},  {210.426758f, 70.255615f},  {210.487305f, 70.106689f},
        {210.533691f, 69.972656f},  {210.566406f, 69.851562f},  {210.586914f, 69.741943f},  {210.594727f, 69.641846f},
        {210.590332f, 69.549805f},  {210.574707f, 69.464600f},  {210.546875f, 69.384033f},  {210.422852f, 69.443115f},
        {210.301758f, 69.508545f},  {210.182617f, 69.578613f},  {210.065430f, 69.652100f},  {209.948730f, 69.727051f},
        {209.833008f, 69.802246f},  {209.716797f, 69.876221f},  {209.600586f, 69.947510f},  {209.482422f, 70.014160f},
        {209.352051f, 70.082520f},  {209.237793f, 70.154053f},  {209.139648f, 70.229004f},  {209.058105f, 70.307617f},
        {208.994629f, 70.389648f},  {208.950195f, 70.475586f},  {208.924316f, 70.565186f},  {208.917969f, 70.658936f},
        {208.933105f, 70.756348f},  {209.036621f, 71.043213f},  {209.087891f, 71.302002f},  {209.092285f, 71.536865f},
        {209.058594f, 71.751465f},  {208.993652f, 71.949707f},  {208.906250f, 72.135742f},  {208.803223f, 72.313477f},
        {208.691895f, 72.486328f},  {208.580078f, 72.658936f},
    };  // data size = 1261

    Vec2 vertices4[] = {
        {29.895508f, 90.680420f},  {29.844238f, 90.800293f},  {29.795898f, 90.923828f},  {29.749023f, 91.048096f},
        {29.699707f, 91.171143f},  {29.646973f, 91.290283f},  {29.587891f, 91.403076f},  {29.520508f, 91.507568f},
        {29.441895f, 91.600830f},  {29.350586f, 91.680664f},  {28.963379f, 91.887451f},  {28.601074f, 92.114990f},
        {28.263672f, 92.363770f},  {27.949219f, 92.634277f},  {27.656738f, 92.927246f},  {27.386719f, 93.243408f},
        {27.136230f, 93.583496f},  {26.905273f, 93.947998f},  {26.693359f, 94.337891f},  {26.509277f, 94.689941f},
        {26.310059f, 94.962646f},  {26.100098f, 95.166016f},  {25.882324f, 95.310791f},  {25.658691f, 95.406494f},
        {25.434570f, 95.464111f},  {25.211914f, 95.493164f},  {24.994141f, 95.504639f},  {24.785156f, 95.508545f},
        {24.435059f, 95.542969f},  {24.115723f, 95.606445f},  {23.824219f, 95.697266f},  {23.558594f, 95.815186f},
        {23.314453f, 95.958984f},  {23.090820f, 96.127441f},  {22.883789f, 96.320068f},  {22.689941f, 96.535400f},
        {22.508789f, 96.772705f},  {22.398438f, 96.953125f},  {22.300781f, 97.128174f},  {22.213379f, 97.293945f},
        {22.131836f, 97.446533f},  {22.051758f, 97.582275f},  {21.971191f, 97.697266f},  {21.884766f, 97.787842f},
        {21.790039f, 97.849854f},  {21.684082f, 97.879639f},  {21.551270f, 97.842773f},  {21.445801f, 97.781738f},
        {21.361816f, 97.700195f},  {21.296387f, 97.602051f},  {21.246094f, 97.491699f},  {21.206543f, 97.372314f},
        {21.173828f, 97.248291f},  {21.144531f, 97.123291f},  {21.114746f, 97.001709f},  {21.070801f, 96.877441f},
        {21.026367f, 96.761230f},  {20.980469f, 96.651855f},  {20.933594f, 96.548584f},  {20.886719f, 96.450439f},
        {20.839844f, 96.356201f},  {20.792969f, 96.265869f},  {20.747559f, 96.177490f},  {20.703125f, 96.090820f},
        {20.605469f, 96.125244f},  {20.521484f, 96.169922f},  {20.451172f, 96.223145f},  {20.393066f, 96.283447f},
        {20.347168f, 96.349609f},  {20.311523f, 96.419678f},  {20.286133f, 96.492920f},  {20.270020f, 96.566895f},
        {20.262695f, 96.640869f},  {20.265137f, 97.175293f},  {20.236328f, 97.707764f},  {20.190430f, 98.237793f},
        {20.140625f, 98.764893f},  {20.101562f, 99.289551f},  {20.086426f, 99.810791f},  {20.109375f, 100.328857f},
        {20.184570f, 100.843018f}, {20.325684f, 101.353271f}, {20.484375f, 101.725586f}, {20.576660f, 102.054199f},
        {20.611328f, 102.343994f}, {20.595703f, 102.598877f}, {20.538086f, 102.822998f}, {20.446777f, 103.020996f},
        {20.330078f, 103.197266f}, {20.194336f, 103.355713f}, {20.049805f, 103.500732f}, {19.731445f, 103.790771f},
        {19.471680f, 104.014893f}, {19.259277f, 104.171631f}, {19.083008f, 104.260742f}, {18.930664f, 104.280762f},
        {18.791016f, 104.230713f}, {18.652832f, 104.109863f}, {18.504883f, 103.917725f}, {18.334961f, 103.652832f},
        {18.226074f, 103.474365f}, {18.125977f, 103.315918f}, {18.034180f, 103.175293f}, {17.949707f, 103.049561f},
        {17.872559f, 102.936035f}, {17.802246f, 102.832764f}, {17.737793f, 102.736572f}, {17.678711f, 102.645264f},
        {17.624512f, 102.555908f}, {17.407715f, 102.146729f}, {17.221191f, 101.823975f}, {17.054688f, 101.585938f},
        {16.899902f, 101.429199f}, {16.745605f, 101.352051f}, {16.582520f, 101.351562f}, {16.400391f, 101.426270f},
        {16.189941f, 101.573242f}, {15.940430f, 101.790283f}, {15.429688f, 102.354248f}, {15.029785f, 102.935547f},
        {14.739258f, 103.529297f}, {14.556641f, 104.129639f}, {14.479980f, 104.730957f}, {14.507324f, 105.327637f},
        {14.637207f, 105.913818f}, {14.867676f, 106.483887f}, {15.197754f, 107.032959f}, {15.448242f, 107.322754f},
        {15.659180f, 107.583496f}, {15.831055f, 107.819824f}, {15.961426f, 108.037109f}, {16.049316f, 108.240967f},
        {16.093262f, 108.436279f}, {16.093262f, 108.628906f}, {16.047363f, 108.823486f}, {15.954590f, 109.025635f},
        {15.764648f, 109.289551f}, {15.583496f, 109.544678f}, {15.414062f, 109.795410f}, {15.258789f, 110.043945f},
        {15.119141f, 110.294189f}, {14.998535f, 110.549316f}, {14.898926f, 110.812744f}, {14.822754f, 111.087646f},
        {14.771484f, 111.377686f}, {14.749512f, 111.634521f}, {14.707520f, 111.848633f}, {14.647461f, 112.020752f},
        {14.571289f, 112.151611f}, {14.480469f, 112.241943f}, {14.376953f, 112.292725f}, {14.262207f, 112.304688f},
        {14.138184f, 112.278564f}, {14.006348f, 112.215332f}, {13.849121f, 112.088623f}, {13.697266f, 111.968750f},
        {13.552734f, 111.853516f}, {13.413574f, 111.741943f}, {13.280762f, 111.632324f}, {13.153809f, 111.523193f},
        {13.033203f, 111.413086f}, {12.918457f, 111.300537f}, {12.810059f, 111.184326f}, {12.630371f, 110.979980f},
        {12.474121f, 110.842285f}, {12.338867f, 110.764404f}, {12.222168f, 110.740723f}, {12.122070f, 110.764648f},
        {12.035156f, 110.830566f}, {11.960449f, 110.931885f}, {11.895996f, 111.062256f}, {11.837402f, 111.216309f},
        {11.741699f, 111.542725f}, {11.649414f, 111.860107f}, {11.560547f, 112.169922f}, {11.475098f, 112.472656f},
        {11.392578f, 112.769775f}, {11.312500f, 113.062256f}, {11.236328f, 113.351074f}, {11.162109f, 113.637939f},
        {11.091797f, 113.923096f}, {11.036133f, 114.164795f}, {10.988281f, 114.390625f}, {10.948730f, 114.603027f},
        {10.920410f, 114.804199f}, {10.903809f, 114.996094f}, {10.901367f, 115.181396f}, {10.914062f, 115.361816f},
        {10.943848f, 115.539551f}, {10.992188f, 115.716553f}, {11.117188f, 116.055664f}, {11.203613f, 116.391357f},
        {11.256836f, 116.723145f}, {11.283691f, 117.051025f}, {11.289551f, 117.375977f}, {11.281738f, 117.697021f},
        {11.265625f, 118.015137f}, {11.247070f, 118.329834f}, {11.232910f, 118.641846f}, {11.265625f, 118.746338f},
        {11.298340f, 118.829102f}, {11.331055f, 118.891602f}, {11.363770f, 118.935791f}, {11.395996f, 118.963867f},
        {11.427734f, 118.977295f}, {11.459961f, 118.978271f}, {11.491699f, 118.968262f}, {11.523438f, 118.949463f},
        {11.620117f, 118.828613f}, {11.700195f, 118.701904f}, {11.764648f, 118.569580f}, {11.816895f, 118.433350f},
        {11.859375f, 118.293213f}, {11.894531f, 118.150879f}, {11.923828f, 118.006592f}, {11.949707f, 117.861572f},
        {11.975586f, 117.716553f}, {12.035156f, 117.482910f}, {12.108887f, 117.294678f}, {12.195801f, 117.148193f},
        {12.294434f, 117.039062f}, {12.403809f, 116.964355f}, {12.521484f, 116.919922f}, {12.646973f, 116.902100f},
        {12.777832f, 116.907227f}, {12.914062f, 116.931641f}, {13.098145f, 117.006104f}, {13.235352f, 117.093262f},
        {13.331055f, 117.191406f}, {13.391113f, 117.298828f}, {13.418945f, 117.413574f}, {13.420898f, 117.534424f},
        {13.401367f, 117.658936f}, {13.365723f, 117.786133f}, {13.319824f, 117.913574f}, {13.182129f, 118.281738f},
        {13.080078f, 118.646729f}, {13.009766f, 119.009033f}, {12.966309f, 119.368164f}, {12.944336f, 119.725342f},
        {12.939941f, 120.080322f}, {12.947754f, 120.433105f}, {12.963379f, 120.784180f}, {12.981934f, 121.134033f},
        {12.994141f, 121.351318f}, {13.012695f, 121.548340f}, {13.038574f, 121.724854f}, {13.073730f, 121.880127f},
        {13.119629f, 122.014648f}, {13.176270f, 122.127441f}, {13.247070f, 122.218994f}, {13.331055f, 122.288818f},
        {13.432129f, 122.335938f}, {13.595215f, 122.344971f}, {13.736328f, 122.328125f}, {13.858887f, 122.287354f},
        {13.963867f, 122.226074f}, {14.053223f, 122.146240f}, {14.128418f, 122.051025f}, {14.192871f, 121.943115f},
        {14.246094f, 121.824463f}, {14.291992f, 121.697998f}, {14.350586f, 121.465820f}, {14.394531f, 121.238770f},
        {14.424805f, 121.017090f}, {14.444336f, 120.799561f}, {14.455078f, 120.585693f}, {14.458984f, 120.375488f},
        {14.458984f, 120.168213f}, {14.457031f, 119.963135f}, {14.454590f, 119.760010f}, {14.460938f, 119.498047f},
        {14.479492f, 119.258789f}, {14.511230f, 119.043213f}, {14.559082f, 118.850830f}, {14.624023f, 118.682129f},
        {14.708496f, 118.536865f}, {14.814453f, 118.415771f}, {14.942871f, 118.318359f}, {15.097656f, 118.245850f},
        {15.179199f, 118.223389f}, {15.251465f, 118.203369f}, {15.314453f, 118.185059f}, {15.370117f, 118.167969f},
        {15.418945f, 118.152588f}, {15.461914f, 118.138184f}, {15.500977f, 118.124756f}, {15.536621f, 118.111816f},
        {15.569824f, 118.099121f}, {15.750000f, 118.023438f}, {15.948242f, 117.975830f}, {16.155273f, 117.943848f},
        {16.363281f, 117.915771f}, {16.561523f, 117.878174f}, {16.742676f, 117.819336f}, {16.896973f, 117.726318f},
        {17.015625f, 117.586914f}, {17.090332f, 117.388184f}, {17.061035f, 117.037109f}, {16.981934f, 116.767578f},
        {16.860840f, 116.568115f}, {16.705566f, 116.426514f}, {16.524414f, 116.331299f}, {16.324707f, 116.270508f},
        {16.114746f, 116.232178f}, {15.901367f, 116.205078f}, {15.694336f, 116.177002f}, {15.586426f, 116.150879f},
        {15.489258f, 116.125488f}, {15.401855f, 116.098877f}, {15.322266f, 116.068359f}, {15.250488f, 116.032227f},
        {15.184570f, 115.987305f}, {15.123047f, 115.931396f}, {15.065430f, 115.862549f}, {15.009766f, 115.778076f},
        {15.419434f, 115.498047f}, {15.762207f, 115.177979f}, {16.043945f, 114.820801f}, {16.269531f, 114.429443f},
        {16.443359f, 114.007324f}, {16.572266f, 113.556641f}, {16.659668f, 113.081055f}, {16.712891f, 112.583496f},
        {16.734375f, 112.066895f}, {16.736816f, 111.754150f}, {16.752441f, 111.472168f}, {16.782227f, 111.219971f},
        {16.825684f, 110.996094f}, {16.881836f, 110.799316f}, {16.952148f, 110.628174f}, {17.035156f, 110.481445f},
        {17.130859f, 110.357910f}, {17.239746f, 110.255859f}, {17.862793f, 109.853760f}, {18.425293f, 109.398926f},
        {18.933594f, 108.897217f}, {19.393555f, 108.354004f}, {19.812988f, 107.774658f}, {20.196777f, 107.164551f},
        {20.552734f, 106.528809f}, {20.886230f, 105.873535f}, {21.204590f, 105.203857f}, {21.321289f, 104.901123f},
        {21.415527f, 104.633789f}, {21.488770f, 104.398438f}, {21.544922f, 104.190674f}, {21.585938f, 104.006836f},
        {21.613281f, 103.842773f}, {21.631348f, 103.694580f}, {21.641113f, 103.558350f}, {21.645508f, 103.429688f},
        {21.610840f, 103.069336f}, {21.606934f, 102.742188f}, {21.633789f, 102.448486f}, {21.693359f, 102.188721f},
        {21.786621f, 101.962891f}, {21.916016f, 101.771484f}, {22.081543f, 101.614502f}, {22.285645f, 101.491943f},
        {22.528809f, 101.404785f}, {22.671387f, 101.380615f}, {22.798828f, 101.354248f}, {22.911621f, 101.326660f},
        {23.012695f, 101.298340f}, {23.103516f, 101.269775f}, {23.185547f, 101.242432f}, {23.260742f, 101.215576f},
        {23.331055f, 101.190918f}, {23.398438f, 101.168945f}, {23.865723f, 101.043213f}, {24.236816f, 100.925293f},
        {24.517090f, 100.803711f}, {24.710449f, 100.667480f}, {24.821777f, 100.504395f}, {24.855469f, 100.303467f},
        {24.814453f, 100.053223f}, {24.705566f, 99.741943f},  {24.530762f, 99.358154f},  {24.411133f, 99.107178f},
        {24.321289f, 98.890869f},  {24.261230f, 98.706787f},  {24.227051f, 98.550293f},  {24.218262f, 98.418213f},
        {24.230957f, 98.307129f},  {24.264160f, 98.213135f},  {24.314941f, 98.132080f},  {24.381836f, 98.061523f},
        {24.756348f, 97.774658f},  {25.115723f, 97.474121f},  {25.461914f, 97.162354f},  {25.797363f, 96.841064f},
        {26.122070f, 96.512695f},  {26.439453f, 96.178955f},  {26.750977f, 95.842041f},  {27.057617f, 95.503906f},
        {27.362305f, 95.166992f},  {27.846191f, 94.645264f},  {28.319824f, 94.145264f},  {28.779785f, 93.661133f},
        {29.223633f, 93.185791f},  {29.650391f, 92.713623f},  {30.057129f, 92.238281f},  {30.441895f, 91.752686f},
        {30.802246f, 91.250977f},  {31.136230f, 90.726807f},  {31.279297f, 90.441895f},  {31.393066f, 90.182617f},
        {31.481934f, 89.947510f},  {31.551758f, 89.733398f},  {31.607422f, 89.538818f},  {31.653320f, 89.361084f},
        {31.695801f, 89.198242f},  {31.739258f, 89.048584f},  {31.788086f, 88.909180f},  {31.863770f, 88.787109f},
        {31.941895f, 88.677734f},  {32.019531f, 88.578613f},  {32.097656f, 88.487061f},  {32.173340f, 88.400391f},
        {32.246094f, 88.316162f},  {32.313477f, 88.231201f},  {32.375488f, 88.143311f},  {32.430176f, 88.050049f},
        {32.453613f, 87.963135f},  {32.470703f, 87.883057f},  {32.481934f, 87.809082f},  {32.486328f, 87.740479f},
        {32.483887f, 87.677246f},  {32.475098f, 87.618408f},  {32.458984f, 87.563965f},  {32.436523f, 87.512939f},
        {32.406738f, 87.464844f},  {32.168945f, 87.541748f},  {31.943848f, 87.632324f},  {31.734375f, 87.740234f},
        {31.543457f, 87.868896f},  {31.373047f, 88.021729f},  {31.224609f, 88.202393f},  {31.102539f, 88.414307f},
        {31.007812f, 88.660889f},  {30.943359f, 88.945557f},  {30.914062f, 89.246338f},  {30.864746f, 89.511963f},
        {30.795898f, 89.745117f},  {30.709961f, 89.948242f},  {30.606934f, 90.124023f},  {30.489258f, 90.274658f},
        {30.358398f, 90.403076f},  {30.215332f, 90.512207f},  {30.060547f, 90.604004f},
    };  // data size = 451

    Vec2 vertices5[] = {
        {57.639648f, 67.760254f},  {57.662109f, 67.569824f},  {57.684570f, 67.379639f},  {57.707031f, 67.189453f},
        {57.729980f, 66.999023f},  {57.751953f, 66.808838f},  {57.774414f, 66.618652f},  {57.796875f, 66.427979f},
        {57.819824f, 66.237793f},  {57.842285f, 66.047363f},  {57.727539f, 66.117432f},  {57.630859f, 66.210938f},
        {57.550781f, 66.324707f},  {57.483398f, 66.455322f},  {57.427734f, 66.599365f},  {57.381348f, 66.753662f},
        {57.341797f, 66.915283f},  {57.306152f, 67.080811f},  {57.273438f, 67.247070f},  {57.051270f, 68.128906f},
        {56.772949f, 68.965576f},  {56.449707f, 69.766113f},  {56.095703f, 70.538818f},  {55.722656f, 71.293457f},
        {55.343750f, 72.038818f},  {54.971191f, 72.783691f},  {54.617676f, 73.537109f},  {54.296387f, 74.308350f},
        {54.126465f, 74.789551f},  {53.951172f, 75.208496f},  {53.770996f, 75.571045f},  {53.585449f, 75.881836f},
        {53.393066f, 76.146484f},  {53.195312f, 76.370117f},  {52.990723f, 76.558350f},  {52.779297f, 76.716064f},
        {52.560059f, 76.849121f},  {52.437500f, 76.907227f},  {52.326172f, 76.961426f},  {52.227051f, 77.014648f},
        {52.140625f, 77.068115f},  {52.069336f, 77.124023f},  {52.012695f, 77.184814f},  {51.973633f, 77.252197f},
        {51.952637f, 77.328857f},  {51.950195f, 77.416016f},  {51.979004f, 77.509033f},  {52.014648f, 77.585205f},
        {52.055664f, 77.646484f},  {52.102539f, 77.694824f},  {52.153320f, 77.731445f},  {52.207031f, 77.759033f},
        {52.263184f, 77.779053f},  {52.320312f, 77.793457f},  {52.378418f, 77.804199f},  {52.514160f, 77.815918f},
        {52.651367f, 77.816650f},  {52.787598f, 77.814453f},  {52.920898f, 77.815430f},  {53.047852f, 77.826904f},
        {53.165527f, 77.855469f},  {53.270996f, 77.908691f},  {53.361816f, 77.993164f},  {53.434570f, 78.116455f},
        {53.464844f, 78.306641f},  {53.462402f, 78.472900f},  {53.431152f, 78.618164f},  {53.377930f, 78.746094f},
        {53.307129f, 78.859863f},  {53.225098f, 78.963623f},  {53.136719f, 79.060303f},  {53.046387f, 79.153320f},
        {52.960938f, 79.246338f},  {52.881348f, 79.354736f},  {52.805176f, 79.456543f},  {52.733887f, 79.554443f},
        {52.668457f, 79.649414f},  {52.610352f, 79.743896f},  {52.560547f, 79.838867f},  {52.519531f, 79.936768f},
        {52.490234f, 80.039307f},  {52.472656f, 80.148193f},  {52.341309f, 80.448730f},  {52.204590f, 80.742432f},
        {52.064453f, 81.030273f},  {51.924316f, 81.312744f},  {51.786133f, 81.590820f},  {51.651855f, 81.865479f},
        {51.524902f, 82.137207f},  {51.406738f, 82.407227f},  {51.299805f, 82.676514f},  {50.977051f, 83.717529f},
        {50.673340f, 84.752930f},  {50.393555f, 85.783447f},  {50.142578f, 86.810791f},  {49.925781f, 87.836182f},
        {49.746582f, 88.860840f},  {49.610840f, 89.885742f},  {49.522461f, 90.912354f},  {49.486328f, 91.941650f},
        {49.528809f, 92.923828f},  {49.558594f, 93.731934f},  {49.563477f, 94.389893f},  {49.531738f, 94.920654f},
        {49.448242f, 95.348877f},  {49.302246f, 95.697266f},  {49.080566f, 95.990234f},  {48.769043f, 96.251221f},
        {48.356934f, 96.503418f},  {47.946777f, 96.720703f},  {47.608887f, 96.936523f},  {47.339355f, 97.153320f},
        {47.136719f, 97.374512f},  {46.998047f, 97.603027f},  {46.919922f, 97.841553f},  {46.900391f, 98.093506f},
        {46.936035f, 98.361572f},  {47.024902f, 98.648926f},  {47.105957f, 98.815430f},  {47.182129f, 98.967529f},
        {47.252441f, 99.106689f},  {47.314941f, 99.233887f},  {47.367676f, 99.351074f},  {47.409668f, 99.458984f},
        {47.438965f, 99.558838f},  {47.453125f, 99.652100f},  {47.452148f, 99.740234f},  {47.309082f, 100.180176f},
        {47.171387f, 100.621338f}, {47.034668f, 101.060059f}, {46.896484f, 101.494385f}, {46.752930f, 101.920654f},
        {46.601074f, 102.336670f}, {46.437012f, 102.738770f}, {46.258301f, 103.124023f}, {46.060059f, 103.490234f},
        {45.838379f, 103.820312f}, {45.641602f, 104.127197f}, {45.469238f, 104.415527f}, {45.322266f, 104.690186f},
        {45.200195f, 104.955811f}, {45.104004f, 105.216553f}, {45.032715f, 105.477783f}, {44.987305f, 105.743408f},
        {44.968262f, 106.018799f}, {44.994629f, 106.631104f}, {44.994141f, 107.212891f}, {44.963867f, 107.765869f},
        {44.899414f, 108.291260f}, {44.797852f, 108.790283f}, {44.654297f, 109.264160f}, {44.466797f, 109.714111f},
        {44.230957f, 110.141602f}, {43.942383f, 110.548096f}, {43.680176f, 110.856934f}, {43.486328f, 111.156006f},
        {43.357910f, 111.443604f}, {43.291016f, 111.717529f}, {43.283203f, 111.976562f}, {43.330566f, 112.218750f},
        {43.430176f, 112.442139f}, {43.578125f, 112.645508f}, {43.771973f, 112.826904f}, {44.048340f, 112.997314f},
        {44.291992f, 113.165771f}, {44.502441f, 113.336182f}, {44.678223f, 113.513184f}, {44.818848f, 113.700684f},
        {44.923340f, 113.903076f}, {44.991211f, 114.124512f}, {45.020508f, 114.369385f}, {45.011230f, 114.641846f},
        {44.918457f, 115.008301f}, {44.805176f, 115.304932f}, {44.673828f, 115.539551f}, {44.525879f, 115.719238f},
        {44.362793f, 115.851318f}, {44.186035f, 115.943604f}, {43.999023f, 116.002930f}, {43.801270f, 116.037109f},
        {43.596680f, 116.053223f}, {43.292969f, 116.055176f}, {43.000488f, 116.058105f}, {42.722656f, 116.071289f},
        {42.460938f, 116.104492f}, {42.218750f, 116.166748f}, {41.997559f, 116.267822f}, {41.800293f, 116.417480f},
        {41.629883f, 116.624512f}, {41.488281f, 116.898926f}, {41.388184f, 117.401123f}, {41.333496f, 117.934326f},
        {41.319336f, 118.482910f}, {41.343750f, 119.031494f}, {41.402832f, 119.565186f}, {41.493164f, 120.067871f},
        {41.612305f, 120.525391f}, {41.756348f, 120.921631f}, {41.921387f, 121.241455f}, {42.120605f, 121.426758f},
        {42.312988f, 121.573975f}, {42.498535f, 121.685791f}, {42.678711f, 121.764648f}, {42.854980f, 121.813721f},
        {43.027832f, 121.835205f}, {43.198242f, 121.832275f}, {43.367676f, 121.807373f}, {43.536133f, 121.763672f},
        {43.689941f, 121.704834f}, {43.835938f, 121.651855f}, {43.973633f, 121.607910f}, {44.103516f, 121.577148f},
        {44.225586f, 121.563232f}, {44.340332f, 121.569092f}, {44.448242f, 121.599121f}, {44.548828f, 121.656250f},
        {44.642090f, 121.744385f}, {44.729980f, 121.904053f}, {44.792480f, 122.058594f}, {44.833008f, 122.208252f},
        {44.853027f, 122.353271f}, {44.855957f, 122.494385f}, {44.844238f, 122.631836f}, {44.820801f, 122.766602f},
        {44.787598f, 122.898682f}, {44.748047f, 123.028564f}, {44.734863f, 123.069580f}, {44.723145f, 123.105469f},
        {44.713867f, 123.137451f}, {44.705566f, 123.165283f}, {44.697754f, 123.189453f}, {44.690430f, 123.211182f},
        {44.683105f, 123.230225f}, {44.674316f, 123.247314f}, {44.665039f, 123.262695f}, {44.250488f, 123.823486f},
        {43.944824f, 124.400146f}, {43.735840f, 124.991211f}, {43.610352f, 125.596680f}, {43.554688f, 126.214844f},
        {43.555176f, 126.844971f}, {43.599121f, 127.485840f}, {43.673340f, 128.136963f}, {43.764648f, 128.796875f},
        {43.879883f, 129.736572f}, {43.963867f, 130.644043f}, {44.021973f, 131.522705f}, {44.059082f, 132.375977f},
        {44.079590f, 133.207031f}, {44.089355f, 134.019287f}, {44.092773f, 134.815918f}, {44.095215f, 135.600830f},

        {44.101074f, 136.376953f}, {44.107422f, 136.789551f}, {44.108887f, 137.160156f}, {44.110840f, 137.492432f},
        {44.115723f, 137.790283f}, {44.129883f, 138.057373f}, {44.155762f, 138.297119f}, {44.198730f, 138.513916f},
        {44.262207f, 138.710938f}, {44.352051f, 138.892822f}, {44.553711f, 139.066895f}, {44.725586f, 139.242920f},
        {44.866211f, 139.421631f}, {44.977539f, 139.605225f}, {45.060059f, 139.794678f}, {45.114746f, 139.991699f},
        {45.141602f, 140.197266f}, {45.142090f, 140.413086f}, {45.117188f, 140.640869f}, {45.039062f, 140.930420f},
        {44.954102f, 141.188477f}, {44.859375f, 141.415771f}, {44.754395f, 141.612549f}, {44.636719f, 141.779297f},
        {44.504883f, 141.916504f}, {44.358398f, 142.024170f}, {44.193848f, 142.102783f}, {44.012207f, 142.153076f},
        {43.806152f, 142.168945f}, {43.611816f, 142.193359f}, {43.430664f, 142.227051f}, {43.261230f, 142.271484f},
        {43.104004f, 142.328125f}, {42.958984f, 142.397949f}, {42.825684f, 142.482666f}, {42.705078f, 142.583740f},
        {42.596191f, 142.701660f}, {42.156738f, 143.344238f}, {41.691895f, 143.905518f}, {41.202148f, 144.391846f},
        {40.689941f, 144.809082f}, {40.155762f, 145.163330f}, {39.602539f, 145.460938f}, {39.030762f, 145.708008f},
        {38.441895f, 145.910645f}, {37.837891f, 146.074707f}, {37.551270f, 146.133057f}, {37.296875f, 146.186768f},
        {37.073242f, 146.239746f}, {36.877930f, 146.295898f}, {36.710449f, 146.359375f}, {36.567871f, 146.434326f},
        {36.448730f, 146.523926f}, {36.351562f, 146.632812f}, {36.274902f, 146.764648f}, {36.472656f, 147.114014f},
        {36.694336f, 147.388184f}, {36.937012f, 147.598389f}, {37.196289f, 147.755127f}, {37.469727f, 147.868652f},
        {37.753418f, 147.950195f}, {38.044434f, 148.010254f}, {38.338867f, 148.059570f}, {38.633301f, 148.108887f},
        {38.765137f, 148.134766f}, {38.881836f, 148.155029f}, {38.983887f, 148.170654f}, {39.074707f, 148.181641f},
        {39.154297f, 148.187744f}, {39.225098f, 148.190430f}, {39.289062f, 148.189941f}, {39.348633f, 148.185791f},
        {39.403320f, 148.179443f}, {39.780762f, 148.163818f}, {40.137207f, 148.113525f}, {40.475098f, 148.027832f},
        {40.794434f, 147.905762f}, {41.097168f, 147.746582f}, {41.383789f, 147.549316f}, {41.655762f, 147.312988f},
        {41.913574f, 147.037354f}, {42.158691f, 146.720947f}, {42.388672f, 146.360840f}, {42.619141f, 146.031494f},
        {42.852051f, 145.734375f}, {43.088867f, 145.471680f}, {43.333496f, 145.245361f}, {43.586914f, 145.056641f},
        {43.851562f, 144.908203f}, {44.128906f, 144.801270f}, {44.422363f, 144.737793f}, {44.660156f, 144.720947f},
        {44.863281f, 144.677002f}, {45.034180f, 144.608643f}, {45.176270f, 144.518066f}, {45.291016f, 144.407227f},
        {45.382324f, 144.279053f}, {45.451660f, 144.135498f}, {45.502930f, 143.978760f}, {45.537598f, 143.811768f},
        {45.580566f, 143.446533f}, {45.639160f, 143.100586f}, {45.713379f, 142.773438f}, {45.801758f, 142.462891f},
        {45.905762f, 142.167480f}, {46.023926f, 141.886719f}, {46.157715f, 141.617676f}, {46.305176f, 141.359619f},
        {46.467773f, 141.111572f}, {46.656250f, 140.848877f}, {46.814941f, 140.593506f}, {46.941895f, 140.344238f},
        {47.035645f, 140.099609f}, {47.096680f, 139.858154f}, {47.122559f, 139.618896f}, {47.113281f, 139.380371f},
        {47.066895f, 139.141602f}, {46.982910f, 138.900635f}, {46.851074f, 138.643311f}, {46.744141f, 138.393799f},
        {46.659180f, 138.151367f}, {46.594238f, 137.915283f}, {46.546875f, 137.683838f}, {46.512695f, 137.456787f},
        {46.491211f, 137.233398f}, {46.478027f, 137.011963f}, {46.471191f, 136.792236f}, {46.468750f, 136.015625f},
        {46.474121f, 135.249268f}, {46.478027f, 134.493896f}, {46.472656f, 133.749268f}, {46.448730f, 133.015137f},
        {46.397949f, 132.291260f}, {46.312012f, 131.577881f}, {46.181641f, 130.874756f}, {45.998535f, 130.181641f},
        {45.905762f, 129.921631f}, {45.831055f, 129.694824f}, {45.774902f, 129.498535f}, {45.735352f, 129.329590f},
        {45.709961f, 129.184082f}, {45.698242f, 129.059570f}, {45.699219f, 128.952148f}, {45.710449f, 128.859131f},
        {45.730469f, 128.776855f}, {45.893555f, 128.348389f}, {46.020996f, 127.912842f}, {46.121582f, 127.472656f},
        {46.203125f, 127.029297f}, {46.274902f, 126.585205f}, {46.345215f, 126.142090f}, {46.422363f, 125.702148f},
        {46.514648f, 125.267334f}, {46.630371f, 124.839600f}, {46.841797f, 124.272461f}, {46.991211f, 123.786865f},
        {47.077637f, 123.369141f}, {47.102539f, 123.005615f}, {47.063965f, 122.681396f}, {46.961914f, 122.383057f},
        {46.795410f, 122.096191f}, {46.564941f, 121.807129f}, {46.269531f, 121.501221f}, {46.030273f, 121.260498f},
        {45.857910f, 121.040283f}, {45.745605f, 120.840332f}, {45.687012f, 120.658936f}, {45.674805f, 120.495361f},
        {45.703125f, 120.348633f}, {45.765625f, 120.217529f}, {45.854492f, 120.101318f}, {45.964844f, 119.998779f},
        {46.323730f, 119.728760f}, {46.620117f, 119.436279f}, {46.859375f, 119.122559f}, {47.046875f, 118.789062f},
        {47.187500f, 118.437012f}, {47.286133f, 118.067383f}, {47.348633f, 117.681396f}, {47.379395f, 117.280029f},
        {47.385254f, 116.864746f}, {47.362305f, 116.523682f}, {47.329102f, 116.214600f}, {47.285156f, 115.933838f},
        {47.230957f, 115.678711f}, {47.165527f, 115.445068f}, {47.090332f, 115.229980f}, {47.004883f, 115.030273f},
        {46.908203f, 114.842041f}, {46.802246f, 114.662354f}, {46.403320f, 114.070312f}, {46.089355f, 113.543213f},
        {45.857910f, 113.065918f}, {45.709473f, 112.623047f}, {45.641602f, 112.200195f}, {45.653320f, 111.781982f},
        {45.743164f, 111.353027f}, {45.910645f, 110.898682f}, {46.154297f, 110.404053f}, {46.590332f, 109.650879f},
        {46.976562f, 108.916748f}, {47.312500f, 108.197266f}, {47.596191f, 107.487549f}, {47.826172f, 106.782959f},
        {48.001953f, 106.078613f}, {48.121094f, 105.370117f}, {48.183105f, 104.652344f}, {48.186523f, 103.921143f},
        {48.161621f, 103.504395f}, {48.168945f, 103.146729f}, {48.204102f, 102.841553f}, {48.263184f, 102.581055f},
        {48.340820f, 102.359619f}, {48.434570f, 102.169189f}, {48.538086f, 102.003662f}, {48.647949f, 101.855713f},
        {48.760254f, 101.718506f}, {49.012695f, 101.407715f}, {49.256348f, 101.105225f}, {49.480957f, 100.805420f},
        {49.673828f, 100.503906f}, {49.824219f, 100.195312f}, {49.921387f, 99.874756f},  {49.952637f, 99.536621f},
        {49.908203f, 99.176514f},  {49.775391f, 98.789062f},  {49.661133f, 98.572754f},  {49.586426f, 98.380127f},
        {49.546875f, 98.209473f},  {49.537598f, 98.057861f},  {49.553223f, 97.923584f},  {49.587891f, 97.804199f},
        {49.637207f, 97.697021f},  {49.695312f, 97.600586f},  {49.757812f, 97.511963f},  {49.895020f, 97.330322f},
        {50.034180f, 97.158691f},  {50.173828f, 96.993896f},  {50.311035f, 96.833252f},  {50.444824f, 96.673584f},
        {50.572266f, 96.512695f},  {50.691895f, 96.347168f},  {50.802734f, 96.174072f},  {50.901855f, 95.990967f},
        {50.946289f, 95.748047f},  {50.977051f, 95.516113f},  {50.995117f, 95.293457f},  {51.003906f, 95.079346f},
        {51.004395f, 94.872314f},  {50.999023f, 94.671143f},  {50.990234f, 94.474609f},  {50.979004f, 94.282227f},
        {50.968262f, 94.091797f},  {50.951172f, 93.506348f},  {50.946777f, 92.937012f},  {50.961914f, 92.384033f},
        {51.000488f, 91.846924f},  {51.068848f, 91.326172f},  {51.171875f, 90.821045f},  {51.315430f, 90.331787f},
        {51.504395f, 89.858154f},  {51.744141f, 89.399902f},  {52.051270f, 88.916260f},  {52.276367f, 88.435303f},
        {52.432617f, 87.958008f},  {52.534668f, 87.485596f},  {52.595215f, 87.019531f},  {52.629883f, 86.560791f},
        {52.651367f, 86.110840f},  {52.673340f, 85.670654f},  {52.710449f, 85.241943f},  {52.828613f, 84.603760f},
        {52.934082f, 83.983643f},  {53.036133f, 83.381836f},  {53.143555f, 82.800293f},  {53.263672f, 82.240234f},
        {53.405273f, 81.702881f},  {53.576172f, 81.189697f},  {53.785156f, 80.701904f},  {54.041504f, 80.240723f},
        {54.204102f, 80.019043f},  {54.344238f, 79.813477f},  {54.462402f, 79.622070f},  {54.559082f, 79.443359f},
        {54.633301f, 79.276367f},  {54.686523f, 79.119629f},  {54.719238f, 78.971680f},  {54.730469f, 78.831055f},
        {54.722656f, 78.696289f},  {54.581543f, 78.077148f},  {54.520020f, 77.486328f},  {54.529785f, 76.922119f},
        {54.600586f, 76.383301f},  {54.723145f, 75.867432f},  {54.889648f, 75.373535f},  {55.089355f, 74.899658f},
        {55.314941f, 74.444092f},  {55.555664f, 74.005127f},  {55.923828f, 73.346436f},  {56.244141f, 72.701172f},
        {56.520508f, 72.066895f},  {56.757324f, 71.441162f},  {56.961426f, 70.822754f},  {57.135742f, 70.208740f},
        {57.286133f, 69.597656f},  {57.417480f, 68.987061f},  {57.534668f, 68.375000f},
    };  // data size = 559

    Vec2 vertices6[] = {
        {250.690430f, 217.840088f}, {250.542480f, 217.442139f}, {250.456055f, 217.040527f}, {250.419922f, 216.635498f},
        {250.421387f, 216.227783f}, {250.447754f, 215.816895f}, {250.486816f, 215.404541f}, {250.525879f, 214.990234f},
        {250.552734f, 214.574219f}, {250.555176f, 214.157959f}, {250.460938f, 213.241455f}, {250.407227f, 212.342041f},
        {250.382324f, 211.458984f}, {250.370117f, 210.590820f}, {250.358887f, 209.736572f}, {250.333984f, 208.895508f},
        {250.281738f, 208.066406f}, {250.189453f, 207.248535f}, {250.042480f, 206.440918f}, {249.925293f, 205.992920f},
        {249.847656f, 205.584229f}, {249.807617f, 205.212402f}, {249.801758f, 204.874268f}, {249.829590f, 204.567383f},
        {249.887207f, 204.289551f}, {249.973145f, 204.037842f}, {250.084473f, 203.809814f}, {250.219238f, 203.602539f},
        {250.377441f, 203.416504f}, {250.519043f, 203.234375f}, {250.644531f, 203.055176f}, {250.755859f, 202.878418f},
        {250.854980f, 202.703613f}, {250.944336f, 202.530273f}, {251.023926f, 202.357666f}, {251.096680f, 202.184814f},
        {251.164551f, 202.011475f}, {251.237305f, 201.790771f}, {251.295410f, 201.581299f}, {251.336914f, 201.381836f},
        {251.358887f, 201.191895f}, {251.363281f, 201.010742f}, {251.345703f, 200.837646f}, {251.307617f, 200.672119f},
        {251.246094f, 200.513184f}, {251.160645f, 200.360107f}, {251.010742f, 200.198486f}, {250.866699f, 200.080811f},
        {250.726562f, 200.001709f}, {250.591309f, 199.956787f}, {250.458496f, 199.941895f}, {250.327637f, 199.951660f},
        {250.198730f, 199.981934f}, {250.069336f, 200.027832f}, {249.939453f, 200.084717f}, {249.590820f, 200.234619f},
        {249.276855f, 200.325684f}, {248.995605f, 200.357422f}, {248.746094f, 200.330322f}, {248.527832f, 200.243652f},
        {248.337891f, 200.097900f}, {248.175293f, 199.892822f}, {248.039551f, 199.628662f}, {247.928223f, 199.304932f},
        {247.869629f, 199.004150f}, {247.818848f, 198.722900f}, {247.774414f, 198.458740f}, {247.736816f, 198.210205f},
        {247.705078f, 197.974854f}, {247.679199f, 197.750488f}, {247.658691f, 197.535156f}, {247.643066f, 197.326660f},
        {247.631836f, 197.122559f}, {247.630859f, 196.703613f}, {247.656250f, 196.350342f}, {247.708984f, 196.057861f},
        {247.793945f, 195.821045f}, {247.914062f, 195.634277f}, {248.071777f, 195.492676f}, {248.270508f, 195.391357f},
        {248.513672f, 195.324463f}, {248.804688f, 195.287598f}, {249.432129f, 195.277344f}, {249.941895f, 195.254883f},
        {250.347168f, 195.209961f}, {250.663086f, 195.133301f}, {250.901855f, 195.016113f}, {251.077637f, 194.847900f},
        {251.206055f, 194.619629f}, {251.299316f, 194.321777f}, {251.372559f, 193.945068f}, {251.417480f, 193.559814f},
        {251.443359f, 193.211426f}, {251.446777f, 192.899170f}, {251.423828f, 192.622803f}, {251.371094f, 192.382080f},
        {251.285645f, 192.176514f}, {251.162598f, 192.006104f}, {251.000977f, 191.870361f}, {250.794922f, 191.769287f},
        {250.607422f, 191.726318f}, {250.433105f, 191.677979f}, {250.273926f, 191.623291f}, {250.129883f, 191.559570f},
        {250.000488f, 191.484619f}, {249.887207f, 191.396729f}, {249.791016f, 191.293945f}, {249.710449f, 191.173828f},
        {249.647949f, 191.034180f}, {249.611816f, 190.819092f}, {249.605469f, 190.632568f}, {249.625000f, 190.471191f},
        {249.666504f, 190.330566f}, {249.726562f, 190.207031f}, {249.801758f, 190.096191f}, {249.888184f, 189.994141f},
        {249.980957f, 189.896973f}, {250.077637f, 189.800537f}, {250.326172f, 189.521729f}, {250.556152f, 189.239502f},
        {250.765625f, 188.950928f}, {250.950684f, 188.654053f}, {251.107910f, 188.345459f}, {251.234375f, 188.023438f},
        {251.328613f, 187.685059f}, {251.385742f, 187.327393f}, {251.403320f, 186.948975f}, {251.377930f, 186.638916f},
        {251.360840f, 186.349854f}, {251.350098f, 186.079102f}, {251.345215f, 185.824463f}, {251.344727f, 185.583740f},
        {251.347656f, 185.354736f}, {251.353516f, 185.135010f}, {251.358887f, 184.922852f}, {251.365234f, 184.715576f},
        {251.367676f, 184.574219f}, {251.370605f, 184.435303f}, {251.374023f, 184.301758f}, {251.379395f, 184.176025f},
        {251.385742f, 184.061279f}, {251.394043f, 183.959473f}, {251.405273f, 183.874023f}, {251.419434f, 183.807373f},
        {251.437012f, 183.762451f}, {251.850098f, 183.567383f}, {252.159180f, 183.294922f}, {252.385254f, 182.960205f},
        {252.549805f, 182.579102f}, {252.671387f, 182.166748f}, {252.771484f, 181.738281f}, {252.870605f, 181.309082f},
        {252.988281f, 180.894775f}, {253.145508f, 180.510254f}, {253.385254f, 180.177246f}, {253.586914f, 179.854492f},
        {253.746094f, 179.540527f}, {253.861328f, 179.233887f}, {253.927734f, 178.933350f}, {253.942871f, 178.637207f},
        {253.902832f, 178.343994f}, {253.806152f, 178.052490f}, {253.647461f, 177.760498f}, {253.453613f, 177.503418f},
        {253.315430f, 177.266602f}, {253.228516f, 177.049561f}, {253.189941f, 176.851807f}, {253.197266f, 176.672852f},
        {253.244629f, 176.511475f}, {253.329590f, 176.367676f}, {253.449219f, 176.240234f}, {253.599609f, 176.128662f},
        {253.668457f, 176.093750f}, {253.728027f, 176.064697f}, {253.779785f, 176.041504f}, {253.823730f, 176.022705f},
        {253.862305f, 176.008057f}, {253.895020f, 175.996094f}, {253.923340f, 175.986328f}, {253.948242f, 175.977783f},
        {253.971191f, 175.969727f}, {254.588379f, 175.685059f}, {255.091797f, 175.416992f}, {255.486816f, 175.148193f},
        {255.781738f, 174.861328f}, {255.982422f, 174.538086f}, {256.096191f, 174.161865f}, {256.130859f, 173.714600f},
        {256.091797f, 173.178223f}, {255.987305f, 172.535889f}, {255.876465f, 171.986816f}, {255.799316f, 171.487305f},
        {255.753418f, 171.032227f}, {255.736328f, 170.616455f}, {255.746094f, 170.234131f}, {255.779297f, 169.879883f},
        {255.834473f, 169.548584f}, {255.909180f, 169.234619f}, {256.000000f, 168.932373f}, {256.158691f, 168.485352f},
        {256.297852f, 168.052490f}, {256.416992f, 167.630859f}, {256.517090f, 167.218994f}, {256.599121f, 166.814941f},
        {256.663574f, 166.416504f}, {256.710938f, 166.021973f}, {256.742676f, 165.629395f}, {256.759277f, 165.236328f},
        {256.764160f, 164.735107f}, {256.790039f, 164.264160f}, {256.837891f, 163.822510f}, {256.909668f, 163.408936f},
        {257.004883f, 163.022217f}, {257.126465f, 162.661621f}, {257.275391f, 162.325439f}, {257.452148f, 162.012939f},
        {257.658203f, 161.723145f}, {257.891113f, 161.446045f}, {258.068359f, 161.171143f}, {258.199219f, 160.898682f},
        {258.292480f, 160.629883f}, {258.356445f, 160.364746f}, {258.401367f, 160.104004f}, {258.435059f, 159.848633f},
        {258.467285f, 159.599365f}, {258.506348f, 159.356201f}, {258.085449f, 159.720947f}, {257.702148f, 160.125244f},
        {257.354492f, 160.567871f}, {257.041504f, 161.046875f}, {256.762695f, 161.561279f}, {256.517578f, 162.109131f},
        {256.304688f, 162.689453f}, {256.123047f, 163.300293f}, {255.972656f, 163.940918f}, {255.881348f, 164.447510f},
        {255.782227f, 164.915283f}, {255.674316f, 165.348389f}, {255.557129f, 165.749756f}, {255.432129f, 166.123779f},
        {255.297363f, 166.473389f}, {255.153809f, 166.802490f}, {255.000488f, 167.114502f}, {254.837891f, 167.413330f},
        {254.638184f, 167.750732f}, {254.458008f, 168.082275f}, {254.294434f, 168.407715f}, {254.145996f, 168.728027f},
        {254.009766f, 169.043457f}, {253.884277f, 169.354248f}, {253.766602f, 169.660889f}, {253.653809f, 169.963867f},
        {253.545410f, 170.263184f}, {253.477539f, 170.468506f}, {253.429688f, 170.661133f}, {253.398926f, 170.841797f},
        {253.387207f, 171.010742f}, {253.392090f, 171.168457f}, {253.414551f, 171.316406f}, {253.453613f, 171.454102f},
        {253.508301f, 171.582764f}, {253.578125f, 171.702637f}, {253.666504f, 171.808105f}, {253.751465f, 171.906494f},
        {253.832031f, 171.999756f}, {253.908691f, 172.088623f}, {253.982422f, 172.174316f}, {254.051270f, 172.257812f},
        {254.116699f, 172.340088f}, {254.177734f, 172.422852f}, {254.234863f, 172.506592f}, {254.345703f, 172.666504f},
        {254.472656f, 172.811035f}, {254.606934f, 172.946045f}, {254.739746f, 173.076904f}, {254.863770f, 173.208496f},
        {254.969727f, 173.347168f}, {255.048828f, 173.497559f}, {255.093262f, 173.665527f}, {255.094727f, 173.856201f},
        {254.994141f, 174.128906f}, {254.876953f, 174.367188f}, {254.744629f, 174.573730f}, {254.598633f, 174.752197f},
        {254.441895f, 174.905029f}, {254.276367f, 175.035156f}, {254.102051f, 175.145752f}, {253.923340f, 175.239258f},
        {253.740723f, 175.319336f}, {253.573730f, 175.372559f}, {253.415039f, 175.411865f}, {253.263672f, 175.440430f},
        {253.119629f, 175.461914f}, {252.980469f, 175.479248f}, {252.847656f, 175.495850f}, {252.717773f, 175.515137f},
        {252.592285f, 175.539795f}, {252.468750f, 175.573730f}, {252.303711f, 175.645508f}, {252.149414f, 175.717041f},
        {252.007324f, 175.791260f}, {251.876465f, 175.870850f}, {251.758789f, 175.958740f}, {251.654297f, 176.058105f},
        {251.564941f, 176.171143f}, {251.490723f, 176.301514f}, {251.432617f, 176.451172f}, {251.403809f, 176.672852f},
        {251.403809f, 176.863281f}, {251.430176f, 177.026855f}, {251.478027f, 177.167969f}, {251.543945f, 177.289795f},
        {251.624512f, 177.397705f}, {251.714844f, 177.495361f}, {251.812500f, 177.586914f}, {251.913574f, 177.676514f},
        {252.145020f, 177.932617f}, {252.325684f, 178.206055f}, {252.456543f, 178.491455f}, {252.538086f, 178.784912f},
        {252.571777f, 179.081055f}, {252.558105f, 179.375977f}, {252.498047f, 179.664795f}, {252.392090f, 179.943115f},
        {252.241699f, 180.206299f}, {252.139160f, 180.327393f}, {252.046875f, 180.436523f}, {251.962891f, 180.532227f},
        {251.886230f, 180.614502f}, {251.814453f, 180.681885f}, {251.745605f, 180.734131f}, {251.678223f, 180.769775f},
        {251.611328f, 180.788330f}, {251.541504f, 180.789062f}, {251.197754f, 180.695557f}, {250.931152f, 180.682617f},
        {250.731934f, 180.739014f}, {250.591797f, 180.853516f}, {250.501953f, 181.015381f}, {250.455566f, 181.213623f},
        {250.442383f, 181.437256f}, {250.454590f, 181.675049f}, {250.483398f, 181.916260f}, {250.520508f, 182.167236f},
        {250.543457f, 182.387451f}, {250.549805f, 182.579834f}, {250.540039f, 182.747803f}, {250.511719f, 182.895752f},
        {250.465332f, 183.026367f}, {250.399414f, 183.143555f}, {250.312988f, 183.250732f}, {250.204102f, 183.351807f},
        {249.840332f, 183.649658f}, {249.536133f, 183.986572f}, {249.281250f, 184.355469f}, {249.066406f, 184.748535f},
        {248.881348f, 185.159180f}, {248.716309f, 185.580566f}, {248.561035f, 186.004883f}, {248.405273f, 186.425537f},
        {248.239746f, 186.834961f}, {248.126465f, 187.069092f}, {248.025391f, 187.289062f}, {247.936523f, 187.495117f},
        {247.855957f, 187.688721f}, {247.782715f, 187.870850f}, {247.714844f, 188.042236f}, {247.650391f, 188.204590f},
        {247.587891f, 188.358154f}, {247.524902f, 188.504395f}, {247.357422f, 188.873535f}, {247.228516f, 189.225098f},
        {247.139160f, 189.561768f}, {247.088867f, 189.885498f}, {247.077637f, 190.198730f}, {247.106934f, 190.504395f},
        {247.175781f, 190.804688f}, {247.286133f, 191.101807f}, {247.436523f, 191.398193f}, {247.606445f, 191.659668f},
        {247.744141f, 191.903809f}, {247.850098f, 192.133545f}, {247.925293f, 192.350586f}, {247.970215f, 192.557861f},
        {247.984863f, 192.757568f}, {247.969727f, 192.952148f}, {247.925293f, 193.143555f}, {247.852539f, 193.335205f},
        {247.697266f, 193.605225f}, {247.547363f, 193.865234f}, {247.403809f, 194.116943f}, {247.267578f, 194.362549f},
        {247.139648f, 194.604248f}, {247.020508f, 194.843994f}, {246.910156f, 195.083984f}, {246.810059f, 195.326172f},
        {246.720703f, 195.572754f}, {246.532227f, 196.300537f}, {246.380859f, 197.020020f}, {246.261719f, 197.731445f},
        {246.171875f, 198.436523f}, {246.106934f, 199.134766f}, {246.064453f, 199.827637f}, {246.040039f, 200.515625f},
        {246.030273f, 201.199951f}, {246.031250f, 201.880859f}, {246.058594f, 202.325928f}, {246.124023f, 202.723877f},
        {246.223145f, 203.075684f}, {246.351562f, 203.383789f}, {246.505859f, 203.650391f}, {246.681152f, 203.877686f},
        {246.873535f, 204.067383f}, {247.078125f, 204.221680f}, {247.291504f, 204.342773f}, {247.586426f, 204.463623f},
        {247.841797f, 204.601562f}, {248.060547f, 204.756104f}, {248.245117f, 204.926270f}, {248.398438f, 205.111816f},
        {248.522949f, 205.312500f}, {248.621582f, 205.527832f}, {248.698242f, 205.757080f}, {248.753906f, 206.000000f},
        {248.803223f, 206.381348f}, {248.854004f, 206.744873f}, {248.910156f, 207.091797f}, {248.973633f, 207.423340f},
        {249.045898f, 207.740234f}, {249.130859f, 208.042969f}, {249.230957f, 208.333252f}, {249.347168f, 208.612061f},
        {249.483398f, 208.879883f}, {249.575684f, 209.033691f}, {249.648438f, 209.175293f}, {249.701660f, 209.305908f},
        {249.735840f, 209.426270f}, {249.752930f, 209.537598f}, {249.752930f, 209.641113f}, {249.736816f, 209.737305f},
        {249.706055f, 209.827637f}, {249.660645f, 209.913330f}, {249.578613f, 210.006592f}, {249.499512f, 210.077637f},
        {249.421387f, 210.128906f}, {249.345703f, 210.161621f}, {249.270020f, 210.177246f}, {249.194824f, 210.177979f},
        {249.119629f, 210.164795f}, {249.043457f, 210.139648f}, {248.967285f, 210.104492f}, {248.468750f, 209.843262f},
        {248.015137f, 209.683105f}, {247.610840f, 209.622559f}, {247.259766f, 209.660400f}, {246.965820f, 209.795410f},
        {246.733887f, 210.025879f}, {246.566895f, 210.350098f}, {246.469238f, 210.767334f}, {246.445801f, 211.276123f},
        {246.538574f, 212.023438f}, {246.611328f, 212.732666f}, {246.662598f, 213.407471f}, {246.693848f, 214.053223f},
        {246.703613f, 214.674316f}, {246.691406f, 215.274902f}, {246.657227f, 215.860352f}, {246.600098f, 216.434814f},
        {246.520996f, 217.003418f}, {246.910645f, 217.404785f}, {247.309082f, 217.707275f}, {247.715332f, 217.920898f},
        {248.127930f, 218.057617f}, {248.546387f, 218.126953f}, {248.969727f, 218.140137f}, {249.396484f, 218.107422f},
        {249.826660f, 218.040039f}, {250.258789f, 217.947998f},
    };  // data size = 478

    Vec2 vertices7[] = {
        {165.370605f, 158.226807f}, {165.241211f, 158.470459f}, {165.140137f, 158.724365f}, {165.060547f, 158.986572f},
        {165.000488f, 159.255127f}, {164.952637f, 159.528320f}, {164.913574f, 159.804688f}, {164.877441f, 160.082031f},
        {164.840332f, 160.358398f}, {164.796875f, 160.632568f}, {164.662598f, 161.123535f}, {164.499023f, 161.573242f},
        {164.312988f, 161.989258f}, {164.110352f, 162.378418f}, {163.896484f, 162.747803f}, {163.679688f, 163.104736f},
        {163.464355f, 163.455322f}, {163.257812f, 163.807129f}, {163.064941f, 164.167725f}, {162.904297f, 164.564453f},
        {162.763672f, 164.945801f}, {162.639160f, 165.312012f}, {162.526367f, 165.663818f}, {162.422363f, 166.002441f},
        {162.321289f, 166.328613f}, {162.219727f, 166.643555f}, {162.113770f, 166.947998f}, {162.000488f, 167.242432f},
        {161.928711f, 167.412354f}, {161.877930f, 167.565430f}, {161.845703f, 167.702881f}, {161.830566f, 167.827393f},
        {161.829590f, 167.940674f}, {161.841797f, 168.044678f}, {161.864746f, 168.141357f}, {161.896973f, 168.232666f},
        {161.936035f, 168.320068f}, {162.068359f, 168.601807f}, {162.156250f, 168.868896f}, {162.202148f, 169.121094f},
        {162.207520f, 169.357666f}, {162.174805f, 169.577393f}, {162.105469f, 169.780273f}, {162.001953f, 169.964844f},
        {161.865723f, 170.130859f}, {161.700195f, 170.277100f}, {161.487305f, 170.409424f}, {161.308594f, 170.539551f},
        {161.164062f, 170.670166f}, {161.050781f, 170.802979f}, {160.968750f, 170.939941f}, {160.916016f, 171.083252f},
        {160.890625f, 171.234863f}, {160.893066f, 171.397217f}, {160.919922f, 171.571777f}, {160.961426f, 171.724854f},
        {160.988770f, 171.864014f}, {161.003418f, 171.990479f}, {161.007324f, 172.106201f}, {161.000488f, 172.212402f},
        {160.984863f, 172.310547f}, {160.962402f, 172.402588f}, {160.933105f, 172.489502f}, {160.899414f, 172.573486f},
        {160.691406f, 173.045166f}, {160.521484f, 173.518799f}, {160.385742f, 173.994629f}, {160.281250f, 174.472656f},
        {160.204590f, 174.954346f}, {160.154297f, 175.439697f}, {160.125977f, 175.928955f}, {160.117676f, 176.422852f},
        {160.125488f, 176.921631f}, {160.129395f, 177.335205f}, {160.101074f, 177.717529f}, {160.043457f, 178.070557f},
        {159.961426f, 178.396484f}, {159.857910f, 178.697754f}, {159.738281f, 178.976807f}, {159.604492f, 179.235352f},
        {159.461426f, 179.475830f}, {159.312988f, 179.700928f}, {159.095703f, 180.016602f}, {158.911133f, 180.324707f},
        {158.756836f, 180.627686f}, {158.630859f, 180.926758f}, {158.532227f, 181.224365f}, {158.459473f, 181.522217f},
        {158.411133f, 181.822998f}, {158.385742f, 182.128174f}, {158.381836f, 182.439941f}, {158.403809f, 182.874268f},
        {158.407227f, 183.292969f}, {158.400391f, 183.697021f}, {158.389160f, 184.087891f}, {158.380859f, 184.467041f},
        {158.382324f, 184.835693f}, {158.400879f, 185.194824f}, {158.442871f, 185.546143f}, {158.514648f, 185.890869f},
        {158.309082f, 186.287598f}, {158.112793f, 186.671143f}, {157.933105f, 187.045898f}, {157.776855f, 187.416748f},
        {157.649902f, 187.788330f}, {157.560059f, 188.165771f}, {157.513184f, 188.553955f}, {157.516602f, 188.957520f},
        {157.576660f, 189.381592f}, {157.646973f, 189.641846f}, {157.693848f, 189.881348f}, {157.716797f, 190.101562f},
        {157.717773f, 190.303223f}, {157.698730f, 190.487305f}, {157.661133f, 190.654785f}, {157.605469f, 190.806641f},
        {157.532715f, 190.943848f}, {157.445801f, 191.067627f}, {157.106445f, 191.428711f}, {156.808105f, 191.801025f},
        {156.550781f, 192.186279f}, {156.334473f, 192.585449f}, {156.158203f, 193.000000f}, {156.021973f, 193.430420f},
        {155.926270f, 193.878174f}, {155.869629f, 194.344482f}, {155.852051f, 194.830566f}, {155.882812f, 195.704590f},
        {155.850586f, 196.534668f}, {155.765625f, 197.327393f}, {155.638672f, 198.088379f}, {155.479004f, 198.822754f},
        {155.298828f, 199.536377f}, {155.107422f, 200.235107f}, {154.914551f, 200.924316f}, {154.731445f, 201.609863f},
        {154.630371f, 202.091553f}, {154.553711f, 202.526123f}, {154.503906f, 202.919189f}, {154.480469f, 203.276367f},
        {154.483887f, 203.602539f}, {154.515625f, 203.903320f}, {154.574707f, 204.184082f}, {154.663086f, 204.450439f},
        {154.780762f, 204.707275f}, {155.146973f, 205.322754f}, {155.426270f, 205.885010f}, {155.619629f, 206.404297f},
        {155.729004f, 206.890381f}, {155.752930f, 207.354248f}, {155.694336f, 207.804932f}, {155.552734f, 208.253906f},
        {155.328613f, 208.710449f}, {155.023926f, 209.185059f}, {154.847168f, 209.407227f}, {154.689941f, 209.599854f},
        {154.549316f, 209.766602f}, {154.424805f, 209.910889f}, {154.312988f, 210.036621f}, {154.212891f, 210.147461f},
        {154.123535f, 210.246826f}, {154.041504f, 210.338135f}, {153.964844f, 210.425049f}, {153.826660f, 210.612061f},
        {153.718750f, 210.792236f}, {153.643066f, 210.964844f}, {153.600098f, 211.128418f}, {153.591309f, 211.281982f},
        {153.617676f, 211.424316f}, {153.679688f, 211.554199f}, {153.778320f, 211.671143f}, {153.915039f, 211.773193f},
        {154.228027f, 211.926025f}, {154.480469f, 212.096924f}, {154.679199f, 212.286133f}, {154.828613f, 212.493408f},
        {154.935059f, 212.718750f}, {155.004395f, 212.961670f}, {155.041992f, 213.222656f}, {155.052734f, 213.500732f},
        {155.043457f, 213.796387f}, {154.990723f, 214.379395f}, {154.941406f, 214.946289f}, {154.893555f, 215.497803f},
        {154.848145f, 216.036621f}, {154.803711f, 216.563965f}, {154.759277f, 217.082275f}, {154.715820f, 217.593018f},
        {154.670898f, 218.097656f}, {154.625000f, 218.598633f}, {154.605469f, 218.788574f}, {154.587891f, 218.952393f},
        {154.571777f, 219.093262f}, {154.558594f, 219.213379f}, {154.548340f, 219.314941f}, {154.541992f, 219.400391f},
        {154.539551f, 219.473145f}, {154.542480f, 219.534424f}, {154.551270f, 219.587646f}, {154.823730f, 220.431641f},
        {154.974609f, 221.269775f}, {155.026367f, 222.104004f}, {155.000000f, 222.934082f}, {154.917969f, 223.761230f},
        {154.802246f, 224.586426f}, {154.674805f, 225.409668f}, {154.558594f, 226.232666f}, {154.474121f, 227.055420f},
        {154.460938f, 227.401611f}, {154.441406f, 227.706787f}, {154.418945f, 227.974609f}, {154.397461f, 228.208252f},
        {154.379883f, 228.410645f}, {154.370117f, 228.584717f}, {154.372070f, 228.734131f}, {154.389648f, 228.862061f},
        {154.425781f, 228.971436f}, {154.640137f, 229.283691f}, {154.784668f, 229.585449f}, {154.867188f, 229.877686f},
        {154.895996f, 230.161621f}, {154.879395f, 230.437988f}, {154.824707f, 230.708496f}, {154.741211f, 230.974121f},
        {154.636719f, 231.235352f}, {154.518555f, 231.494629f}, {154.350586f, 231.848145f}, {154.192383f, 232.188965f},
        {154.043457f, 232.518799f}, {153.906250f, 232.840576f}, {153.781250f, 233.156982f}, {153.668457f, 233.469727f},
        {153.569336f, 233.781982f}, {153.485352f, 234.095947f}, {153.416992f, 234.414307f}, {153.369629f, 234.682129f},
        {153.310547f, 234.909180f}, {153.240234f, 235.098877f}, {153.158203f, 235.254883f}, {153.064453f, 235.380127f},
        {152.959473f, 235.479004f}, {152.843262f, 235.554688f}, {152.715820f, 235.610596f}, {152.577637f, 235.650879f},
        {152.124023f, 235.760498f}, {151.721680f, 235.938232f}, {151.361816f, 236.172119f}, {151.037598f, 236.452148f},
        {150.740723f, 236.767334f}, {150.464355f, 237.106689f}, {150.199707f, 237.459717f}, {149.939453f, 237.815430f},
        {149.676758f, 238.162842f}, {149.768555f, 238.365234f}, {149.876953f, 238.538086f}, {150.000977f, 238.681152f},
        {150.138184f, 238.795166f}, {150.288086f, 238.880127f}, {150.448242f, 238.935791f}, {150.618652f, 238.962646f},
        {150.797363f, 238.960938f}, {150.982422f, 238.931152f}, {151.114746f, 238.858887f}, {151.229004f, 238.781738f},
        {151.327637f, 238.700195f}, {151.412598f, 238.615234f}, {151.486328f, 238.527588f}, {151.551270f, 238.438477f},
        {151.609863f, 238.347900f}, {151.664062f, 238.257080f}, {151.714844f, 238.166992f}, {151.826660f, 237.986572f},
        {151.936523f, 237.835693f}, {152.043945f, 237.717285f}, {152.149414f, 237.634521f}, {152.253418f, 237.591309f},
        {152.355469f, 237.590576f}, {152.456055f, 237.636230f}, {152.555664f, 237.731201f}, {152.655273f, 237.879395f},
        {152.735352f, 238.059814f}, {152.813965f, 238.226562f}, {152.892090f, 238.377197f}, {152.972168f, 238.509277f},
        {153.055664f, 238.620850f}, {153.145020f, 238.709717f}, {153.240723f, 238.772949f}, {153.346191f, 238.808838f},
        {153.462891f, 238.814941f}, {153.646973f, 238.751465f}, {153.818848f, 238.672852f}, {153.976562f, 238.579346f},
        {154.118164f, 238.471924f}, {154.242188f, 238.351807f}, {154.347168f, 238.218506f}, {154.430664f, 238.074219f},
        {154.490723f, 237.918701f}, {154.526367f, 237.752686f}, {154.533691f, 236.936768f}, {154.591797f, 236.150391f},
        {154.694336f, 235.389893f}, {154.837402f, 234.652100f}, {155.016113f, 233.934326f}, {155.223633f, 233.232666f},
        {155.457031f, 232.544434f}, {155.709473f, 231.866211f}, {155.977051f, 231.195312f}, {156.085449f, 230.924072f},
        {156.171387f, 230.684814f}, {156.235352f, 230.474854f}, {156.279297f, 230.291748f}, {156.304199f, 230.133789f},
        {156.310547f, 229.997559f}, {156.300781f, 229.881348f}, {156.274902f, 229.782715f}, {156.234375f, 229.698975f},
        {155.968262f, 229.349365f}, {155.786621f, 229.001465f}, {155.680664f, 228.655029f}, {155.638184f, 228.310791f},
        {155.648926f, 227.968506f}, {155.702637f, 227.629150f}, {155.787598f, 227.292480f}, {155.893555f, 226.958984f},
        {156.009766f, 226.628906f}, {156.157715f, 226.202393f}, {156.299316f, 225.793457f}, {156.436035f, 225.400391f},
        {156.567383f, 225.020996f}, {156.694824f, 224.653320f}, {156.818848f, 224.295410f}, {156.940918f, 223.945801f},
        {157.061035f, 223.602295f}, {157.181152f, 223.263184f}, {157.303223f, 222.892822f}, {157.395020f, 222.549072f},
        {157.456055f, 222.228271f}, {157.482422f, 221.928467f}, {157.473145f, 221.646973f}, {157.426270f, 221.381348f},
        {157.339355f, 221.128906f}, {157.211426f, 220.887451f}, {157.040039f, 220.654297f}, {156.710449f, 220.286865f},
        {156.469238f, 219.908203f}, {156.305176f, 219.519775f}, {156.207031f, 219.125488f}, {156.164551f, 218.727051f},
        {156.166992f, 218.328125f}, {156.203125f, 217.930664f}, {156.262695f, 217.538086f}, {156.334473f, 217.152344f},
        {156.412109f, 216.727539f}, {156.478516f, 216.324463f}, {156.533691f, 215.939453f}, {156.579102f, 215.571045f},
        {156.613770f, 215.216309f}, {156.639648f, 214.872314f}, {156.657715f, 214.537109f}, {156.666992f, 214.207275f},
        {156.668945f, 213.881348f}, {156.665039f, 213.667725f}, {156.659668f, 213.469482f}, {156.651855f, 213.285645f},
        {156.639648f, 213.116943f}, {156.621582f, 212.963135f}, {156.595703f, 212.823730f}, {156.561035f, 212.699219f},
        {156.515137f, 212.588867f}, {156.458008f, 212.492676f}, {156.177734f, 212.196045f}, {155.981445f, 211.918701f},
        {155.860840f, 211.657227f}, {155.809082f, 211.408447f}, {155.818848f, 211.169678f}, {155.884277f, 210.937012f},
        {155.997559f, 210.707275f}, {156.151367f, 210.477783f}, {156.338867f, 210.245117f}, {156.717285f, 209.744141f},
        {157.031738f, 209.146729f}, {157.282715f, 208.475098f}, {157.469238f, 207.751953f}, {157.590820f, 206.999512f},
        {157.647949f, 206.239990f}, {157.638672f, 205.496826f}, {157.563477f, 204.791504f}, {157.420898f, 204.146973f},
        {157.302246f, 203.861816f}, {157.196777f, 203.607666f}, {157.104492f, 203.380371f}, {157.027832f, 203.175781f},
        {156.964844f, 202.989746f}, {156.916016f, 202.818604f}, {156.882812f, 202.657227f}, {156.863770f, 202.502197f},
        {156.860352f, 202.348877f}, {156.945312f, 201.570312f}, {157.014648f, 200.797852f}, {157.075684f, 200.031250f},
        {157.133789f, 199.270752f}, {157.195312f, 198.516113f}, {157.267578f, 197.768311f}, {157.356934f, 197.026611f},
        {157.468262f, 196.291504f}, {157.609375f, 195.562988f}, {157.745117f, 195.008545f}, {157.857910f, 194.488037f},
        {157.953613f, 193.999268f}, {158.039062f, 193.539551f}, {158.121582f, 193.106689f}, {158.208008f, 192.698242f},
        {158.304199f, 192.312012f}, {158.417969f, 191.945557f}, {158.555176f, 191.596191f}, {158.666504f, 191.362793f},
        {158.747070f, 191.141846f}, {158.799805f, 190.931641f}, {158.829102f, 190.730957f}, {158.839844f, 190.538818f},
        {158.835449f, 190.354980f}, {158.819824f, 190.177246f}, {158.797852f, 190.005371f}, {158.773438f, 189.838135f},
        {158.734375f, 189.506348f}, {158.706055f, 189.185791f}, {158.693359f, 188.876465f}, {158.699707f, 188.578857f},
        {158.728516f, 188.293457f}, {158.783203f, 188.021240f}, {158.866699f, 187.761963f}, {158.983887f, 187.516602f},
        {159.137695f, 187.285645f}, {159.213379f, 187.193115f}, {159.278320f, 187.111572f}, {159.332520f, 187.040283f},
        {159.377930f, 186.977051f}, {159.415039f, 186.921143f}, {159.445312f, 186.870850f}, {159.470703f, 186.825195f},
        {159.491211f, 186.782715f}, {159.508789f, 186.742188f}, {159.607422f, 186.472900f}, {159.671387f, 186.202393f},
        {159.707031f, 185.931152f}, {159.720215f, 185.659668f}, {159.716797f, 185.388184f}, {159.702637f, 185.116943f},
        {159.684082f, 184.846680f}, {159.666504f, 184.577393f}, {159.656250f, 184.309814f}, {159.697754f, 183.643555f},
        {159.766113f, 183.000000f}, {159.856445f, 182.375977f}, {159.963867f, 181.768311f}, {160.082520f, 181.174316f},
        {160.208984f, 180.590576f}, {160.337402f, 180.013916f}, {160.462891f, 179.441406f}, {160.580566f, 178.869873f},
        {160.631836f, 178.581299f}, {160.677734f, 178.324463f}, {160.716797f, 178.095215f}, {160.749512f, 177.890137f},
        {160.775391f, 177.706055f}, {160.793945f, 177.538574f}, {160.804688f, 177.384766f}, {160.807129f, 177.240234f},
        {160.801758f, 177.101807f}, {160.766113f, 176.788086f}, {160.748047f, 176.489258f}, {160.748535f, 176.204102f},
        {160.768555f, 175.931641f}, {160.809082f, 175.670410f}, {160.872559f, 175.419434f}, {160.958496f, 175.177979f},
        {161.069336f, 174.943604f}, {161.206055f, 174.716797f}, {161.397949f, 174.449707f}, {161.557129f, 174.181641f},
        {161.687012f, 173.912354f}, {161.789551f, 173.641602f}, {161.870117f, 173.369629f}, {161.930664f, 173.096191f},
        {161.975586f, 172.822266f}, {162.008301f, 172.547363f}, {162.031250f, 172.271240f}, {162.047363f, 172.012939f},
        {162.065918f, 171.767822f}, {162.086914f, 171.535400f}, {162.113281f, 171.314453f}, {162.145508f, 171.104248f},
        {162.185547f, 170.904541f}, {162.234375f, 170.714355f}, {162.292969f, 170.532715f}, {162.364258f, 170.358643f},
        {162.447266f, 170.199463f}, {162.528320f, 170.049072f}, {162.605957f, 169.905762f}, {162.676270f, 169.768066f},
        {162.737793f, 169.634033f}, {162.787598f, 169.502197f}, {162.824707f, 169.371338f}, {162.844727f, 169.239502f},
        {162.846191f, 169.104980f}, {162.759766f, 168.551514f}, {162.734863f, 168.027100f}, {162.764160f, 167.528564f},
        {162.840332f, 167.052246f}, {162.956543f, 166.595215f}, {163.105957f, 166.153564f}, {163.280273f, 165.724609f},
        {163.473145f, 165.304443f}, {163.676758f, 164.890137f}, {163.825195f, 164.594482f}, {163.960449f, 164.320312f},
        {164.083984f, 164.064941f}, {164.196289f, 163.825928f}, {164.298340f, 163.600342f}, {164.392578f, 163.385498f},
        {164.478027f, 163.178711f}, {164.556641f, 162.977539f}, {164.628906f, 162.778809f}, {164.731934f, 162.293945f},
        {164.837402f, 161.821289f}, {164.941895f, 161.358154f}, {165.042969f, 160.903564f}, {165.135742f, 160.455078f},
        {165.218750f, 160.010498f}, {165.287109f, 159.568115f}, {165.337402f, 159.125000f}, {165.366699f, 158.679932f},
    };  // data size = 532

    Vec2 vertices8[] = {
        {215.615723f, 181.699707f}, {215.460938f, 181.938477f}, {215.300781f, 182.173340f}, {215.143555f, 182.408691f},
        {214.998535f, 182.648682f}, {214.875488f, 182.897949f}, {214.781250f, 183.160645f}, {214.726074f, 183.440674f},
        {214.718262f, 183.743164f}, {214.767090f, 184.071777f}, {214.838867f, 184.316406f}, {214.865723f, 184.523438f},
        {214.854492f, 184.698486f}, {214.812012f, 184.845703f}, {214.745117f, 184.969971f}, {214.659668f, 185.075928f},
        {214.562988f, 185.168457f}, {214.461914f, 185.251953f}, {214.362305f, 185.331299f}, {214.130371f, 185.567871f},
        {213.943848f, 185.789795f}, {213.802734f, 186.000488f}, {213.705078f, 186.203369f}, {213.649902f, 186.401611f},
        {213.636719f, 186.599121f}, {213.665039f, 186.799072f}, {213.732422f, 187.004639f}, {213.839355f, 187.219238f},
        {213.990234f, 187.431396f}, {214.131836f, 187.604736f}, {214.266602f, 187.738525f}, {214.395020f, 187.831299f},
        {214.520020f, 187.882812f}, {214.643555f, 187.891357f}, {214.767578f, 187.856201f}, {214.893555f, 187.776367f},
        {215.023438f, 187.650391f}, {215.341309f, 187.262695f}, {215.670898f, 186.958984f}, {216.009766f, 186.738525f},
        {216.353027f, 186.599609f}, {216.697754f, 186.541504f}, {217.041504f, 186.561768f}, {217.378906f, 186.659912f},
        {217.708496f, 186.834229f}, {218.025391f, 187.083008f}, {218.309082f, 187.385254f}, {218.582520f, 187.617676f},
        {218.848633f, 187.787109f}, {219.106445f, 187.901367f}, {219.356934f, 187.966797f}, {219.601562f, 187.990723f},
        {219.839844f, 187.980469f}, {220.073242f, 187.942871f}, {220.303223f, 187.884766f}, {220.631348f, 187.791992f},
        {220.917480f, 187.744141f}, {221.163574f, 187.741699f}, {221.370117f, 187.784668f}, {221.540527f, 187.873291f},
        {221.675781f, 188.007568f}, {221.778809f, 188.187744f}, {221.850586f, 188.414062f}, {221.893555f, 188.686768f},
        {221.901367f, 188.898193f}, {221.914062f, 189.089844f}, {221.932129f, 189.263428f}, {221.953125f, 189.421875f},
        {221.978516f, 189.567383f}, {222.007324f, 189.701660f}, {222.038574f, 189.827393f}, {222.073730f, 189.947021f},
        {222.110352f, 190.062744f}, {222.200195f, 190.294678f}, {222.299316f, 190.505615f}, {222.407715f, 190.695068f},
        {222.525879f, 190.861328f}, {222.652832f, 191.002930f}, {222.789062f, 191.119385f}, {222.934082f, 191.208984f},
        {223.087891f, 191.270508f}, {223.250488f, 191.302490f}, {223.472656f, 191.273438f}, {223.669434f, 191.214600f},
        {223.840820f, 191.127930f}, {223.988770f, 191.015137f}, {224.113770f, 190.878174f}, {224.215820f, 190.718750f},
        {224.297363f, 190.539551f}, {224.358887f, 190.341064f}, {224.399902f, 190.126465f}, {224.438965f, 189.710693f},
        {224.502441f, 189.331543f}, {224.589355f, 188.988281f}, {224.702637f, 188.679688f}, {224.842285f, 188.404785f},
        {225.010254f, 188.162598f}, {225.208496f, 187.951904f}, {225.436035f, 187.771973f}, {225.696777f, 187.621826f},
        {225.894531f, 187.538086f}, {226.073730f, 187.444824f}, {226.235840f, 187.343994f}, {226.382812f, 187.238281f},
        {226.517090f, 187.128662f}, {226.641602f, 187.017578f}, {226.758789f, 186.907227f}, {226.870117f, 186.799316f},
        {226.979004f, 186.695801f}, {227.102539f, 186.588379f}, {227.235840f, 186.525391f}, {227.373535f, 186.493652f},
        {227.511719f, 186.480225f}, {227.645996f, 186.472412f}, {227.772461f, 186.457275f}, {227.885742f, 186.421631f},
        {227.982422f, 186.352783f}, {228.057617f, 186.238037f}, {228.087891f, 185.998291f}, {228.084961f, 185.789795f},
        {228.052246f, 185.609619f}, {227.994629f, 185.454834f}, {227.915039f, 185.323486f}, {227.818848f, 185.211914f},
        {227.710449f, 185.118408f}, {227.592773f, 185.039551f}, {227.471680f, 184.972900f}, {227.247559f, 184.853027f},
        {227.075684f, 184.719727f}, {226.948730f, 184.575439f}, {226.862305f, 184.420410f}, {226.810059f, 184.256348f},
        {226.786621f, 184.084229f}, {226.786133f, 183.904785f}, {226.802246f, 183.719971f}, {226.829590f, 183.530273f},
        {226.449707f, 183.398193f}, {226.145508f, 183.282227f}, {225.911621f, 183.172852f}, {225.742188f, 183.061768f},
        {225.631348f, 182.940430f}, {225.575195f, 182.799561f}, {225.566895f, 182.630859f}, {225.602539f, 182.425049f},
        {225.675293f, 182.173584f}, {225.755371f, 181.962158f}, {225.834961f, 181.767578f}, {225.909180f, 181.587646f},
        {225.971680f, 181.420654f}, {226.018066f, 181.264160f}, {226.041016f, 181.116455f}, {226.036621f, 180.975098f},
        {225.997559f, 180.838135f}, {225.919434f, 180.703857f}, {225.801270f, 180.598145f}, {225.690430f, 180.514160f},
        {225.586426f, 180.451904f}, {225.488770f, 180.410889f}, {225.395996f, 180.391113f}, {225.308105f, 180.392090f},
        {225.225098f, 180.413330f}, {225.145020f, 180.454346f}, {225.068359f, 180.515137f}, {224.954102f, 180.651611f},
        {224.846191f, 180.786133f}, {224.746094f, 180.919434f}, {224.657227f, 181.054443f}, {224.582520f, 181.192383f},
        {224.524414f, 181.335205f}, {224.486328f, 181.485107f}, {224.470703f, 181.643311f}, {224.479980f, 181.812012f},
        {224.504395f, 181.911865f}, {224.528320f, 182.002686f}, {224.551270f, 182.084473f}, {224.574219f, 182.158447f},
        {224.597168f, 182.224609f}, {224.620117f, 182.284424f}, {224.644043f, 182.338135f}, {224.669434f, 182.385986f},
        {224.696289f, 182.429443f}, {224.834961f, 182.631104f}, {224.925781f, 182.822998f}, {224.973145f, 183.005615f},
        {224.981445f, 183.180176f}, {224.957520f, 183.346680f}, {224.905762f, 183.506104f}, {224.831055f, 183.659180f},
        {224.740234f, 183.806396f}, {224.637207f, 183.948730f}, {224.528809f, 184.078369f}, {224.421875f, 184.196045f},
        {224.317383f, 184.303711f}, {224.214355f, 184.401855f}, {224.112305f, 184.491943f}, {224.012695f, 184.575684f},
        {223.914062f, 184.653809f}, {223.816406f, 184.727783f}, {223.719238f, 184.799072f}, {223.414062f, 185.001465f},
        {223.143066f, 185.138916f}, {222.907227f, 185.212402f}, {222.704102f, 185.220947f}, {222.534668f, 185.165283f},
        {222.396973f, 185.045166f}, {222.290527f, 184.860840f}, {222.214844f, 184.611572f}, {222.168945f, 184.298340f},
        {222.159180f, 183.996582f}, {222.141113f, 183.724609f}, {222.113281f, 183.478760f}, {222.075684f, 183.256348f},
        {222.027344f, 183.054443f}, {221.966797f, 182.869629f}, {221.894531f, 182.699219f}, {221.809570f, 182.539551f},
        {221.710449f, 182.387939f}, {221.595703f, 182.261963f}, {221.471680f, 182.147217f}, {221.344727f, 182.041504f},
        {221.221191f, 181.941650f}, {221.108887f, 181.845703f}, {221.012207f, 181.750244f}, {220.938965f, 181.653320f},
        {220.895508f, 181.552002f}, {220.887695f, 181.443604f}, {220.977539f, 181.234863f}, {221.065918f, 181.027588f},
        {221.155762f, 180.824951f}, {221.250000f, 180.629639f}, {221.352051f, 180.444580f}, {221.464355f, 180.272217f},
        {221.589844f, 180.116211f}, {221.731445f, 179.978760f}, {221.893066f, 179.863037f}, {222.110352f, 179.776123f},
        {222.319824f, 179.698975f}, {222.521973f, 179.628174f}, {222.716797f, 179.560059f}, {222.903320f, 179.490479f},
        {223.081543f, 179.416016f}, {223.251953f, 179.332275f}, {223.414062f, 179.236084f}, {223.568359f, 179.123535f},
        {223.540039f, 179.036865f}, {223.503906f, 178.968750f}, {223.460449f, 178.918457f}, {223.411133f, 178.885010f},
        {223.355957f, 178.867188f}, {223.296875f, 178.864014f}, {223.233887f, 178.874756f}, {223.167969f, 178.897949f},
        {223.100098f, 178.932861f}, {223.060059f, 178.946289f}, {223.022949f, 178.957520f}, {222.989746f, 178.966797f},
        {222.959961f, 178.974121f}, {222.931641f, 178.980225f}, {222.906738f, 178.985107f}, {222.882324f, 178.989258f},
        {222.859375f, 178.992676f}, {222.837891f, 178.995850f}, {222.390137f, 179.174805f}, {221.938965f, 179.328857f},
        {221.484375f, 179.464355f}, {221.028320f, 179.586182f}, {220.571777f, 179.699707f}, {220.114746f, 179.810791f},
        {219.659180f, 179.925049f}, {219.205566f, 180.047852f}, {218.754883f, 180.184814f}, {218.501465f, 180.255615f},
        {218.271484f, 180.317871f}, {218.063477f, 180.372803f}, {217.874023f, 180.421143f}, {217.700684f, 180.464111f},
        {217.540527f, 180.501953f}, {217.391113f, 180.536377f}, {217.249512f, 180.567871f}, {217.113770f, 180.597656f},
        {216.940918f, 180.685547f}, {216.775391f, 180.771973f}, {216.616211f, 180.856934f}, {216.462402f, 180.940918f},
        {216.313965f, 181.023682f}, {216.168945f, 181.105713f}, {216.027832f, 181.187012f}, {215.888672f, 181.267578f},
        {215.751465f, 181.347900f}, {215.692871f, 181.388184f}, {215.644531f, 181.424072f}, {215.606445f, 181.455811f},
        {215.576660f, 181.484375f}, {215.555664f, 181.509766f}, {215.540527f, 181.532959f}, {215.532715f, 181.553955f},
        {215.530273f, 181.573730f}, {215.532715f, 181.592529f}, {215.541016f, 181.614746f}, {215.550293f, 181.634033f},
        {215.559082f, 181.651123f}, {215.567383f, 181.665039f}, {215.575684f, 181.676758f}, {215.583496f, 181.686035f},
        {215.591797f, 181.693115f}, {215.599609f, 181.697998f}, {215.607422f, 181.700928f},
    };  // data size = 307

    Vec2 vertices9[] = {
        {182.175781f, 195.563477f}, {182.198242f, 195.563232f}, {182.221191f, 195.562744f}, {182.243652f, 195.561768f},
        {182.266602f, 195.561035f}, {182.289062f, 195.560547f}, {182.311523f, 195.560059f}, {182.333496f, 195.560547f},
        {182.355957f, 195.561279f}, {182.378418f, 195.563477f}, {182.831055f, 195.711670f}, {183.310059f, 195.995850f},
        {183.798340f, 196.392822f}, {184.278320f, 196.879150f}, {184.731934f, 197.432129f}, {185.141602f, 198.028809f},
        {185.490234f, 198.645996f}, {185.759277f, 199.260254f}, {185.931641f, 199.849365f}, {185.955566f, 200.315918f},
        {185.997559f, 200.745850f}, {186.054688f, 201.142822f}, {186.124512f, 201.511230f}, {186.204590f, 201.855469f},
        {186.292969f, 202.178711f}, {186.386719f, 202.486084f}, {186.482910f, 202.781250f}, {186.579590f, 203.068115f},
        {186.710938f, 203.404297f}, {186.854980f, 203.660645f}, {187.010254f, 203.843262f}, {187.173828f, 203.959229f},
        {187.343262f, 204.014404f}, {187.518555f, 204.014648f}, {187.697266f, 203.966797f}, {187.875977f, 203.876709f},
        {188.054688f, 203.750977f}, {188.296875f, 203.501221f}, {188.512207f, 203.242188f}, {188.703613f, 202.975586f},
        {188.876953f, 202.703369f}, {189.036621f, 202.427734f}, {189.186523f, 202.149414f}, {189.332031f, 201.871338f},
        {189.477051f, 201.594971f}, {189.626465f, 201.321777f}, {189.838379f, 201.432373f}, {190.003906f, 201.573242f},
        {190.128418f, 201.739990f}, {190.220215f, 201.927979f}, {190.287598f, 202.132812f}, {190.336426f, 202.350342f},
        {190.374023f, 202.575684f}, {190.409180f, 202.804688f}, {190.448242f, 203.032959f}, {190.578125f, 203.431152f},
        {190.736328f, 203.759521f}, {190.918457f, 204.024414f}, {191.121582f, 204.234131f}, {191.341309f, 204.395996f},
        {191.574219f, 204.517822f}, {191.816406f, 204.606445f}, {192.064453f, 204.669922f}, {192.314941f, 204.715576f},
        {192.573242f, 204.723633f}, {192.803711f, 204.679688f}, {193.005859f, 204.591553f}, {193.179688f, 204.467041f},
        {193.323242f, 204.313965f}, {193.437012f, 204.140381f}, {193.519043f, 203.954102f}, {193.568848f, 203.762939f},
        {193.586914f, 203.575195f}, {193.512695f, 203.116455f}, {193.454102f, 202.659424f}, {193.400879f, 202.207520f},
        {193.344727f, 201.763184f}, {193.276855f, 201.329590f}, {193.188477f, 200.909180f}, {193.070801f, 200.505371f},
        {192.915039f, 200.121094f}, {192.712402f, 199.758789f}, {192.422852f, 199.419922f}, {192.147949f, 199.098145f},
        {191.885254f, 198.791992f}, {191.634277f, 198.499268f}, {191.393066f, 198.218262f}, {191.159180f, 197.947266f},
        {190.932617f, 197.684082f}, {190.709961f, 197.427002f}, {190.490723f, 197.173828f}, {190.415527f, 197.309570f},
        {190.370117f, 197.449219f}, {190.353027f, 197.591553f}, {190.361328f, 197.735596f}, {190.395020f, 197.880859f},
        {190.449219f, 198.026123f}, {190.524414f, 198.169678f}, {190.617676f, 198.311523f}, {190.726074f, 198.450439f},
        {190.818848f, 198.551025f}, {190.900879f, 198.647705f}, {190.972168f, 198.741699f}, {191.032715f, 198.834229f},
        {191.080078f, 198.926270f}, {191.114746f, 199.019043f}, {191.136230f, 199.113037f}, {191.143066f, 199.209473f},
        {191.135254f, 199.310059f}, {191.088867f, 199.452881f}, {191.033691f, 199.572510f}, {190.971680f, 199.671143f},
        {190.902832f, 199.749756f}, {190.828125f, 199.810547f}, {190.748535f, 199.855225f}, {190.664062f, 199.885498f},
        {190.576172f, 199.902588f}, {190.484863f, 199.908936f}, {190.179199f, 199.893799f}, {189.893066f, 199.898926f},
        {189.629883f, 199.931641f}, {189.392090f, 199.998047f}, {189.182617f, 200.104980f}, {189.003418f, 200.259277f},
        {188.857910f, 200.467773f}, {188.748535f, 200.736572f}, {188.677246f, 201.072998f}, {188.652344f, 201.343994f},
        {188.603027f, 201.573242f}, {188.531738f, 201.764160f}, {188.442871f, 201.919434f}, {188.339844f, 202.042969f},
        {188.225586f, 202.137451f}, {188.104004f, 202.206299f}, {187.979004f, 202.253174f}, {187.852539f, 202.280273f},
        {187.701172f, 202.284668f}, {187.551758f, 202.281250f}, {187.406738f, 202.266846f}, {187.268066f, 202.239990f},
        {187.139160f, 202.197754f}, {187.021973f, 202.137695f}, {186.919922f, 202.057617f}, {186.834473f, 201.955322f},
        {186.768555f, 201.828125f}, {186.726074f, 201.620850f}, {186.688477f, 201.417236f}, {186.659180f, 201.218018f},
        {186.642578f, 201.024414f}, {186.640137f, 200.837646f}, {186.657227f, 200.658936f}, {186.695312f, 200.489014f},
        {186.759277f, 200.328857f}, {186.851562f, 200.180176f}, {186.956543f, 200.080566f}, {187.058105f, 199.993164f},
        {187.156250f, 199.915527f}, {187.250488f, 199.846680f}, {187.342285f, 199.784912f}, {187.430664f, 199.728760f},
        {187.516602f, 199.676514f}, {187.600586f, 199.626953f}, {187.682617f, 199.578125f}, {187.865723f, 199.453613f},
        {188.024902f, 199.325195f}, {188.155273f, 199.192871f}, {188.253906f, 199.055908f}, {188.317383f, 198.914307f},
        {188.342285f, 198.767090f}, {188.325195f, 198.614014f}, {188.261230f, 198.455078f}, {188.149414f, 198.289551f},
        {187.926758f, 198.044189f}, {187.759277f, 197.785400f}, {187.633789f, 197.517822f}, {187.541992f, 197.245117f},
        {187.472656f, 196.970947f}, {187.414551f, 196.699463f}, {187.357910f, 196.434570f}, {187.291504f, 196.180176f},
        {187.204590f, 195.939941f}, {186.853516f, 195.467529f}, {186.488770f, 195.125732f}, {186.113281f, 194.895508f},
        {185.729004f, 194.759521f}, {185.338379f, 194.699219f}, {184.943848f, 194.696045f}, {184.546387f, 194.731934f},
        {184.150391f, 194.789062f}, {183.756836f, 194.848389f}, {183.529785f, 194.880371f}, {183.325195f, 194.928955f},
        {183.139160f, 194.991943f}, {182.970703f, 195.065430f}, {182.816406f, 195.146484f}, {182.674316f, 195.232666f},
        {182.541504f, 195.320801f}, {182.416016f, 195.407227f}, {182.294922f, 195.489502f},
    };  // data size = 199

    Vec2 vertices10[] = {
        {202.070801f, 147.920166f}, {202.210449f, 147.701904f}, {202.321777f, 147.468994f}, {202.411133f, 147.224121f},
        {202.485840f, 146.971191f}, {202.551758f, 146.713623f}, {202.615234f, 146.454346f}, {202.682129f, 146.197510f},
        {202.759277f, 145.946045f}, {202.853027f, 145.703613f}, {202.710938f, 145.715332f}, {202.571289f, 145.714844f},
        {202.434570f, 145.698486f}, {202.302246f, 145.663818f}, {202.172363f, 145.607666f}, {202.046875f, 145.527100f},
        {201.925293f, 145.419189f}, {201.807617f, 145.281006f}, {201.693848f, 145.109375f}, {201.553711f, 144.838623f},
        {201.409668f, 144.585449f}, {201.271973f, 144.345947f}, {201.150391f, 144.114502f}, {201.053711f, 143.888184f},
        {200.992188f, 143.661621f}, {200.975586f, 143.431152f}, {201.013184f, 143.191895f}, {201.114746f, 142.940186f},
        {201.210449f, 142.798584f}, {201.292969f, 142.665039f}, {201.363770f, 142.538574f}, {201.422852f, 142.418945f},
        {201.472168f, 142.305664f}, {201.511230f, 142.197754f}, {201.541992f, 142.094971f}, {201.564453f, 141.996582f},
        {201.580566f, 141.901855f}, {201.603027f, 141.630127f}, {201.622070f, 141.358154f}, {201.630371f, 141.091553f},
        {201.623535f, 140.835938f}, {201.593262f, 140.596191f}, {201.533691f, 140.378418f}, {201.438477f, 140.187744f},
        {201.301270f, 140.029541f}, {201.115234f, 139.909912f}, {200.794922f, 139.865723f}, {200.536133f, 139.884277f},
        {200.332031f, 139.958252f}, {200.174805f, 140.080811f}, {200.056641f, 140.244141f}, {199.970215f, 140.441650f},
        {199.908203f, 140.665527f}, {199.862793f, 140.909180f}, {199.826660f, 141.164795f}, {199.770996f, 141.576172f},
        {199.723633f, 141.961914f}, {199.692383f, 142.323730f}, {199.683105f, 142.663574f}, {199.703613f, 142.983154f},
        {199.760742f, 143.284912f}, {199.860352f, 143.569824f}, {200.010254f, 143.840576f}, {200.216797f, 144.098145f},
        {200.418457f, 144.299316f}, {200.568359f, 144.516113f}, {200.670898f, 144.744873f}, {200.734375f, 144.981934f},
        {200.764648f, 145.224121f}, {200.766113f, 145.468018f}, {200.747070f, 145.710205f}, {200.713379f, 145.947021f},
        {200.670898f, 146.175049f}, {200.625488f, 146.344971f}, {200.569336f, 146.484619f}, {200.503418f, 146.595703f},
        {200.429199f, 146.681152f}, {200.347656f, 146.743652f}, {200.260742f, 146.784912f}, {200.169434f, 146.808105f},
        {200.074707f, 146.814941f}, {199.978027f, 146.808105f}, {199.853516f, 146.771729f}, {199.747559f, 146.723877f},
        {199.658203f, 146.665039f}, {199.583984f, 146.595947f}, {199.523438f, 146.517578f}, {199.476074f, 146.429932f},
        {199.438477f, 146.334473f}, {199.410645f, 146.231445f}, {199.390137f, 146.121094f}, {199.378418f, 145.920898f},
        {199.378418f, 145.720459f}, {199.382324f, 145.523193f}, {199.383789f, 145.331787f}, {199.376465f, 145.148682f},
        {199.352539f, 144.977295f}, {199.304688f, 144.820312f}, {199.226562f, 144.680176f}, {199.111328f, 144.560059f},
        {198.888184f, 144.474121f}, {198.691406f, 144.444824f}, {198.517090f, 144.463135f}, {198.362305f, 144.521484f},
        {198.224121f, 144.611572f}, {198.097168f, 144.725098f}, {197.979492f, 144.853760f}, {197.866211f, 144.989502f},
        {197.754395f, 145.124268f}, {197.645996f, 145.234863f}, {197.541992f, 145.336914f}, {197.442871f, 145.431396f},
        {197.347656f, 145.519287f}, {197.255859f, 145.602295f}, {197.167480f, 145.680908f}, {197.081055f, 145.756836f},
        {196.998047f, 145.830566f}, {196.916016f, 145.903320f}, {196.501953f, 146.275635f}, {196.158203f, 146.557617f},
        {195.873047f, 146.747070f}, {195.637207f, 146.840332f}, {195.439453f, 146.834717f}, {195.271484f, 146.726807f},
        {195.121582f, 146.514160f}, {194.979980f, 146.193359f}, {194.836914f, 145.761230f}, {194.764160f, 145.497803f},
        {194.700195f, 145.263428f}, {194.644531f, 145.054688f}, {194.596191f, 144.868164f}, {194.555176f, 144.701416f},
        {194.520020f, 144.550293f}, {194.490234f, 144.412109f}, {194.464844f, 144.283203f}, {194.443359f, 144.160645f},
        {194.401855f, 143.942871f}, {194.347656f, 143.768066f}, {194.283203f, 143.634766f}, {194.208496f, 143.540283f},
        {194.125488f, 143.482422f}, {194.036133f, 143.459473f}, {193.940918f, 143.468506f}, {193.841797f, 143.508057f},
        {193.738770f, 143.576172f}, {193.562988f, 143.733887f}, {193.389160f, 143.857178f}, {193.217773f, 143.949463f},
        {193.047852f, 144.016113f}, {192.879395f, 144.060791f}, {192.711914f, 144.088623f}, {192.544922f, 144.104248f},
        {192.378418f, 144.111572f}, {192.211914f, 144.115479f}, {191.621094f, 144.140869f}, {191.039551f, 144.167480f},
        {190.465332f, 144.194336f}, {189.898438f, 144.221680f}, {189.337891f, 144.249512f}, {188.781738f, 144.277344f},
        {188.230469f, 144.304932f}, {187.681641f, 144.332275f}, {187.134766f, 144.359131f}, {186.907715f, 144.370850f},
        {186.710449f, 144.381836f}, {186.538086f, 144.391113f}, {186.389160f, 144.398438f}, {186.259766f, 144.403320f},
        {186.147461f, 144.404541f}, {186.049316f, 144.401367f}, {185.961426f, 144.393311f}, {185.880859f, 144.379639f},
        {185.673340f, 144.315430f}, {185.467285f, 144.247803f}, {185.265625f, 144.173584f}, {185.071777f, 144.090088f},
        {184.888672f, 143.994385f}, {184.718262f, 143.882324f}, {184.563477f, 143.752197f}, {184.428223f, 143.599609f},
        {184.314453f, 143.422119f}, {184.243164f, 143.160889f}, {184.227539f, 142.933594f}, {184.258301f, 142.735352f},
        {184.326660f, 142.561523f}, {184.424316f, 142.407471f}, {184.541504f, 142.268555f}, {184.669434f, 142.139404f},
        {184.800293f, 142.016113f}, {184.923340f, 141.892822f}, {185.156738f, 141.583496f}, {185.336914f, 141.333252f},
        {185.464355f, 141.129639f}, {185.539551f, 140.959717f}, {185.561035f, 140.811279f}, {185.530762f, 140.671875f},
        {185.447754f, 140.528564f}, {185.312012f, 140.369385f}, {185.124512f, 140.180908f}, {184.843750f, 139.931396f},
        {184.572754f, 139.725830f}, {184.310547f, 139.560547f}, {184.054199f, 139.431885f}, {183.803223f, 139.336426f},
        {183.555176f, 139.270508f}, {183.309082f, 139.229980f}, {183.063477f, 139.211670f}, {182.815918f, 139.211670f},
        {182.606934f, 139.233643f}, {182.417969f, 139.266846f}, {182.249023f, 139.312256f}, {182.097168f, 139.371094f},
        {181.961914f, 139.444092f}, {181.842285f, 139.531738f}, {181.736816f, 139.635498f}, {181.644043f, 139.756104f},
        {181.562988f, 139.894043f}, {181.489258f, 140.108154f}, {181.453125f, 140.296875f}, {181.449219f, 140.464355f},
        {181.471680f, 140.613525f}, {181.515625f, 140.748047f}, {181.575684f, 140.872070f}, {181.646484f, 140.989258f},
        {181.723145f, 141.102783f}, {181.799316f, 141.216797f}, {181.927734f, 141.405518f}, {182.081543f, 141.579834f},
        {182.249023f, 141.743164f}, {182.415039f, 141.899902f}, {182.568848f, 142.053955f}, {182.696289f, 142.209473f},
        {182.786133f, 142.370605f}, {182.823730f, 142.541016f}, {182.797852f, 142.725342f}, {182.605957f, 142.972900f},
        {182.396484f, 143.156006f}, {182.172852f, 143.281006f}, {181.939453f, 143.353760f}, {181.698242f, 143.379883f},
        {181.452637f, 143.365723f}, {181.206543f, 143.316650f}, {180.962402f, 143.239258f}, {180.723633f, 143.139160f},
        {180.593262f, 143.065918f}, {180.477539f, 142.992676f}, {180.374512f, 142.920166f}, {180.283691f, 142.848389f},
        {180.201172f, 142.777832f}, {180.126953f, 142.708252f}, {180.058594f, 142.640625f}, {179.994629f, 142.574951f},
        {179.933105f, 142.511230f}, {179.844727f, 142.430420f}, {179.753906f, 142.361328f}, {179.661621f, 142.304688f},
        {179.571777f, 142.262939f}, {179.484863f, 142.236572f}, {179.404297f, 142.227295f}, {179.330566f, 142.236572f},
        {179.267090f, 142.265625f}, {179.214844f, 142.316162f}, {179.073730f, 142.621582f}, {178.911133f, 142.854736f},
        {178.730469f, 143.026611f}, {178.535156f, 143.148438f}, {178.329102f, 143.231689f}, {178.115723f, 143.288086f},
        {177.898438f, 143.328125f}, {177.681641f, 143.363525f}, {177.467285f, 143.405762f}, {177.237793f, 143.489258f},
        {177.024414f, 143.577393f}, {176.825684f, 143.670410f}, {176.640137f, 143.769287f}, {176.467773f, 143.875244f},
        {176.304688f, 143.988770f}, {176.151367f, 144.111084f}, {176.005371f, 144.242188f}, {175.866211f, 144.383789f},
        {175.588867f, 144.689453f}, {175.313477f, 144.949707f}, {175.037109f, 145.161865f}, {174.759766f, 145.322266f},
        {174.480469f, 145.428467f}, {174.197266f, 145.477295f}, {173.910645f, 145.466064f}, {173.617676f, 145.391602f},
        {173.318359f, 145.250977f}, {173.120117f, 145.111328f}, {172.938477f, 144.999756f}, {172.773438f, 144.916992f},
        {172.622070f, 144.864014f}, {172.483398f, 144.841309f}, {172.355957f, 144.849609f}, {172.239258f, 144.889404f},
        {172.130371f, 144.961182f}, {172.029297f, 145.066162f}, {171.694824f, 145.266357f}, {171.368652f, 145.426758f},
        {171.049316f, 145.544922f}, {170.736328f, 145.617432f}, {170.429688f, 145.641602f}, {170.128906f, 145.614014f},
        {169.833008f, 145.531982f}, {169.541504f, 145.391846f}, {169.254395f, 145.191406f}, {169.077637f, 145.027832f},
        {168.911133f, 144.897217f}, {168.753418f, 144.796387f}, {168.603516f, 144.722656f}, {168.460449f, 144.672363f},
        {168.323242f, 144.643555f}, {168.191406f, 144.632080f}, {168.062500f, 144.635254f}, {167.936523f, 144.650146f},
        {167.869629f, 144.660889f}, {167.810059f, 144.671631f}, {167.756836f, 144.682129f}, {167.708496f, 144.693115f},
        {167.665039f, 144.704346f}, {167.625488f, 144.715820f}, {167.588379f, 144.727539f}, {167.554688f, 144.740234f},
        {167.522461f, 144.753418f}, {167.483398f, 144.774170f}, {167.446777f, 144.794678f}, {167.411621f, 144.815186f},
        {167.378418f, 144.835693f}, {167.346191f, 144.856201f}, {167.315430f, 144.876709f}, {167.285645f, 144.897705f},
        {167.256836f, 144.918945f}, {167.228516f, 144.940430f}, {166.982422f, 145.060547f}, {166.724609f, 145.161621f},
        {166.465332f, 145.256836f}, {166.212891f, 145.359619f}, {165.977539f, 145.483398f}, {165.766602f, 145.641357f},
        {165.591797f, 145.846191f}, {165.460938f, 146.112061f}, {165.383301f, 146.451660f}, {165.527832f, 146.720459f},
        {165.674805f, 146.962891f}, {165.824707f, 147.181641f}, {165.978027f, 147.377686f}, {166.134277f, 147.553711f},
        {166.294434f, 147.711182f}, {166.458008f, 147.852295f}, {166.625977f, 147.979248f}, {166.798828f, 148.093262f},
        {167.166504f, 148.171387f}, {167.525391f, 148.232422f}, {167.875488f, 148.277100f}, {168.218262f, 148.306396f},
        {168.554688f, 148.321289f}, {168.885742f, 148.322510f}, {169.212402f, 148.311279f}, {169.535645f, 148.287842f},
        {169.856934f, 148.253662f}, {170.063477f, 148.202881f}, {170.251953f, 148.148926f}, {170.422852f, 148.092041f},
        {170.579102f, 148.032227f}, {170.722168f, 147.968994f}, {170.853027f, 147.902344f}, {170.973145f, 147.831787f},
        {171.085938f, 147.757324f}, {171.191406f, 147.678955f}, {171.437012f, 147.484375f}, {171.677246f, 147.323486f},
        {171.913086f, 147.196045f}, {172.145996f, 147.102539f}, {172.378906f, 147.042725f}, {172.613281f, 147.016357f},
        {172.849609f, 147.023926f}, {173.090820f, 147.064941f}, {173.338379f, 147.139404f}, {173.663086f, 147.267822f},
        {173.969238f, 147.340332f}, {174.255371f, 147.361084f}, {174.523438f, 147.333740f}, {174.773926f, 147.262695f},
        {175.006836f, 147.150635f}, {175.223633f, 147.002197f}, {175.424805f, 146.821289f}, {175.611328f, 146.610840f},
        {175.844727f, 146.282715f}, {176.075195f, 145.993164f}, {176.303223f, 145.743652f}, {176.533691f, 145.534668f},
        {176.767578f, 145.367920f}, {177.009277f, 145.244141f}, {177.260254f, 145.164551f}, {177.523926f, 145.130859f},
        {177.802246f, 145.143311f}, {178.006348f, 145.184814f}, {178.191895f, 145.204102f}, {178.359375f, 145.202881f},
        {178.512695f, 145.182861f}, {178.652344f, 145.144775f}, {178.780273f, 145.090820f}, {178.898438f, 145.021973f},
        {179.009277f, 144.939941f}, {179.114258f, 144.845703f}, {179.352051f, 144.596680f}, {179.559082f, 144.405762f},
        {179.741699f, 144.272705f}, {179.904785f, 144.197021f}, {180.052734f, 144.178223f}, {180.191406f, 144.216553f},
        {180.327148f, 144.310791f}, {180.464355f, 144.461426f}, {180.608398f, 144.668213f}, {180.680664f, 144.795654f},
        {180.743652f, 144.910156f}, {180.797852f, 145.013428f}, {180.844238f, 145.106201f}, {180.884277f, 145.189941f},
        {180.920410f, 145.265625f}, {180.953125f, 145.334961f}, {180.984375f, 145.398682f}, {181.014648f, 145.458008f},
        {181.158691f, 145.684326f}, {181.307617f, 145.874023f}, {181.459961f, 146.024902f}, {181.617188f, 146.135254f},
        {181.779297f, 146.203369f}, {181.945312f, 146.227783f}, {182.115234f, 146.206055f}, {182.289551f, 146.137207f},
        {182.468262f, 146.019287f}, {182.688965f, 145.812500f}, {182.900879f, 145.650879f}, {183.104004f, 145.531982f},
        {183.300781f, 145.453125f}, {183.492188f, 145.411865f}, {183.679199f, 145.404541f}, {183.863281f, 145.429443f},
        {184.045898f, 145.483398f}, {184.228027f, 145.563965f}, {184.800781f, 145.895752f}, {185.371094f, 146.180420f},
        {185.939941f, 146.421875f}, {186.507812f, 146.623779f}, {187.075684f, 146.789551f}, {187.642578f, 146.923096f},
        {188.210938f, 147.027832f}, {188.780762f, 147.107666f}, {189.352539f, 147.165771f}, {189.866211f, 147.211426f},
        {190.345215f, 147.279541f}, {190.793945f, 147.365723f}, {191.216309f, 147.464600f}, {191.616211f, 147.572754f},
        {191.998535f, 147.685059f}, {192.367188f, 147.796875f}, {192.725586f, 147.904297f}, {193.078613f, 148.002197f},
        {193.288086f, 148.060791f}, {193.467285f, 148.133301f}, {193.619629f, 148.217773f}, {193.748535f, 148.312012f},
        {193.858398f, 148.414307f}, {193.951660f, 148.522461f}, {194.032715f, 148.634766f}, {194.104492f, 148.748535f},
        {194.170898f, 148.862793f}, {194.299316f, 149.071777f}, {194.429199f, 149.264404f}, {194.562988f, 149.438477f},
        {194.701660f, 149.593750f}, {194.845703f, 149.728516f}, {194.997559f, 149.841797f}, {195.157715f, 149.932373f},
        {195.327637f, 149.999023f}, {195.508301f, 150.040771f}, {195.833008f, 149.949219f}, {196.125488f, 149.828613f},
        {196.388184f, 149.678223f}, {196.623535f, 149.497070f}, {196.833008f, 149.284180f}, {197.017578f, 149.038574f},
        {197.179199f, 148.759033f}, {197.319336f, 148.445312f}, {197.439941f, 148.095703f}, {197.512695f, 148.398438f},
        {197.612305f, 148.661865f}, {197.737305f, 148.888672f}, {197.886719f, 149.080322f}, {198.057617f, 149.239014f},
        {198.250000f, 149.366943f}, {198.461426f, 149.465820f}, {198.691895f, 149.537842f}, {198.937988f, 149.585205f},
        {199.163574f, 149.597900f}, {199.375488f, 149.606934f}, {199.573242f, 149.618408f}, {199.758301f, 149.637451f},
        {199.929688f, 149.668945f}, {200.087891f, 149.718018f}, {200.232910f, 149.790527f}, {200.364746f, 149.890625f},
        {200.483887f, 150.024414f}, {200.644043f, 150.199707f}, {200.801758f, 150.346680f}, {200.956543f, 150.464111f},
        {201.108887f, 150.550049f}, {201.258301f, 150.603516f}, {201.405273f, 150.622803f}, {201.549316f, 150.606445f},
        {201.690918f, 150.552979f}, {201.829590f, 150.460938f}, {202.001953f, 150.246094f}, {202.116699f, 150.045654f},
        {202.180664f, 149.856934f}, {202.200195f, 149.679932f}, {202.180664f, 149.512695f}, {202.128906f, 149.354004f},
        {202.051270f, 149.202637f}, {201.953613f, 149.057373f}, {201.843750f, 148.916992f}, {201.761719f, 148.811523f},
        {201.703125f, 148.710693f}, {201.664551f, 148.614258f}, {201.642090f, 148.521729f}, {201.633301f, 148.432617f},
        {201.634766f, 148.346680f}, {201.642578f, 148.263428f}, {201.654297f, 148.182617f}, {201.665527f, 148.103760f},
        {201.654297f, 148.041992f}, {201.635742f, 147.987549f}, {201.613281f, 147.938477f}, {201.589844f, 147.893311f},
        {201.566406f, 147.850586f}, {201.545898f, 147.808838f}, {201.530762f, 147.765869f}, {201.522461f, 147.720947f},
        {201.524902f, 147.672119f}, {201.528320f, 147.698486f}, {201.534668f, 147.726318f}, {201.543457f, 147.755371f},
        {201.554199f, 147.785400f}, {201.567383f, 147.816406f}, {201.582520f, 147.848389f}, {201.599121f, 147.880859f},
        {201.616699f, 147.913574f}, {201.635742f, 147.946533f}, {201.687012f, 147.982422f}, {201.735840f, 148.008789f},
        {201.782227f, 148.026367f}, {201.827637f, 148.035156f}, {201.871094f, 148.035400f}, {201.913086f, 148.027832f},
        {201.953613f, 148.011963f}, {201.994141f, 147.988770f}, {202.032227f, 147.958008f},
    };  // data size = 559

    Vec2 vertices11[] = {
        {348.976074f, 143.716797f}, {348.976074f, 143.172363f}, {348.972656f, 143.121338f}, {348.966309f, 143.071289f},
        {348.956543f, 143.022461f}, {348.944824f, 142.975098f}, {348.930664f, 142.928467f}, {348.915039f, 142.882812f},
        {348.897461f, 142.837402f}, {348.878418f, 142.792969f}, {348.858398f, 142.749023f}, {348.802734f, 142.634521f},
        {348.750977f, 142.521240f}, {348.702148f, 142.408447f}, {348.656250f, 142.296143f}, {348.612793f, 142.184814f},
        {348.570801f, 142.074219f}, {348.529297f, 141.964355f}, {348.488770f, 141.855225f}, {348.447266f, 141.747070f},
        {348.378418f, 141.589355f}, {348.313477f, 141.436035f}, {348.250000f, 141.288574f}, {348.185547f, 141.147705f},
        {348.118652f, 141.015137f}, {348.045898f, 140.891602f}, {347.966797f, 140.778564f}, {347.878418f, 140.677002f},
        {347.778809f, 140.587891f}, {347.333984f, 140.359863f}, {346.917969f, 140.106445f}, {346.532715f, 139.825684f},
        {346.176758f, 139.517578f}, {345.849609f, 139.179932f}, {345.551758f, 138.812256f}, {345.282227f, 138.413330f},
        {345.042480f, 137.982178f}, {344.831055f, 137.516846f}, {344.768066f, 137.344727f}, {344.713867f, 137.199951f},
        {344.667969f, 137.080078f}, {344.628906f, 136.981934f}, {344.595703f, 136.902344f}, {344.567383f, 136.838379f},
        {344.541992f, 136.787109f}, {344.519043f, 136.745117f}, {344.497559f, 136.709717f}, {344.261719f, 136.440430f},
        {344.021973f, 136.187744f}, {343.776367f, 135.955811f}, {343.523438f, 135.747070f}, {343.261230f, 135.564941f},
        {342.988281f, 135.412598f}, {342.701660f, 135.292969f}, {342.400391f, 135.209717f}, {342.083008f, 135.165527f},
        {341.810059f, 135.158447f}, {341.564453f, 135.118408f}, {341.343750f, 135.050049f}, {341.144043f, 134.958008f},
        {340.961914f, 134.846436f}, {340.795410f, 134.719727f}, {340.641113f, 134.583008f}, {340.496094f, 134.439697f},
        {340.356445f, 134.295166f}, {340.153320f, 134.094727f}, {339.952148f, 133.913086f}, {339.753906f, 133.748047f},
        {339.556641f, 133.597656f}, {339.361328f, 133.459961f}, {339.166504f, 133.333252f}, {338.972656f, 133.216064f},
        {338.778320f, 133.105713f}, {338.584961f, 133.001221f}, {338.314941f, 132.926025f}, {338.064941f, 132.836670f},
        {337.834961f, 132.733154f}, {337.622070f, 132.615967f}, {337.424316f, 132.484131f}, {337.241211f, 132.338135f},
        {337.069824f, 132.177979f}, {336.909180f, 132.003418f}, {336.756836f, 131.814941f}, {336.486328f, 131.442139f},
        {336.212402f, 131.110352f}, {335.932129f, 130.819824f}, {335.645020f, 130.572266f}, {335.349121f, 130.367920f},
        {335.041992f, 130.208252f}, {334.722656f, 130.094238f}, {334.389648f, 130.026855f}, {334.041504f, 130.007080f},
        {333.714844f, 130.036133f}, {333.421875f, 130.037354f}, {333.160645f, 130.008789f}, {332.930176f, 129.948486f},
        {332.727539f, 129.854248f}, {332.551270f, 129.723877f}, {332.399414f, 129.555420f}, {332.270020f, 129.346680f},
        {332.161621f, 129.095947f}, {332.030762f, 128.704102f}, {331.873047f, 128.393311f}, {331.691406f, 128.156738f},
        {331.492188f, 127.988281f}, {331.279785f, 127.881348f}, {331.059570f, 127.829590f}, {330.835449f, 127.826904f},
        {330.614258f, 127.866211f}, {330.398926f, 127.941650f}, {329.979980f, 128.161377f}, {329.585938f, 128.313477f},
        {329.213379f, 128.403076f}, {328.857910f, 128.435303f}, {328.515137f, 128.415039f}, {328.181152f, 128.347412f},
        {327.851074f, 128.237549f}, {327.520996f, 128.090332f}, {327.187012f, 127.910889f}, {326.778809f, 127.666748f},
        {326.383301f, 127.444580f}, {325.999023f, 127.240234f}, {325.626953f, 127.049561f}, {325.265137f, 126.867676f},
        {324.913086f, 126.689941f}, {324.571289f, 126.512451f}, {324.237793f, 126.330078f}, {323.912598f, 126.138672f},
        {323.686035f, 126.002197f}, {323.474121f, 125.902588f}, {323.276367f, 125.837402f}, {323.091309f, 125.804443f},
        {322.918457f, 125.801025f}, {322.757812f, 125.824463f}, {322.607422f, 125.872070f}, {322.467285f, 125.941895f},
        {322.336426f, 126.030762f}, {322.083984f, 126.244873f}, {321.844238f, 126.398438f}, {321.614746f, 126.495850f},
        {321.394531f, 126.541260f}, {321.183105f, 126.539307f}, {320.978027f, 126.494385f}, {320.778809f, 126.410156f},
        {320.583008f, 126.291748f}, {320.390625f, 126.142822f}, {320.181152f, 125.948486f}, {319.979980f, 125.777588f},
        {319.784668f, 125.633057f}, {319.594238f, 125.515625f}, {319.406250f, 125.428467f}, {319.219238f, 125.372559f},
        {319.031250f, 125.349854f}, {318.840332f, 125.363037f}, {318.645508f, 125.413574f}, {318.476074f, 125.488281f},
        {318.328125f, 125.530518f}, {318.199219f, 125.542969f}, {318.087402f, 125.528809f}, {317.990234f, 125.490967f},
        {317.904785f, 125.432129f}, {317.829590f, 125.355469f}, {317.761719f, 125.263916f}, {317.699219f, 125.160400f},
        {317.559570f, 124.920898f}, {317.410645f, 124.726074f}, {317.254395f, 124.574707f}, {317.092773f, 124.465088f},
        {316.926270f, 124.395752f}, {316.756836f, 124.365723f}, {316.585938f, 124.373535f}, {316.415039f, 124.417236f},
        {316.245117f, 124.496338f}, {315.971680f, 124.680176f}, {315.720215f, 124.802246f}, {315.486816f, 124.868652f},
        {315.269043f, 124.885010f}, {315.064941f, 124.857910f}, {314.871582f, 124.792236f}, {314.686523f, 124.694336f},
        {314.506836f, 124.570068f}, {314.331055f, 124.425293f}, {314.252441f, 124.362549f}, {314.183594f, 124.309082f},
        {314.123047f, 124.264648f}, {314.068848f, 124.228027f}, {314.020508f, 124.197754f}, {313.978027f, 124.173340f},
        {313.938965f, 124.153564f}, {313.902832f, 124.137451f}, {313.868652f, 124.124023f}, {313.539551f, 124.010742f},
        {313.218262f, 123.935303f}, {312.903809f, 123.897705f}, {312.596191f, 123.898193f}, {312.293945f, 123.937012f},
        {311.998535f, 124.013916f}, {311.708496f, 124.129395f}, {311.423828f, 124.283203f}, {311.144043f, 124.476074f},
        {310.916992f, 124.665283f}, {310.704102f, 124.814209f}, {310.503906f, 124.923584f}, {310.314453f, 124.993896f},
        {310.135254f, 125.026367f}, {309.964844f, 125.020996f}, {309.801758f, 124.978516f}, {309.644531f, 124.900146f},
        {309.492188f, 124.785645f}, {309.383301f, 124.668945f}, {309.280762f, 124.559570f}, {309.183105f, 124.459229f},
        {309.088867f, 124.368896f}, {308.998535f, 124.290771f}, {308.910645f, 124.226562f}, {308.823730f, 124.177490f},
        {308.738281f, 124.145264f}, {308.653320f, 124.132080f}, {307.876953f, 124.215820f}, {307.125000f, 124.168701f},
        {306.392578f, 124.020508f}, {305.673828f, 123.799805f}, {304.963867f, 123.535889f}, {304.258301f, 123.258545f},
        {303.551270f, 122.996826f}, {302.838379f, 122.779785f}, {302.113770f, 122.636719f}, {301.545898f, 122.613037f},
        {301.023438f, 122.546387f}, {300.542969f, 122.441895f}, {300.099121f, 122.303711f}, {299.687500f, 122.136230f},
        {299.303711f, 121.944336f}, {298.943359f, 121.732178f}, {298.600586f, 121.504639f}, {298.271484f, 121.265869f},
        {297.785645f, 120.903076f}, {297.372559f, 120.633057f}, {297.023926f, 120.457764f}, {296.729492f, 120.377930f},
        {296.479004f, 120.395508f}, {296.263672f, 120.511230f}, {296.073730f, 120.727051f}, {295.899902f, 121.044189f},
        {295.732422f, 121.463867f}, {295.661621f, 121.683350f}, {295.600098f, 121.872803f}, {295.545898f, 122.034912f},
        {295.495117f, 122.171631f}, {295.447754f, 122.285889f}, {295.399902f, 122.379395f}, {295.350098f, 122.454834f},
        {295.295898f, 122.514160f}, {295.235840f, 122.560547f}, {294.797852f, 122.694824f}, {294.357422f, 122.743408f},
        {293.920898f, 122.710205f}, {293.496094f, 122.600830f}, {293.090820f, 122.419678f}, {292.711914f, 122.170654f},
        {292.367676f, 121.859375f}, {292.064941f, 121.489990f}, {291.811523f, 121.066895f}, {291.737793f, 120.876221f},
        {291.675293f, 120.710205f}, {291.623047f, 120.566650f}, {291.579590f, 120.442871f}, {291.543457f, 120.335693f},
        {291.513184f, 120.242676f}, {291.487305f, 120.161133f}, {291.464355f, 120.088379f}, {291.443359f, 120.021240f},
        {291.291016f, 119.591797f}, {291.139648f, 119.252686f}, {290.985840f, 119.003174f}, {290.827148f, 118.842285f},
        {290.658691f, 118.769043f}, {290.478516f, 118.782471f}, {290.282715f, 118.882080f}, {290.067871f, 119.066895f},
        {289.830566f, 119.336182f}, {289.742676f, 119.466064f}, {289.669922f, 119.577393f}, {289.610840f, 119.672852f},
        {289.562500f, 119.753418f}, {289.525391f, 119.821777f}, {289.496094f, 119.879639f}, {289.473633f, 119.929688f},
        {289.456543f, 119.973633f}, {289.443359f, 120.013184f}, {289.339355f, 120.506592f}, {289.230957f, 120.903564f},
        {289.111816f, 121.207520f}, {288.977051f, 121.421387f}, {288.820801f, 121.547607f}, {288.637207f, 121.589355f},
        {288.421387f, 121.549316f}, {288.166504f, 121.430664f}, {287.868164f, 121.235840f}, {287.711426f, 121.131836f},
        {287.572754f, 121.045898f}, {287.449707f, 120.976807f}, {287.341309f, 120.922363f}, {287.244629f, 120.880615f},
        {287.158203f, 120.849609f}, {287.079590f, 120.827881f}, {287.006348f, 120.813477f}, {286.937012f, 120.804443f},
        {286.401367f, 120.626709f}, {285.864746f, 120.482910f}, {285.326660f, 120.364990f}, {284.788574f, 120.264160f},
        {284.251953f, 120.172607f}, {283.717285f, 120.082275f}, {283.185059f, 119.984619f}, {282.656250f, 119.871826f},
        {282.132812f, 119.735352f}, {281.825195f, 119.572021f}, {281.549805f, 119.454102f}, {281.302246f, 119.378906f},
        {281.079590f, 119.343262f}, {280.879395f, 119.344482f}, {280.697266f, 119.379150f}, {280.530273f, 119.444824f},
        {280.375977f, 119.538330f}, {280.229980f, 119.657227f}, {280.040039f, 119.856689f}, {279.856445f, 120.045898f},
        {279.677734f, 120.226074f}, {279.503906f, 120.398926f}, {279.333984f, 120.565674f}, {279.168945f, 120.728027f},
        {279.006836f, 120.886963f}, {278.848633f, 121.044922f}, {278.692871f, 121.202637f}, {278.280273f, 121.589355f},
        {277.854004f, 121.900635f}, {277.416992f, 122.136963f}, {276.974609f, 122.298096f}, {276.529785f, 122.384521f},
        {276.086914f, 122.396240f}, {275.650391f, 122.333496f}, {275.223633f, 122.196045f}, {274.811523f, 121.984131f},
        {274.546387f, 121.783691f}, {274.305176f, 121.622559f}, {274.085938f, 121.499756f}, {273.884766f, 121.413330f},
        {273.697754f, 121.361816f}, {273.521973f, 121.343262f}, {273.354492f, 121.356934f}, {273.191406f, 121.400146f},
        {273.029297f, 121.472168f}, {272.856445f, 121.582520f}, {272.689453f, 121.681641f}, {272.528809f, 121.770020f},
        {272.372559f, 121.847656f}, {272.220703f, 121.914551f}, {272.071289f, 121.970703f}, {271.923828f, 122.016602f},
        {271.777344f, 122.052002f}, {271.630859f, 122.077148f}, {271.400391f, 122.089355f}, {271.184570f, 122.087402f},
        {270.985352f, 122.067627f}, {270.804688f, 122.024902f}, {270.643555f, 121.954834f}, {270.503906f, 121.853027f},
        {270.387207f, 121.714600f}, {270.295410f, 121.535645f}, {270.229980f, 121.311035f}, {270.192871f, 121.033447f},
        {270.137207f, 120.796631f}, {270.064941f, 120.597900f}, {269.976562f, 120.434326f}, {269.873535f, 120.302490f},
        {269.757812f, 120.198730f}, {269.629883f, 120.120361f}, {269.490723f, 120.064453f}, {269.342285f, 120.027588f},
        {269.052734f, 120.003418f}, {268.773438f, 119.989502f}, {268.502441f, 119.986816f}, {268.239746f, 119.996582f},
        {267.983398f, 120.020264f}, {267.732910f, 120.059326f}, {267.487793f, 120.114746f}, {267.245605f, 120.188232f},
        {267.006348f, 120.281006f}, {266.531250f, 120.503662f}, {266.067383f, 120.675781f}, {265.614258f, 120.798828f},
        {265.169434f, 120.874023f}, {264.732422f, 120.903076f}, {264.301758f, 120.887207f}, {263.877441f, 120.828125f},
        {263.456543f, 120.727051f}, {263.039062f, 120.585938f}, {262.697266f, 120.427246f}, {262.376953f, 120.280518f},
        {262.074707f, 120.147949f}, {261.789551f, 120.030273f}, {261.517090f, 119.929443f}, {261.254883f, 119.846436f},
        {260.999023f, 119.783203f}, {260.747070f, 119.740967f}, {260.496582f, 119.721191f}, {260.253418f, 119.741943f},
        {260.040527f, 119.779053f}, {259.854492f, 119.833740f}, {259.695312f, 119.908203f}, {259.561035f, 120.003662f},
        {259.450684f, 120.122070f}, {259.363281f, 120.265381f}, {259.297363f, 120.434814f}, {259.252441f, 120.632080f},
        {259.173340f, 121.442139f}, {259.057617f, 122.116455f}, {258.899414f, 122.660645f}, {258.695312f, 123.079834f},
        {258.439941f, 123.380127f}, {258.127441f, 123.566650f}, {257.754395f, 123.644775f}, {257.314941f, 123.619873f},
        {256.804199f, 123.497559f}, {256.612305f, 123.427734f}, {256.452637f, 123.371826f}, {256.320801f, 123.328369f},
        {256.212891f, 123.296143f}, {256.125977f, 123.273682f}, {256.056641f, 123.259033f}, {256.001465f, 123.251465f},
        {255.956543f, 123.249023f}, {255.918945f, 123.250488f}, {255.809082f, 123.355469f}, {255.702637f, 123.461182f},
        {255.597656f, 123.566895f}, {255.494141f, 123.671631f}, {255.390137f, 123.775146f}, {255.285645f, 123.875977f},
        {255.180176f, 123.973877f}, {255.071777f, 124.068115f}, {254.958984f, 124.157227f}, {254.783691f, 124.291016f},
        {254.640625f, 124.428223f}, {254.530273f, 124.568848f}, {254.453613f, 124.712891f}, {254.410645f, 124.859863f},
        {254.401855f, 125.009766f}, {254.428223f, 125.162354f}, {254.489746f, 125.317383f}, {254.586426f, 125.474854f},
        {254.751953f, 125.589355f}, {254.912598f, 125.683594f}, {255.068848f, 125.757568f}, {255.220215f, 125.812012f},
        {255.367188f, 125.847412f}, {255.509277f, 125.863525f}, {255.646973f, 125.860596f}, {255.778809f, 125.839111f},
        {255.906250f, 125.799561f}, {256.246582f, 125.615723f}, {256.577148f, 125.447021f}, {256.900391f, 125.299561f},
        {257.218750f, 125.179199f}, {257.536133f, 125.092285f}, {257.854980f, 125.044922f}, {258.177734f, 125.042969f},
        {258.506836f, 125.092529f}, {258.845703f, 125.199951f}, {259.119629f, 125.318848f}, {259.354004f, 125.361572f},
        {259.553223f, 125.338623f}, {259.719727f, 125.259277f}, {259.856934f, 125.133057f}, {259.968262f, 124.969727f},
        {260.057129f, 124.778564f}, {260.126953f, 124.569824f}, {260.180176f, 124.352295f}, {260.210449f, 124.171387f},
        {260.239746f, 123.999756f}, {260.269531f, 123.838379f}, {260.303223f, 123.689209f}, {260.341797f, 123.553467f},
        {260.388672f, 123.433594f}, {260.445312f, 123.330078f}, {260.514648f, 123.245850f}, {260.599121f, 123.181152f},
        {260.748535f, 123.152344f}, {260.871094f, 123.161377f}, {260.971191f, 123.203125f}, {261.052246f, 123.271484f},
        {261.118164f, 123.360107f}, {261.172363f, 123.463623f}, {261.219727f, 123.575684f}, {261.263184f, 123.690674f},
        {261.307129f, 123.802246f}, {261.558105f, 124.199707f}, {261.861328f, 124.546387f}, {262.205078f, 124.839600f},
        {262.580078f, 125.075195f}, {262.976074f, 125.250000f}, {263.383789f, 125.360596f}, {263.792480f, 125.403809f},
        {264.192383f, 125.375488f}, {264.573242f, 125.273193f}, {264.844727f, 125.127930f}, {265.103027f, 125.020264f},
        {265.349121f, 124.941162f}, {265.581543f, 124.881348f}, {265.801758f, 124.831543f}, {266.010254f, 124.781982f},
        {266.206055f, 124.724121f}, {266.390137f, 124.648438f}, {266.562500f, 124.545410f}, {266.653809f, 124.429199f},
        {266.729492f, 124.316895f}, {266.791504f, 124.208984f}, {266.842285f, 124.104492f}, {266.883789f, 124.003174f},
        {266.916992f, 123.904541f}, {266.945801f, 123.808594f}, {266.970215f, 123.715088f}, {266.993164f, 123.623047f},
        {267.066895f, 123.392822f}, {267.149414f, 123.204834f}, {267.240723f, 123.057861f}, {267.341309f, 122.950684f},
        {267.450684f, 122.881836f}, {267.569824f, 122.850586f}, {267.697754f, 122.854980f}, {267.835449f, 122.894287f},
        {267.982422f, 122.967041f}, {268.298828f, 123.189209f}, {268.611816f, 123.386719f}, {268.921875f, 123.561279f},
        {269.230957f, 123.714111f}, {269.538574f, 123.847412f}, {269.845703f, 123.962402f}, {270.153809f, 124.060547f},
        {270.462891f, 124.143799f}, {270.774414f, 124.213379f}, {271.053711f, 124.256348f}, {271.312500f, 124.286377f},
        {271.554199f, 124.302490f}, {271.779785f, 124.303955f}, {271.991699f, 124.290283f}, {272.193359f, 124.260010f},
        {272.385254f, 124.213379f}, {272.571289f, 124.148926f}, {272.752930f, 124.066406f}, {272.990234f, 123.935547f},
        {273.222168f, 123.833496f}, {273.449219f, 123.757568f}, {273.671387f, 123.705078f}, {273.888672f, 123.672363f},
        {274.102051f, 123.656982f}, {274.311523f, 123.656250f}, {274.517090f, 123.667236f}, {274.719727f, 123.686279f},
        {275.269531f, 123.737061f}, {275.801270f, 123.741699f}, {276.316895f, 123.704346f}, {276.817383f, 123.628662f},
        {277.303711f, 123.518066f}, {277.778809f, 123.377197f}, {278.243164f, 123.209717f}, {278.698242f, 123.018799f},
        {279.145996f, 122.808838f}, {279.650391f, 122.565430f}, {280.131348f, 122.372803f}, {280.592285f, 122.227295f},
        {281.034180f, 122.124756f}, {281.459961f, 122.060547f}, {281.873047f, 122.030762f}, {282.274414f, 122.031006f},
        {282.667480f, 122.057373f}, {283.054199f, 122.105225f}, {283.755371f, 122.254150f}, {284.428223f, 122.431885f},
        {285.072754f, 122.638428f}, {285.691406f, 122.875244f}, {286.286133f, 123.143066f}, {286.857910f, 123.442383f},
        {287.409668f, 123.774170f}, {287.942383f, 124.138916f}, {288.457520f, 124.537842f}, {288.691895f, 124.745117f},
        {288.899414f, 124.927979f}, {289.083496f, 125.089355f}, {289.247559f, 125.231445f}, {289.393066f, 125.357178f},
        {289.525391f, 125.468506f}, {289.645996f, 125.568848f}, {289.758301f, 125.659668f}, {289.865234f, 125.744385f},
        {290.120117f, 125.922363f}, {290.366699f, 126.062012f}, {290.604980f, 126.161865f}, {290.834961f, 126.220215f},
        {291.059082f, 126.234863f}, {291.275879f, 126.203857f}, {291.486328f, 126.125977f}, {291.691895f, 125.999268f},
        {291.892578f, 125.821777f}, {292.149902f, 125.518555f}, {292.407715f, 125.272461f}, {292.665039f, 125.080322f},
        {292.921387f, 124.937744f}, {293.178711f, 124.840576f}, {293.435059f, 124.785156f}, {293.692383f, 124.767822f},
        {293.950195f, 124.783936f}, {294.208496f, 124.829834f}, {294.509277f, 124.915039f}, {294.798828f, 124.983643f},
        {295.077637f, 125.039551f}, {295.346191f, 125.086426f}, {295.604492f, 125.128418f}, {295.853516f, 125.169434f},
        {296.093750f, 125.213623f}, {296.326172f, 125.264648f}, {296.550293f, 125.326904f}, {297.063477f, 125.503662f},
        {297.558594f, 125.624756f}, {298.039062f, 125.695557f}, {298.505859f, 125.720459f}, {298.962402f, 125.705078f},
        {299.409668f, 125.654297f}, {299.850586f, 125.572754f}, {300.287109f, 125.465820f}, {300.722168f, 125.338379f},
        {301.015137f, 125.248535f}, {301.284668f, 125.183838f}, {301.532715f, 125.142822f}, {301.762695f, 125.123047f},
        {301.976562f, 125.122803f}, {302.178223f, 125.139893f}, {302.370117f, 125.173096f}, {302.554199f, 125.219971f},
        {302.733887f, 125.278809f}, {303.665527f, 125.656250f}, {304.588867f, 126.012207f}, {305.506836f, 126.331055f},
        {306.420410f, 126.597168f}, {307.332031f, 126.794189f}, {308.244141f, 126.907471f}, {309.158691f, 126.920410f},
        {310.076172f, 126.818115f}, {311.000488f, 126.584229f}, {311.431641f, 126.405029f}, {311.805664f, 126.274170f},
        {312.126953f, 126.189453f}, {312.402832f, 126.148682f}, {312.636719f, 126.150391f}, {312.836426f, 126.192139f},
        {313.006348f, 126.271973f}, {313.152344f, 126.387939f}, {313.280273f, 126.537842f}, {313.438477f, 126.904785f},
        {313.616699f, 127.209961f}, {313.812012f, 127.460693f}, {314.021973f, 127.662598f}, {314.245117f, 127.822998f},
        {314.479980f, 127.948242f}, {314.723633f, 128.044922f}, {314.974609f, 128.119629f}, {315.231445f, 128.178955f},
        {315.527344f, 128.227051f}, {315.808594f, 128.259521f}, {316.077148f, 128.277100f}, {316.333984f, 128.280762f},
        {316.580566f, 128.271973f}, {316.819336f, 128.251465f}, {317.050781f, 128.220947f}, {317.277344f, 128.180908f},
        {317.500977f, 128.132812f}, {317.861328f, 128.042725f}, {318.206055f, 127.968018f}, {318.535645f, 127.916016f},
        {318.850586f, 127.892822f}, {319.153809f, 127.905762f}, {319.444336f, 127.960938f}, {319.724609f, 128.064941f},
        {319.994629f, 128.224854f}, {320.257324f, 128.447266f}, {320.465332f, 128.676025f}, {320.667969f, 128.837891f},
        {320.864258f, 128.939453f}, {321.053711f, 128.987061f}, {321.235840f, 128.987793f}, {321.410156f, 128.947754f},
        {321.576660f, 128.873779f}, {321.735840f, 128.772705f}, {321.885254f, 128.650879f}, {322.083496f, 128.464600f},
        {322.273438f, 128.314941f}, {322.457031f, 128.202148f}, {322.635254f, 128.125488f}, {322.809082f, 128.084717f},
        {322.979980f, 128.079590f}, {323.149414f, 128.109619f}, {323.317383f, 128.174316f}, {323.486328f, 128.273926f},
        {323.636719f, 128.394775f}, {323.781738f, 128.497314f}, {323.921875f, 128.583252f}, {324.057617f, 128.654541f},
        {324.189453f, 128.713135f}, {324.317871f, 128.760742f}, {324.444336f, 128.799072f}, {324.568848f, 128.830322f},
        {324.692383f, 128.856201f}, {324.885742f, 128.893311f}, {325.069824f, 128.936523f}, {325.245605f, 128.988037f},
        {325.412109f, 129.048828f}, {325.568848f, 129.120850f}, {325.715332f, 129.205566f}, {325.851074f, 129.304443f},
        {325.976074f, 129.419434f}, {326.089844f, 129.551270f}, {326.394043f, 130.000000f}, {326.717285f, 130.373779f},
        {327.057617f, 130.682129f}, {327.412598f, 130.932861f}, {327.780273f, 131.134521f}, {328.158203f, 131.295166f},
        {328.544434f, 131.423584f}, {328.937012f, 131.528564f}, {329.333008f, 131.617432f}, {329.811523f, 131.722168f},
        {330.266602f, 131.833008f}, {330.701172f, 131.945801f}, {331.119141f, 132.057129f}, {331.523926f, 132.163086f},
        {331.917480f, 132.260010f}, {332.304688f, 132.343994f}, {332.687988f, 132.411133f}, {333.070801f, 132.458496f},
        {333.417969f, 132.490479f}, {333.744141f, 132.557373f}, {334.049805f, 132.653809f}, {334.337402f, 132.774658f},
        {334.607422f, 132.914551f}, {334.861816f, 133.069092f}, {335.101074f, 133.232422f}, {335.327637f, 133.399414f},
        {335.542480f, 133.565186f}, {336.122070f, 133.980469f}, {336.710449f, 134.348389f}, {337.299805f, 134.684570f},
        {337.885254f, 135.004639f}, {338.460449f, 135.323975f}, {339.020020f, 135.658691f}, {339.556641f, 136.023682f},
        {340.065918f, 136.435303f}, {340.540527f, 136.908203f}, {340.696777f, 137.107666f}, {340.833496f, 137.273193f},
        {340.952637f, 137.408447f}, {341.056641f, 137.515381f}, {341.147949f, 137.597900f}, {341.227539f, 137.657715f},
        {341.298340f, 137.698486f}, {341.361816f, 137.722656f}, {341.420410f, 137.733643f}, {341.992188f, 137.745605f},
        {342.505371f, 137.863770f}, {342.967285f, 138.073242f}, {343.387207f, 138.359131f}, {343.770996f, 138.706543f},
        {344.127441f, 139.099854f}, {344.464355f, 139.524658f}, {344.789062f, 139.965820f}, {345.109375f, 140.407959f},
        {345.510254f, 140.901123f}, {345.903320f, 141.345703f}, {346.291504f, 141.746826f}, {346.675781f, 142.108643f},
        {347.057617f, 142.436523f}, {347.438477f, 142.733887f}, {347.819336f, 143.005615f}, {348.201660f, 143.256348f},
        {348.587402f, 143.490723f},
    };  // data size = 785

    Vec2 vertices12[] = {
        {347.177734f, 143.445068f}, {346.758789f, 143.131104f}, {346.356445f, 142.779297f}, {345.966309f, 142.401611f},
        {345.585449f, 142.009766f}, {345.208984f, 141.616211f}, {344.833008f, 141.233154f}, {344.453613f, 140.872559f},
        {344.066406f, 140.546631f}, {343.668457f, 140.267090f}, {343.149414f, 140.008057f}, {342.645508f, 139.730957f},
        {342.155273f, 139.452148f}, {341.675293f, 139.186768f}, {341.204590f, 138.950928f}, {340.740234f, 138.760498f},
        {340.281250f, 138.630615f}, {339.823730f, 138.577637f}, {339.366211f, 138.616699f}, {338.840820f, 138.808594f},
        {338.357422f, 138.932129f}, {337.911133f, 138.992188f}, {337.498535f, 138.994385f}, {337.114746f, 138.943604f},
        {336.755371f, 138.844727f}, {336.416016f, 138.703369f}, {336.092285f, 138.523926f}, {335.779785f, 138.312012f},
        {335.520020f, 138.095947f}, {335.276367f, 137.887695f}, {335.046875f, 137.688965f}, {334.829590f, 137.503662f},
        {334.621094f, 137.334229f}, {334.420410f, 137.183594f}, {334.224609f, 137.054443f}, {334.031250f, 136.949951f},
        {333.837402f, 136.872559f}, {333.430664f, 136.777832f}, {333.056641f, 136.642334f}, {332.709961f, 136.473877f},
        {332.385254f, 136.279541f}, {332.078125f, 136.066895f}, {331.784668f, 135.843018f}, {331.497559f, 135.615723f},
        {331.212891f, 135.391846f}, {330.925781f, 135.179199f}, {330.769531f, 135.080078f}, {330.628418f, 134.987793f},
        {330.502930f, 134.900879f}, {330.392090f, 134.815674f}, {330.298340f, 134.730469f}, {330.220215f, 134.641846f},
        {330.160156f, 134.547119f}, {330.117188f, 134.444092f}, {330.091797f, 134.330078f}, {330.010742f, 134.215820f},
        {329.929199f, 134.107422f}, {329.850586f, 134.002686f}, {329.775391f, 133.899902f}, {329.706055f, 133.797363f},
        {329.644043f, 133.694092f}, {329.591797f, 133.587646f}, {329.551270f, 133.476562f}, {329.523438f, 133.359375f},
        {329.490723f, 133.013428f}, {329.424316f, 132.721436f}, {329.327637f, 132.477539f}, {329.204590f, 132.276123f},
        {329.058105f, 132.111572f}, {328.891113f, 131.978516f}, {328.708496f, 131.870605f}, {328.512207f, 131.782715f},
        {328.306641f, 131.708984f}, {327.748535f, 131.553223f}, {327.200195f, 131.411133f}, {326.661133f, 131.273438f},
        {326.133789f, 131.130615f}, {325.618164f, 130.973877f}, {325.115234f, 130.793457f}, {324.626953f, 130.580322f},
        {324.153809f, 130.324707f}, {323.696777f, 130.017822f}, {323.435059f, 129.811768f}, {323.198242f, 129.674561f},
        {322.983398f, 129.598389f}, {322.790039f, 129.574951f}, {322.615234f, 129.596191f}, {322.457520f, 129.653809f},
        {322.315430f, 129.739258f}, {322.187012f, 129.845215f}, {322.069824f, 129.962646f}, {321.861816f, 130.185791f},
        {321.661133f, 130.362305f}, {321.467285f, 130.492432f}, {321.278809f, 130.577148f}, {321.093750f, 130.616211f},
        {320.912598f, 130.610107f}, {320.732910f, 130.559570f}, {320.553711f, 130.465088f}, {320.374512f, 130.326904f},
        {320.255859f, 130.200928f}, {320.143066f, 130.083740f}, {320.035645f, 129.977783f}, {319.933594f, 129.884277f},
        {319.836426f, 129.805176f}, {319.743164f, 129.741699f}, {319.654785f, 129.696289f}, {319.569824f, 129.670166f},
        {319.488281f, 129.665283f}, {319.108887f, 129.772705f}, {318.737305f, 129.812988f}, {318.371582f, 129.802002f},
        {318.011230f, 129.753662f}, {317.653809f, 129.683105f}, {317.299805f, 129.604980f}, {316.947266f, 129.534180f},
        {316.595215f, 129.485352f}, {316.242188f, 129.473389f}, {315.867676f, 129.523926f}, {315.520508f, 129.540283f},
        {315.197754f, 129.521973f}, {314.897949f, 129.470215f}, {314.618652f, 129.384277f}, {314.358398f, 129.264648f},
        {314.114746f, 129.111328f}, {313.885742f, 128.924561f}, {313.669922f, 128.704102f}, {313.270508f, 128.241211f},
        {312.840820f, 127.870361f}, {312.388184f, 127.590576f}, {311.921875f, 127.400635f}, {311.448242f, 127.299072f},
        {310.975098f, 127.284912f}, {310.510742f, 127.356689f}, {310.062500f, 127.513428f}, {309.637695f, 127.753662f},
        {309.470215f, 127.901123f}, {309.324219f, 128.031982f}, {309.198242f, 128.148926f}, {309.089355f, 128.252930f},
        {308.995605f, 128.346924f}, {308.914551f, 128.431885f}, {308.843262f, 128.510498f}, {308.780762f, 128.584229f},
        {308.724121f, 128.655029f}, {308.571289f, 128.839355f}, {308.421387f, 128.984619f}, {308.274414f, 129.089844f},
        {308.130859f, 129.155029f}, {307.992188f, 129.179199f}, {307.858398f, 129.161377f}, {307.730469f, 129.100830f},
        {307.608887f, 128.997070f}, {307.494629f, 128.849854f}, {307.219727f, 128.347656f}, {306.929199f, 127.944092f},
        {306.623047f, 127.629639f}, {306.301270f, 127.394287f}, {305.963867f, 127.227783f}, {305.610840f, 127.120850f},
        {305.241211f, 127.063721f}, {304.855469f, 127.045898f}, {304.454102f, 127.058350f}, {303.892090f, 127.108154f},
        {303.355469f, 127.157471f}, {302.841797f, 127.210938f}, {302.348145f, 127.271240f}, {301.872070f, 127.343018f},
        {301.410156f, 127.429443f}, {300.960938f, 127.534424f}, {300.520508f, 127.661865f}, {300.086426f, 127.815430f},
        {299.739258f, 127.957031f}, {299.409180f, 128.062256f}, {299.094727f, 128.133545f}, {298.794434f, 128.174072f},
        {298.506836f, 128.187012f}, {298.230957f, 128.175293f}, {297.965332f, 128.141357f}, {297.708008f, 128.088379f},
        {297.458984f, 128.019287f}, {297.192383f, 127.932617f}, {296.948242f, 127.872070f}, {296.722656f, 127.838867f},
        {296.514160f, 127.833984f}, {296.320801f, 127.858887f}, {296.139648f, 127.914551f}, {295.971191f, 128.002197f},
        {295.810547f, 128.122803f}, {295.657227f, 128.277588f}, {295.441406f, 128.550781f}, {295.227051f, 128.767822f},
        {295.014160f, 128.930420f}, {294.801270f, 129.040771f}, {294.588379f, 129.101074f}, {294.375000f, 129.113770f},
        {294.160156f, 129.080811f}, {293.943848f, 129.004150f}, {293.725098f, 128.885986f}, {293.321777f, 128.596191f},
        {292.920410f, 128.350342f}, {292.520996f, 128.142334f}, {292.123047f, 127.966309f}, {291.728027f, 127.816650f},
        {291.334961f, 127.688232f}, {290.944336f, 127.574219f}, {290.556152f, 127.469727f}, {290.169922f, 127.368408f},
        {289.865234f, 127.298828f}, {289.594727f, 127.266846f}, {289.355469f, 127.271729f}, {289.146484f, 127.312500f},
        {288.964844f, 127.388184f}, {288.809570f, 127.497559f}, {288.677246f, 127.639648f}, {288.567383f, 127.813232f},
        {288.476562f, 128.017334f}, {288.416992f, 128.223633f}, {288.355957f, 128.414062f}, {288.294434f, 128.590332f},
        {288.231934f, 128.753418f}, {288.167969f, 128.906006f}, {288.101074f, 129.048340f}, {288.033691f, 129.182617f},
        {287.962891f, 129.310303f}, {287.889160f, 129.433105f}, {287.895508f, 129.665771f}, {287.928223f, 129.844971f},
        {287.982910f, 129.975342f}, {288.055176f, 130.062012f}, {288.140625f, 130.110596f}, {288.235352f, 130.126221f},
        {288.333496f, 130.114258f}, {288.432129f, 130.079834f}, {288.525391f, 130.027832f}, {288.895508f, 129.751953f},
        {289.252930f, 129.572266f}, {289.600098f, 129.477295f}, {289.937500f, 129.456055f}, {290.267578f, 129.496826f},
        {290.591309f, 129.588867f}, {290.910156f, 129.720703f}, {291.226074f, 129.880859f}, {291.540527f, 130.058594f},
        {291.696777f, 130.148682f}, {291.836914f, 130.227783f}, {291.962402f, 130.297852f}, {292.074219f, 130.360596f},
        {292.174316f, 130.417969f}, {292.263672f, 130.471924f}, {292.344238f, 130.523926f}, {292.416992f, 130.575928f},
        {292.482910f, 130.629639f}, {292.825195f, 130.934082f}, {293.161621f, 131.156738f}, {293.493652f, 131.302246f},
        {293.820801f, 131.375732f}, {294.144043f, 131.381836f}, {294.462891f, 131.324951f}, {294.777344f, 131.210205f},
        {295.087891f, 131.041992f}, {295.394043f, 130.825439f}, {295.644043f, 130.609619f}, {295.875977f, 130.432129f},
        {296.093262f, 130.291992f}, {296.298828f, 130.187744f}, {296.495117f, 130.117188f}, {296.685547f, 130.079834f},
        {296.874023f, 130.073486f}, {297.061523f, 130.096924f}, {297.253418f, 130.148926f}, {297.617188f, 130.291260f},
        {297.969727f, 130.390137f}, {298.312012f, 130.447754f}, {298.644531f, 130.466309f}, {298.968262f, 130.448730f},
        {299.284180f, 130.396729f}, {299.592773f, 130.313721f}, {299.895996f, 130.201416f}, {300.193848f, 130.062256f},
        {300.470703f, 129.905762f}, {300.733398f, 129.768799f}, {300.983887f, 129.652344f}, {301.223633f, 129.555908f},
        {301.455078f, 129.479980f}, {301.679199f, 129.424316f}, {301.898438f, 129.389404f}, {302.114258f, 129.375488f},
        {302.328613f, 129.382324f}, {302.653809f, 129.422607f}, {302.954590f, 129.427979f}, {303.233398f, 129.400146f},
        {303.490723f, 129.340088f}, {303.729492f, 129.249268f}, {303.952637f, 129.128418f}, {304.160156f, 128.978760f},
        {304.355469f, 128.801758f}, {304.540039f, 128.598145f}, {304.614258f, 128.518799f}, {304.679688f, 128.450928f},
        {304.735840f, 128.394287f}, {304.784668f, 128.346680f}, {304.827148f, 128.306885f}, {304.864258f, 128.274170f},
        {304.896973f, 128.246582f}, {304.927246f, 128.223145f}, {304.954590f, 128.202881f}, {305.094727f, 128.125977f},
        {305.229492f, 128.072021f}, {305.356934f, 128.041260f}, {305.478516f, 128.034912f}, {305.594238f, 128.053223f},
        {305.702637f, 128.097412f}, {305.805176f, 128.167969f}, {305.900391f, 128.265869f}, {305.990234f, 128.391602f},
        {306.028320f, 128.465576f}, {306.062500f, 128.531006f}, {306.092773f, 128.588379f}, {306.120117f, 128.639404f},
        {306.145020f, 128.684326f}, {306.167480f, 128.724609f}, {306.187988f, 128.760986f}, {306.207520f, 128.794189f},
        {306.226074f, 128.825928f}, {306.356934f, 129.070068f}, {306.482910f, 129.316895f}, {306.608887f, 129.561035f},
        {306.739258f, 129.797119f}, {306.878418f, 130.019531f}, {307.033203f, 130.222656f}, {307.206543f, 130.401367f},
        {307.403320f, 130.550049f}, {307.629395f, 130.663574f}, {307.873535f, 130.713623f}, {308.100098f, 130.754395f},
        {308.309082f, 130.781006f}, {308.502441f, 130.789062f}, {308.680176f, 130.773926f}, {308.842773f, 130.730713f},
        {308.991211f, 130.654541f}, {309.125977f, 130.541260f}, {309.247559f, 130.385742f}, {309.342285f, 130.203613f},
        {309.434082f, 130.055908f}, {309.523926f, 129.941406f}, {309.613281f, 129.859863f}, {309.700684f, 129.810791f},
        {309.789062f, 129.793213f}, {309.877441f, 129.807373f}, {309.967773f, 129.851807f}, {310.059082f, 129.926758f},
        {310.219238f, 130.104980f}, {310.378906f, 130.249268f}, {310.539062f, 130.362305f}, {310.699707f, 130.447021f},
        {310.862305f, 130.506104f}, {311.025879f, 130.542236f}, {311.191406f, 130.558350f}, {311.359863f, 130.557373f},
        {311.531250f, 130.541504f}, {311.816406f, 130.499756f}, {312.090332f, 130.479248f}, {312.354492f, 130.478516f},
        {312.608887f, 130.497803f}, {312.854980f, 130.535645f}, {313.093750f, 130.592041f}, {313.325684f, 130.665283f},
        {313.552734f, 130.755127f}, {313.774902f, 130.860596f}, {313.915527f, 130.943848f}, {314.045898f, 131.025635f},
        {314.166016f, 131.103516f}, {314.277832f, 131.175537f}, {314.381836f, 131.239502f}, {314.478516f, 131.292725f},
        {314.570801f, 131.333984f}, {314.657715f, 131.360352f}, {314.742188f, 131.370117f}, {315.118652f, 131.291504f},
        {315.491211f, 131.233887f}, {315.859375f, 131.195068f}, {316.223633f, 131.170654f}, {316.585449f, 131.158447f},
        {316.944824f, 131.155762f}, {317.302246f, 131.158691f}, {317.659180f, 131.165527f}, {318.015625f, 131.172119f},
        {318.304199f, 131.173828f}, {318.563477f, 131.177490f}, {318.794922f, 131.187256f}, {319.002441f, 131.207275f},
        {319.188965f, 131.241211f}, {319.356445f, 131.293213f}, {319.509277f, 131.366943f}, {319.649414f, 131.466797f},
        {319.779297f, 131.596436f}, {320.014160f, 131.912109f}, {320.245605f, 132.165527f}, {320.475586f, 132.358154f},
        {320.704590f, 132.490479f}, {320.934570f, 132.563477f}, {321.165527f, 132.577393f}, {321.399414f, 132.533691f},
        {321.636719f, 132.433350f}, {321.879883f, 132.276367f}, {322.109863f, 132.075195f}, {322.329102f, 131.906250f},
        {322.538574f, 131.771240f}, {322.740234f, 131.673096f}, {322.934570f, 131.613770f}, {323.123535f, 131.595215f},
        {323.309082f, 131.619629f}, {323.491699f, 131.689209f}, {323.672852f, 131.805908f}, {323.829102f, 131.947998f},
        {323.979492f, 132.054688f}, {324.123535f, 132.130371f}, {324.262695f, 132.179443f}, {324.397949f, 132.205811f},
        {324.529297f, 132.214111f}, {324.657715f, 132.208740f}, {324.784180f, 132.193604f}, {324.908691f, 132.173340f},
        {325.098633f, 132.145996f}, {325.281738f, 132.128174f}, {325.458496f, 132.119141f}, {325.630371f, 132.117920f},
        {325.797363f, 132.124756f}, {325.960449f, 132.138916f}, {326.121094f, 132.159180f}, {326.279297f, 132.186035f},
        {326.436035f, 132.217773f}, {326.623047f, 132.265381f}, {326.791016f, 132.314209f}, {326.937012f, 132.368652f},
        {327.061035f, 132.433594f}, {327.160645f, 132.513428f}, {327.233887f, 132.612061f}, {327.279297f, 132.734619f},
        {327.295410f, 132.885254f}, {327.279785f, 133.068848f}, {327.225098f, 133.327881f}, {327.201660f, 133.557861f},
        {327.208008f, 133.760010f}, {327.242676f, 133.936279f}, {327.302734f, 134.088623f}, {327.387695f, 134.218506f},
        {327.495117f, 134.327393f}, {327.623047f, 134.416992f}, {327.770996f, 134.489258f}, {328.083008f, 134.595459f},
        {328.372559f, 134.722412f}, {328.642090f, 134.869141f}, {328.892578f, 135.034668f}, {329.125977f, 135.218506f},
        {329.343262f, 135.419434f}, {329.546387f, 135.636719f}, {329.736816f, 135.869629f}, {329.916504f, 136.116943f},
        {330.177246f, 136.156738f}, {330.414551f, 136.229736f}, {330.631348f, 136.329102f}, {330.831543f, 136.447510f},
        {331.018555f, 136.579346f}, {331.196777f, 136.717041f}, {331.369141f, 136.854004f}, {331.538574f, 136.983643f},
        {331.709961f, 137.099365f}, {332.023438f, 137.273682f}, {332.343750f, 137.395508f}, {332.665527f, 137.481445f},
        {332.985352f, 137.549561f}, {333.297852f, 137.616699f}, {333.598145f, 137.701172f}, {333.882324f, 137.819336f},
        {334.144043f, 137.989258f}, {334.379883f, 138.228271f}, {334.597168f, 138.469482f}, {334.812012f, 138.672119f},
        {335.023926f, 138.841797f}, {335.232422f, 138.985596f}, {335.437500f, 139.109375f}, {335.637695f, 139.218994f},
        {335.833008f, 139.320801f}, {336.022949f, 139.420898f}, {336.207031f, 139.525635f}, {338.633789f, 139.640625f},
        {338.951172f, 139.634277f}, {339.262207f, 139.660889f}, {339.566406f, 139.717773f}, {339.864258f, 139.801270f},
        {340.155273f, 139.909180f}, {340.440430f, 140.038330f}, {340.719238f, 140.185547f}, {340.992188f, 140.348145f},
        {341.259766f, 140.522949f}, {341.709961f, 140.815674f}, {342.161133f, 141.056396f}, {342.610352f, 141.260498f},
        {343.053711f, 141.442383f}, {343.487305f, 141.617188f}, {343.907715f, 141.799561f}, {344.310547f, 142.004639f},
        {344.692871f, 142.246826f}, {345.051270f, 142.541260f}, {345.230469f, 142.760010f}, {345.398438f, 142.941650f},
        {345.555664f, 143.089600f}, {345.704102f, 143.207275f}, {345.846191f, 143.297607f}, {345.981934f, 143.363281f},
        {346.114258f, 143.407959f}, {346.244141f, 143.434326f}, {346.374023f, 143.446045f}, {346.477539f, 143.496338f},
        {346.573242f, 143.535400f}, {346.662598f, 143.563232f}, {346.746582f, 143.579834f}, {346.826172f, 143.585449f},
        {346.901367f, 143.579590f}, {346.974121f, 143.562744f}, {347.043945f, 143.534912f}, {347.112305f, 143.496094f},
    };  // data size = 524

    Vec2 vertices13[] = {
        {206.011230f, 100.587891f}, {206.281250f, 100.586426f}, {206.550781f, 100.583008f}, {206.821289f, 100.578857f},
        {207.090820f, 100.574219f}, {207.361328f, 100.570557f}, {207.630859f, 100.568359f}, {207.900879f, 100.569580f},
        {208.170410f, 100.574463f}, {208.439941f, 100.584229f}, {208.916016f, 100.605713f}, {209.368652f, 100.601807f},
        {209.797363f, 100.568115f}, {210.205566f, 100.501221f}, {210.593750f, 100.397217f}, {210.964355f, 100.251953f},
        {211.318848f, 100.062012f}, {211.658203f, 99.822754f},  {211.984863f, 99.531250f},  {212.315430f, 99.207031f},
        {212.679199f, 98.963623f},  {213.067871f, 98.795654f},  {213.470703f, 98.698242f},  {213.877930f, 98.665039f},
        {214.278809f, 98.691162f},  {214.664551f, 98.770752f},  {215.024414f, 98.898438f},  {215.348145f, 99.068604f},
        {215.670410f, 99.329834f},  {215.980469f, 99.554688f},  {216.281250f, 99.744385f},  {216.576660f, 99.899414f},
        {216.870605f, 100.021240f}, {217.165039f, 100.110352f}, {217.463379f, 100.167480f}, {217.770020f, 100.193848f},
        {218.086426f, 100.190430f}, {218.679688f, 100.116699f}, {219.256836f, 100.057861f}, {219.819336f, 100.018066f},
        {220.369141f, 100.000977f}, {220.908203f, 100.010742f}, {221.438477f, 100.051514f}, {221.961914f, 100.127686f},
        {222.479492f, 100.242676f}, {222.994629f, 100.400879f}, {223.525879f, 100.613770f}, {224.040039f, 100.784180f},
        {224.537109f, 100.918945f}, {225.019043f, 101.024170f}, {225.487305f, 101.106934f}, {225.943359f, 101.172607f},
        {226.388184f, 101.228516f}, {226.824707f, 101.281006f}, {227.252441f, 101.336426f}, {227.475098f, 101.364746f},
        {227.676270f, 101.379150f}, {227.858887f, 101.385254f}, {228.022949f, 101.388672f}, {228.171875f, 101.395020f},
        {228.305664f, 101.410156f}, {228.426758f, 101.439941f}, {228.535645f, 101.490234f}, {228.635742f, 101.566650f},
        {228.798340f, 101.744629f}, {228.966797f, 101.895996f}, {229.137695f, 102.026123f}, {229.311035f, 102.140137f},
        {229.484375f, 102.242432f}, {229.656738f, 102.338623f}, {229.825195f, 102.433594f}, {229.990723f, 102.532471f},
        {230.148926f, 102.640381f}, {231.425781f, 102.761719f}, {231.446777f, 102.743652f}, {231.465332f, 102.725586f},
        {231.480957f, 102.707031f}, {231.492676f, 102.688965f}, {231.501953f, 102.670898f}, {231.507812f, 102.652832f},
        {231.511230f, 102.634766f}, {231.511230f, 102.616699f}, {231.508301f, 102.598877f}, {231.499023f, 102.576660f},
        {231.489746f, 102.557373f}, {231.481445f, 102.540771f}, {231.472656f, 102.526611f}, {231.464844f, 102.514893f},
        {231.456543f, 102.505615f}, {231.448730f, 102.498779f}, {231.441406f, 102.493896f}, {231.433105f, 102.490967f},
        {231.312988f, 102.475830f}, {231.193359f, 102.453125f}, {231.075195f, 102.422363f}, {230.959473f, 102.383057f},
        {230.849609f, 102.334229f}, {230.746094f, 102.275879f}, {230.651855f, 102.206543f}, {230.567383f, 102.126221f},
        {230.495605f, 102.034424f}, {230.125488f, 101.363037f}, {229.707520f, 100.842773f}, {229.250488f, 100.452393f},
        {228.761230f, 100.170654f}, {228.247070f, 99.976074f},  {227.715820f, 99.847412f},  {227.175293f, 99.763672f},
        {226.632812f, 99.703125f},  {226.096191f, 99.645020f},  {225.389648f, 99.524414f},  {224.712402f, 99.411621f},
        {224.062500f, 99.299316f},  {223.437500f, 99.181396f},  {222.835449f, 99.050293f},  {222.253906f, 98.898682f},
        {221.690918f, 98.720459f},  {221.144043f, 98.508057f},  {220.610840f, 98.254639f},  {220.261719f, 98.048096f},
        {219.942871f, 97.876953f},  {219.652832f, 97.745117f},  {219.386719f, 97.656738f},  {219.141602f, 97.615479f},
        {218.914551f, 97.625732f},  {218.702148f, 97.691406f},  {218.501465f, 97.816650f},  {218.309082f, 98.005371f},
        {218.125977f, 98.251465f},  {217.949219f, 98.433594f},  {217.779297f, 98.553711f},  {217.617188f, 98.614990f},
        {217.464844f, 98.619141f},  {217.320312f, 98.569092f},  {217.187500f, 98.467285f},  {217.064941f, 98.316650f},
        {216.954102f, 98.118896f},  {216.874512f, 97.901123f},  {216.799316f, 97.700195f},  {216.727051f, 97.515381f},
        {216.655273f, 97.345703f},  {216.581055f, 97.189941f},  {216.503906f, 97.047119f},  {216.419922f, 96.916260f},
        {216.327637f, 96.796143f},  {216.225586f, 96.686279f},  {216.027832f, 96.533936f},  {215.841797f, 96.409912f},
        {215.667480f, 96.318115f},  {215.505371f, 96.262695f},  {215.354980f, 96.247803f},  {215.216797f, 96.277344f},
        {215.091309f, 96.355713f},  {214.978027f, 96.486572f},  {214.877441f, 96.674561f},  {214.778809f, 96.951172f},
        {214.670898f, 97.173096f},  {214.555176f, 97.343994f},  {214.431641f, 97.469482f},  {214.302734f, 97.553711f},
        {214.167969f, 97.601318f},  {214.031250f, 97.617188f},  {213.891113f, 97.605713f},  {213.750488f, 97.572021f},
        {213.421387f, 97.460205f},  {213.120605f, 97.405762f},  {212.845215f, 97.404297f},  {212.592773f, 97.452393f},
        {212.360352f, 97.545166f},  {212.145508f, 97.679199f},  {211.945801f, 97.850098f},  {211.758789f, 98.054199f},
        {211.581055f, 98.286621f},  {211.366211f, 98.615723f},  {211.151855f, 98.912842f},  {210.937012f, 99.172607f},
        {210.719727f, 99.390137f},  {210.497070f, 99.560791f},  {210.266602f, 99.679688f},  {210.027344f, 99.741699f},
        {209.776855f, 99.741943f},  {209.512695f, 99.675537f},  {209.181641f, 99.498291f},  {208.874512f, 99.364258f},
        {208.587402f, 99.273193f},  {208.318848f, 99.225586f},  {208.065430f, 99.222168f},  {207.825684f, 99.262695f},
        {207.595703f, 99.347412f},  {207.374023f, 99.476807f},  {207.157715f, 99.650879f},  {207.018066f, 99.797119f},
        {206.885254f, 99.925293f},  {206.759277f, 100.037842f}, {206.638184f, 100.137451f}, {206.523438f, 100.225830f},
        {206.413086f, 100.305664f}, {206.306641f, 100.379395f}, {206.205078f, 100.449463f}, {206.106445f, 100.517578f},
    };  // data size = 200

    Vec2 vertices14[] = {
        {131.020020f, 137.745850f}, {131.264160f, 138.044434f}, {131.443359f, 138.347900f}, {131.562988f, 138.656250f},
        {131.626953f, 138.968262f}, {131.642090f, 139.283203f}, {131.612793f, 139.601074f}, {131.544922f, 139.920654f},
        {131.443848f, 140.241943f}, {131.314941f, 140.563477f}, {131.214355f, 140.767334f}, {131.122559f, 140.952393f},
        {131.040039f, 141.121826f}, {130.968262f, 141.278564f}, {130.906738f, 141.425537f}, {130.857422f, 141.566162f},
        {130.821289f, 141.702881f}, {130.798828f, 141.839355f}, {130.791016f, 141.978271f}, {130.819336f, 142.194824f},
        {130.862793f, 142.392334f}, {130.918945f, 142.571777f}, {130.987305f, 142.732666f}, {131.066895f, 142.875244f},
        {131.157227f, 143.000244f}, {131.256348f, 143.106934f}, {131.364258f, 143.196289f}, {131.479492f, 143.267822f},
        {131.634766f, 143.310791f}, {131.770020f, 143.315186f}, {131.888672f, 143.285889f}, {131.991699f, 143.228027f},
        {132.080078f, 143.145264f}, {132.155762f, 143.043457f}, {132.220215f, 142.926514f}, {132.273926f, 142.798584f},
        {132.319824f, 142.665527f}, {132.380859f, 142.468750f}, {132.450195f, 142.284424f}, {132.522949f, 142.109375f},
        {132.597168f, 141.941162f}, {132.667969f, 141.776367f}, {132.731934f, 141.612793f}, {132.785645f, 141.446777f},
        {132.825195f, 141.275635f}, {132.846680f, 141.096191f}, {132.846680f, 140.917725f}, {132.864258f, 140.755127f},
        {132.895996f, 140.608643f}, {132.942383f, 140.478271f}, {133.000488f, 140.363770f}, {133.070312f, 140.265137f},
        {133.150391f, 140.182373f}, {133.238770f, 140.115479f}, {133.335449f, 140.064453f}, {133.460938f, 140.041748f},
        {133.572754f, 140.046387f}, {133.672852f, 140.073730f}, {133.761230f, 140.120850f}, {133.840332f, 140.183350f},
        {133.911621f, 140.257568f}, {133.976074f, 140.340332f}, {134.035645f, 140.427246f}, {134.090820f, 140.514893f},
        {134.312500f, 140.910889f}, {134.466309f, 141.300049f}, {134.553711f, 141.678223f}, {134.576660f, 142.039795f},
        {134.535645f, 142.380615f}, {134.430664f, 142.695312f}, {134.264160f, 142.979492f}, {134.036133f, 143.227783f},
        {133.748535f, 143.436035f}, {133.442871f, 143.563721f}, {133.190918f, 143.683838f}, {132.989746f, 143.801758f},
        {132.838867f, 143.923828f}, {132.734375f, 144.055420f}, {132.675293f, 144.202881f}, {132.659180f, 144.372070f},
        {132.684082f, 144.568604f}, {132.747559f, 144.798828f}, {132.875000f, 145.218262f}, {132.904785f, 145.571045f},
        {132.854004f, 145.868164f}, {132.739746f, 146.119873f}, {132.577637f, 146.337646f}, {132.386719f, 146.532715f},
        {132.181641f, 146.715576f}, {131.979980f, 146.897217f}, {131.799805f, 147.088867f}, {131.671875f, 147.269531f},
        {131.543457f, 147.371338f}, {131.416504f, 147.406738f}, {131.292969f, 147.385986f}, {131.175293f, 147.320801f},
        {131.065430f, 147.222656f}, {130.965332f, 147.102539f}, {130.876953f, 146.971924f}, {130.803711f, 146.841797f},
        {130.666504f, 146.570557f}, {130.519531f, 146.336670f}, {130.363281f, 146.136475f}, {130.198730f, 145.965332f},
        {130.025391f, 145.820557f}, {129.843750f, 145.697266f}, {129.655273f, 145.592529f}, {129.459961f, 145.501953f},
        {129.257324f, 145.421875f}, {129.014160f, 145.342285f}, {128.776367f, 145.268311f}, {128.544434f, 145.196533f},
        {128.321777f, 145.123535f}, {128.110840f, 145.047119f}, {127.914551f, 144.963135f}, {127.734863f, 144.869141f},
        {127.574219f, 144.761475f}, {127.435547f, 144.637207f}, {127.139160f, 144.258545f}, {126.844238f, 143.994873f},
        {126.550293f, 143.829346f}, {126.258301f, 143.744873f}, {125.966309f, 143.725098f}, {125.675293f, 143.753174f},
        {125.386230f, 143.812256f}, {125.097656f, 143.885498f}, {124.809570f, 143.956055f}, {124.583008f, 143.995850f},
        {124.379883f, 144.045410f}, {124.196777f, 144.105957f}, {124.033203f, 144.177979f}, {123.885742f, 144.261719f},
        {123.752441f, 144.358154f}, {123.632324f, 144.467529f}, {123.522461f, 144.590576f}, {123.420410f, 144.727539f},
        {123.274414f, 144.948730f}, {123.120605f, 145.136719f}, {122.959961f, 145.292480f}, {122.793457f, 145.416016f},
        {122.622070f, 145.508545f}, {122.447266f, 145.570801f}, {122.270508f, 145.603271f}, {122.092285f, 145.606934f},
        {121.914551f, 145.582275f}, {121.713867f, 145.514893f}, {121.517578f, 145.448730f}, {121.331055f, 145.377441f},
        {121.160156f, 145.292725f}, {121.009766f, 145.187744f}, {120.885742f, 145.054932f}, {120.793945f, 144.887451f},
        {120.738770f, 144.677734f}, {120.726562f, 144.418457f}, {120.745117f, 144.171631f}, {120.719238f, 143.971436f},
        {120.655762f, 143.812744f}, {120.562500f, 143.690674f}, {120.444824f, 143.600342f}, {120.309082f, 143.537109f},
        {120.163086f, 143.496338f}, {120.011719f, 143.472900f}, {119.863281f, 143.461914f}, {119.286621f, 143.458740f},
        {118.716797f, 143.455566f}, {118.154297f, 143.452637f}, {117.597656f, 143.450439f}, {117.046387f, 143.449219f},
        {116.498535f, 143.448975f}, {115.954590f, 143.449951f}, {115.413086f, 143.452637f}, {114.873047f, 143.457275f},
        {114.534180f, 143.455566f}, {114.232422f, 143.438965f}, {113.964844f, 143.405518f}, {113.729004f, 143.353760f},
        {113.522461f, 143.281006f}, {113.342285f, 143.186035f}, {113.185547f, 143.067139f}, {113.050781f, 142.921631f},
        {112.934082f, 142.747803f}, {112.696289f, 142.258057f}, {112.436523f, 141.832031f}, {112.155273f, 141.466064f},
        {111.854980f, 141.155273f}, {111.535645f, 140.895264f}, {111.200195f, 140.681641f}, {110.848633f, 140.510010f},
        {110.482422f, 140.375488f}, {110.102539f, 140.273926f}, {109.831055f, 140.218506f}, {109.605469f, 140.150146f},
        {109.421387f, 140.067627f}, {109.275391f, 139.972168f}, {109.163086f, 139.862549f}, {109.081543f, 139.739014f},
        {109.025879f, 139.601807f}, {108.992676f, 139.450439f}, {108.978027f, 139.284668f}, {108.836426f, 139.036133f},
        {108.699219f, 138.850830f}, {108.565918f, 138.726074f}, {108.439453f, 138.658447f}, {108.317871f, 138.645508f},
        {108.204102f, 138.684326f}, {108.097168f, 138.772217f}, {107.999023f, 138.906006f}, {107.910156f, 139.083008f},
        {107.657227f, 139.828613f}, {107.429199f, 140.384521f}, {107.215332f, 140.765137f}, {107.008789f, 140.985107f},
        {106.798828f, 141.059570f}, {106.577148f, 141.002441f}, {106.334473f, 140.828857f}, {106.061035f, 140.553223f},
        {105.749512f, 140.190186f}, {105.320312f, 139.696045f}, {104.924805f, 139.297363f}, {104.553711f, 138.991211f},
        {104.196289f, 138.773438f}, {103.843262f, 138.639893f}, {103.483398f, 138.586670f}, {103.107422f, 138.610840f},
        {102.705078f, 138.707520f}, {102.266602f, 138.873535f}, {101.780762f, 139.376221f}, {101.659668f, 139.630371f},
        {101.530273f, 139.838867f}, {101.390625f, 140.004150f}, {101.239746f, 140.127930f}, {101.076660f, 140.211914f},
        {100.899902f, 140.258545f}, {100.708008f, 140.269043f}, {100.500977f, 140.245850f}, {100.276367f, 140.190186f},
        {99.839355f, 140.031982f},  {99.410645f, 139.896240f},  {98.990723f, 139.776367f},  {98.580566f, 139.664795f},
        {98.178223f, 139.554199f},  {97.784668f, 139.437500f},  {97.400879f, 139.307373f},  {97.025879f, 139.156738f},
        {96.659668f, 138.978516f},  {96.327148f, 138.750732f},  {96.036621f, 138.520508f},  {95.784668f, 138.286377f},
        {95.568848f, 138.045410f},  {95.385742f, 137.796387f},  {95.232910f, 137.536377f},  {95.106445f, 137.263672f},
        {95.004883f, 136.976074f},  {94.924805f, 136.671631f},  {94.840820f, 136.249023f},  {94.745117f, 135.903564f},
        {94.635254f, 135.632812f},  {94.510254f, 135.433350f},  {94.368164f, 135.301514f},  {94.206543f, 135.234863f},
        {94.025391f, 135.229980f},  {93.821289f, 135.283447f},  {93.594727f, 135.392578f},  {93.361328f, 135.551758f},
        {93.142578f, 135.703369f},  {92.936035f, 135.848877f},  {92.740723f, 135.989014f},  {92.555664f, 136.125244f},
        {92.378906f, 136.258789f},  {92.209961f, 136.390869f},  {92.046387f, 136.522705f},  {91.887207f, 136.655518f},
        {91.524414f, 136.944336f},  {91.178223f, 137.155518f},  {90.850098f, 137.289795f},  {90.537598f, 137.348877f},
        {90.242188f, 137.333740f},  {89.962402f, 137.245361f},  {89.698730f, 137.084961f},  {89.450195f, 136.853271f},
        {89.216797f, 136.552002f},  {88.940918f, 136.038818f},  {88.711914f, 135.633301f},  {88.516602f, 135.329346f},
        {88.341797f, 135.121826f},  {88.173340f, 135.004150f},  {87.999023f, 134.971436f},  {87.805176f, 135.017090f},
        {87.577148f, 135.136230f},  {87.302734f, 135.322266f},  {87.127441f, 135.445801f},  {86.969727f, 135.543213f},
        {86.828125f, 135.617188f},  {86.700195f, 135.670898f},  {86.583496f, 135.707031f},  {86.476074f, 135.728516f},
        {86.376953f, 135.739014f},  {86.282227f, 135.740479f},  {86.191406f, 135.736328f},  {86.051270f, 135.727539f},
        {85.915527f, 135.724609f},  {85.784180f, 135.729248f},  {85.658203f, 135.741699f},  {85.538086f, 135.763916f},
        {85.423828f, 135.796631f},  {85.315918f, 135.841064f},  {85.215820f, 135.898193f},  {85.122559f, 135.969482f},
        {84.854004f, 136.246094f},  {84.611816f, 136.431152f},  {84.392578f, 136.532471f},  {84.193848f, 136.557373f},
        {84.012695f, 136.513916f},  {83.844238f, 136.408691f},  {83.687012f, 136.250732f},  {83.536621f, 136.046387f},
        {83.391113f, 135.803467f},  {83.110352f, 135.294189f},  {82.848145f, 134.897217f},  {82.600586f, 134.610840f},
        {82.365723f, 134.433105f},  {82.140625f, 134.361572f},  {81.923340f, 134.394043f},  {81.710938f, 134.529053f},
        {81.500488f, 134.763672f},  {81.289551f, 135.096436f},  {81.209473f, 135.260010f},  {81.139648f, 135.399170f},
        {81.078613f, 135.516113f},  {81.023438f, 135.613281f},  {80.972656f, 135.692139f},  {80.925293f, 135.755127f},
        {80.877930f, 135.803711f},  {80.830566f, 135.840332f},  {80.779785f, 135.866699f},  {80.651855f, 135.771484f},
        {80.558594f, 135.641357f},  {80.490234f, 135.486572f},  {80.437988f, 135.317627f},  {80.392090f, 135.144775f},
        {80.343262f, 134.979248f},  {80.281738f, 134.830566f},  {80.197754f, 134.709473f},  {80.083008f, 134.626465f},
        {79.867676f, 134.602783f},  {79.659668f, 134.568359f},  {79.457520f, 134.529785f},  {79.261230f, 134.494629f},
        {79.071289f, 134.468750f},  {78.885742f, 134.459229f},  {78.706055f, 134.472900f},  {78.530273f, 134.516602f},
        {78.359375f, 134.596924f},  {78.329102f, 134.798828f},  {78.312500f, 134.988525f},  {78.303223f, 135.168701f},
        {78.294922f, 135.342041f},  {78.282715f, 135.510986f},  {78.258301f, 135.677734f},  {78.218262f, 135.845459f},
        {78.154297f, 136.015869f},  {78.062012f, 136.192139f},  {77.880859f, 136.478760f},  {77.772461f, 136.760010f},
        {77.728027f, 137.034912f},  {77.739746f, 137.302490f},  {77.796875f, 137.561523f},  {77.892578f, 137.811279f},
        {78.017578f, 138.051270f},  {78.162109f, 138.279785f},  {78.318848f, 138.496338f},  {78.559082f, 138.772217f},
        {78.796875f, 138.994873f},  {79.032227f, 139.165039f},  {79.264648f, 139.284668f},  {79.493652f, 139.355225f},
        {79.719238f, 139.377930f},  {79.940918f, 139.354248f},  {80.157715f, 139.285400f},  {80.370117f, 139.173096f},
        {80.506836f, 139.057373f},  {80.627441f, 138.944580f},  {80.733887f, 138.834717f},  {80.828613f, 138.727295f},
        {80.914062f, 138.623291f},  {80.991699f, 138.521729f},  {81.062988f, 138.422852f},  {81.131348f, 138.327148f},
        {81.197266f, 138.233887f},  {81.234375f, 138.173096f},  {81.258789f, 138.133057f},  {81.273438f, 138.109619f},
        {81.281250f, 138.097656f},  {81.284668f, 138.093994f},  {81.286133f, 138.093750f},  {81.289551f, 138.092529f},
        {81.297852f, 138.086182f},  {81.312500f, 138.070557f},  {81.404785f, 137.931641f},  {81.481445f, 137.772217f},
        {81.548340f, 137.602051f},  {81.612305f, 137.430664f},  {81.679199f, 137.267578f},  {81.755371f, 137.121338f},
        {81.847168f, 137.001953f},  {81.960449f, 136.918701f},  {82.102539f, 136.881104f},  {82.296387f, 136.940674f},
        {82.459473f, 137.028320f},  {82.594238f, 137.141113f},  {82.705078f, 137.274414f},  {82.795410f, 137.424072f},
        {82.868164f, 137.586914f},  {82.926758f, 137.758545f},  {82.975586f, 137.935303f},  {83.017578f, 138.112549f},
        {83.057617f, 138.291748f},  {83.097168f, 138.460449f},  {83.136719f, 138.619873f},  {83.177246f, 138.770264f},
        {83.220703f, 138.912109f},  {83.266602f, 139.046631f},  {83.316895f, 139.174316f},  {83.372559f, 139.295410f},
        {83.434082f, 139.411133f},  {83.630859f, 139.673584f},  {83.830566f, 139.873535f},  {84.029297f, 140.011719f},
        {84.224609f, 140.088379f},  {84.412109f, 140.103760f},  {84.589355f, 140.058594f},  {84.752441f, 139.952637f},
        {84.898926f, 139.786865f},  {85.024902f, 139.561523f},  {85.138672f, 139.205566f},  {85.251953f, 138.900391f},
        {85.367188f, 138.648438f},  {85.489258f, 138.451416f},  {85.621094f, 138.311279f},  {85.766113f, 138.229980f},
        {85.926758f, 138.209961f},  {86.108398f, 138.252686f},  {86.312500f, 138.360596f},  {86.413086f, 138.437256f},
        {86.503906f, 138.500977f},  {86.585449f, 138.552246f},  {86.659180f, 138.591553f},  {86.726074f, 138.620117f},
        {86.785645f, 138.637939f},  {86.840332f, 138.645508f},  {86.889648f, 138.643799f},  {86.934570f, 138.633545f},
        {87.284180f, 138.479248f},  {87.616211f, 138.407715f},  {87.932617f, 138.407959f},  {88.234375f, 138.468506f},
        {88.525391f, 138.578125f},  {88.806641f, 138.725342f},  {89.081055f, 138.898926f},  {89.350586f, 139.087891f},
        {89.617676f, 139.280762f},  {90.053223f, 139.563721f},  {90.477539f, 139.820068f},  {90.893066f, 140.048828f},
        {91.301758f, 140.248779f},  {91.705566f, 140.419434f},  {92.106934f, 140.559570f},  {92.506836f, 140.668701f},
        {92.909668f, 140.745605f},  {93.314453f, 140.789551f},  {94.052734f, 140.800293f},  {94.762207f, 140.848389f},
        {95.445801f, 140.931152f},  {96.105957f, 141.046875f},  {96.746094f, 141.193359f},  {97.367676f, 141.367920f},
        {97.975098f, 141.569092f},  {98.569336f, 141.794434f},  {99.154785f, 142.041504f},  {99.548340f, 142.217529f},
        {99.899902f, 142.353271f},  {100.214355f, 142.448242f}, {100.497559f, 142.502441f}, {100.752441f, 142.514648f},
        {100.984375f, 142.484619f}, {101.196777f, 142.411865f}, {101.395020f, 142.295654f}, {101.583496f, 142.135254f},
        {101.721191f, 141.974365f}, {101.852539f, 141.830322f}, {101.978516f, 141.701904f}, {102.100098f, 141.587402f},
        {102.218262f, 141.485352f}, {102.334473f, 141.395020f}, {102.449219f, 141.314453f}, {102.562988f, 141.242676f},
        {102.677734f, 141.177734f}, {102.900879f, 141.081543f}, {103.110352f, 141.017578f}, {103.305664f, 140.986084f},
        {103.487305f, 140.987793f}, {103.656250f, 141.022949f}, {103.812500f, 141.092529f}, {103.956543f, 141.196777f},
        {104.088867f, 141.336426f}, {104.210449f, 141.511475f}, {104.327637f, 141.759277f}, {104.438477f, 141.995361f},
        {104.545898f, 142.219727f}, {104.651367f, 142.432129f}, {104.758301f, 142.633057f}, {104.867188f, 142.822021f},
        {104.981445f, 142.998779f}, {105.103027f, 143.163818f}, {105.233887f, 143.316406f}, {105.295410f, 143.354492f},
        {105.349121f, 143.385254f}, {105.395508f, 143.408936f}, {105.436035f, 143.427002f}, {105.471680f, 143.439453f},
        {105.502930f, 143.448242f}, {105.530762f, 143.453369f}, {105.556152f, 143.456299f}, {105.579590f, 143.457031f},
        {105.753906f, 143.456299f}, {105.928223f, 143.453613f}, {106.100586f, 143.450439f}, {106.272461f, 143.447266f},
        {106.442871f, 143.444824f}, {106.613281f, 143.443604f}, {106.782715f, 143.444336f}, {106.951660f, 143.447754f},
        {107.119629f, 143.454834f}, {107.390137f, 143.470947f}, {107.642578f, 143.472168f}, {107.876953f, 143.454590f},
        {108.093262f, 143.412842f}, {108.290039f, 143.342285f}, {108.468262f, 143.237793f}, {108.627930f, 143.094482f},
        {108.768066f, 142.908203f}, {108.888184f, 142.673584f}, {108.984375f, 142.406250f}, {109.090820f, 142.197998f},
        {109.204590f, 142.043945f}, {109.324707f, 141.939697f}, {109.449219f, 141.880615f}, {109.577637f, 141.862549f},
        {109.707031f, 141.880859f}, {109.836914f, 141.931152f}, {109.964844f, 142.008545f}, {110.202637f, 142.222168f},
        {110.430176f, 142.432861f}, {110.646973f, 142.644287f}, {110.851562f, 142.859619f}, {111.043457f, 143.081787f},
        {111.220215f, 143.313965f}, {111.381348f, 143.558838f}, {111.525391f, 143.820068f}, {111.651367f, 144.100830f},
        {111.779785f, 144.440186f}, {111.926758f, 144.721924f}, {112.089355f, 144.945312f}, {112.260742f, 145.110596f},
        {112.437988f, 145.216553f}, {112.616699f, 145.263428f}, {112.790527f, 145.250488f}, {112.956543f, 145.177246f},
        {113.109375f, 145.043945f}, {113.435059f, 144.544678f}, {113.745605f, 144.209961f}, {114.042969f, 144.017578f},
        {114.329102f, 143.945801f}, {114.604980f, 143.973145f}, {114.874023f, 144.077637f}, {115.138184f, 144.237305f},
        {115.398438f, 144.430420f}, {115.657227f, 144.635742f}, {116.341309f, 145.102783f}, {117.017578f, 145.523438f},
        {117.688965f, 145.892578f}, {118.357910f, 146.204102f}, {119.026855f, 146.453369f}, {119.699219f, 146.634033f},
        {120.377441f, 146.741211f}, {121.064453f, 146.769043f}, {121.763184f, 146.712402f}, {122.072754f, 146.643066f},
        {122.340820f, 146.586670f}, {122.571777f, 146.544922f}, {122.770020f, 146.519043f}, {122.939941f, 146.510498f},
        {123.086426f, 146.520020f}, {123.212402f, 146.550293f}, {123.323242f, 146.601318f}, {123.423340f, 146.675049f},
        {123.631348f, 146.894043f}, {123.839355f, 147.060059f}, {124.046387f, 147.177246f}, {124.254395f, 147.251709f},
        {124.461426f, 147.287354f}, {124.668945f, 147.289062f}, {124.875977f, 147.261475f}, {125.082520f, 147.209717f},
        {125.289551f, 147.138672f}, {125.808594f, 146.946533f}, {126.283203f, 146.844971f}, {126.714844f, 146.832031f},
        {127.104492f, 146.905518f}, {127.452637f, 147.063965f}, {127.759277f, 147.305176f}, {128.025391f, 147.626953f},
        {128.251953f, 148.028320f}, {128.439941f, 148.506592f}, {128.539062f, 148.896973f}, {128.642578f, 149.256104f},
        {128.749512f, 149.586426f}, {128.859863f, 149.890381f}, {128.974121f, 150.170410f}, {129.092285f, 150.428955f},
        {129.213379f, 150.668701f}, {129.338867f, 150.891846f}, {129.466797f, 151.101074f}, {129.644043f, 151.328125f},
        {129.801270f, 151.471924f}, {129.940430f, 151.542725f}, {130.062500f, 151.550537f}, {130.169434f, 151.504883f},
        {130.261719f, 151.416016f}, {130.341309f, 151.293701f}, {130.409668f, 151.148193f}, {130.468262f, 150.989258f},
        {130.600098f, 150.594971f}, {130.756348f, 150.254150f}, {130.936035f, 149.967529f}, {131.137207f, 149.734375f},
        {131.358398f, 149.555176f}, {131.599609f, 149.429443f}, {131.860352f, 149.357666f}, {132.137207f, 149.339600f},
        {132.431152f, 149.375488f}, {132.609863f, 149.440674f}, {132.760742f, 149.508789f}, {132.885742f, 149.581299f},
        {132.988770f, 149.657715f}, {133.070801f, 149.739258f}, {133.135254f, 149.826660f}, {133.184570f, 149.919922f},
        {133.220703f, 150.020020f}, {133.247070f, 150.127686f}, {133.306641f, 150.475098f}, {133.391602f, 150.790527f},
        {133.500488f, 151.075928f}, {133.631348f, 151.333008f}, {133.783203f, 151.563965f}, {133.954102f, 151.771484f},
        {134.143066f, 151.957031f}, {134.347168f, 152.122559f}, {134.566895f, 152.270508f}, {134.850586f, 152.430664f},
        {135.112305f, 152.596191f}, {135.354004f, 152.768066f}, {135.575684f, 152.948242f}, {135.776855f, 153.137695f},
        {135.958984f, 153.338623f}, {136.122559f, 153.551514f}, {136.268555f, 153.778564f}, {136.396484f, 154.020752f},
        {136.610352f, 154.508545f}, {136.850586f, 154.956055f}, {137.106934f, 155.371582f}, {137.372559f, 155.764893f},
        {137.639160f, 156.144775f}, {137.897461f, 156.520508f}, {138.140137f, 156.900635f}, {138.358887f, 157.294922f},
        {138.545410f, 157.712402f}, {138.626953f, 157.958008f}, {138.712402f, 158.161133f}, {138.801758f, 158.324707f},
        {138.895508f, 158.452148f}, {138.992676f, 158.546387f}, {139.092773f, 158.610840f}, {139.196777f, 158.648438f},
        {139.303223f, 158.662842f}, {139.412109f, 158.656738f}, {139.539551f, 158.615234f}, {139.647949f, 158.562744f},
        {139.737793f, 158.499756f}, {139.811035f, 158.427246f}, {139.870117f, 158.345703f}, {139.916504f, 158.256104f},
        {139.952148f, 158.158936f}, {139.978027f, 158.054688f}, {139.997070f, 157.944824f}, {140.010742f, 157.679688f},
        {140.009277f, 157.412598f}, {140.004883f, 157.153320f}, {140.013672f, 156.911133f}, {140.046875f, 156.695312f},
        {140.119629f, 156.515625f}, {140.245605f, 156.381348f}, {140.437988f, 156.301758f}, {140.709961f, 156.286621f},
        {140.934570f, 156.295166f}, {141.103027f, 156.226807f}, {141.220703f, 156.096924f}, {141.292480f, 155.919922f},
        {141.322266f, 155.711670f}, {141.315430f, 155.486572f}, {141.276367f, 155.260010f}, {141.210449f, 155.046631f},
        {141.121094f, 154.861816f}, {140.900879f, 154.619873f}, {140.701172f, 154.375244f}, {140.520020f, 154.128418f},
        {140.354492f, 153.879150f}, {140.202637f, 153.628906f}, {140.060547f, 153.377441f}, {139.927734f, 153.125488f},
        {139.799805f, 152.873535f}, {139.674805f, 152.621338f}, {139.412109f, 152.068848f}, {139.169922f, 151.522217f},
        {138.946777f, 150.980469f}, {138.739258f, 150.443604f}, {138.544922f, 149.910645f}, {138.361328f, 149.381104f},
        {138.186035f, 148.854492f}, {138.015625f, 148.329834f}, {137.848145f, 147.807129f}, {137.535156f, 146.837891f},
        {137.225098f, 145.895752f}, {136.910156f, 144.984131f}, {136.581055f, 144.106445f}, {136.231445f, 143.266602f},
        {135.851562f, 142.467529f}, {135.434570f, 141.713379f}, {134.970703f, 141.007324f}, {134.453613f, 140.353027f},
        {134.031738f, 139.956543f}, {133.632812f, 139.606445f}, {133.254395f, 139.296143f}, {132.895020f, 139.019775f},
        {132.552246f, 138.771973f}, {132.224121f, 138.546387f}, {131.908203f, 138.337158f}, {131.603516f, 138.138184f},
        {131.306641f, 137.944092f},
    };  // data size = 749

    Vec2 vertices15[] = {
        {270.807129f, 100.845703f}, {270.411621f, 101.252686f}, {270.030762f, 101.555420f}, {269.667480f, 101.755127f},
        {269.323730f, 101.851562f}, {269.000488f, 101.844971f}, {268.701172f, 101.736328f}, {268.426270f, 101.525635f},
        {268.178223f, 101.213135f}, {267.958984f, 100.799316f}, {267.861816f, 100.493652f}, {267.786133f, 100.220215f},
        {267.734375f, 99.977539f},  {267.707031f, 99.763672f},  {267.706055f, 99.576660f},  {267.733398f, 99.415039f},
        {267.789551f, 99.276367f},  {267.877441f, 99.159668f},  {267.997070f, 99.062500f},  {268.122070f, 99.015625f},
        {268.244141f, 98.981689f},  {268.361816f, 98.955566f},  {268.473145f, 98.931641f},  {268.574219f, 98.904785f},
        {268.663086f, 98.868896f},  {268.737305f, 98.818604f},  {268.793457f, 98.748535f},  {268.830078f, 98.653320f},
        {268.821289f, 98.497314f},  {268.787598f, 98.378662f},  {268.732910f, 98.291504f},  {268.663086f, 98.228271f},
        {268.581055f, 98.183350f},  {268.492188f, 98.149170f},  {268.401367f, 98.119629f},  {268.312500f, 98.088379f},
        {268.229980f, 98.047852f},  {268.179199f, 97.997803f},  {268.133789f, 97.948486f},  {268.093262f, 97.899658f},
        {268.056641f, 97.851807f},  {268.022949f, 97.804688f},  {267.992676f, 97.758301f},  {267.963867f, 97.713135f},
        {267.937012f, 97.668945f},  {267.910156f, 97.625732f},  {267.891602f, 97.597900f},  {267.874512f, 97.572021f},
        {267.858887f, 97.547852f},  {267.844727f, 97.525635f},  {267.831055f, 97.505127f},  {267.818359f, 97.485840f},
        {267.806152f, 97.467285f},  {267.794434f, 97.449463f},  {267.783203f, 97.431885f},  {267.471680f, 97.219238f},
        {267.159668f, 97.008057f},  {266.848145f, 96.799561f},  {266.534668f, 96.595703f},  {266.220215f, 96.397217f},
        {265.903320f, 96.205566f},  {265.583496f, 96.022461f},  {265.261230f, 95.848877f},  {264.934570f, 95.686035f},
        {264.530762f, 95.529785f},  {264.172852f, 95.432617f},  {263.857910f, 95.393799f},  {263.582031f, 95.412109f},
        {263.343750f, 95.487061f},  {263.140137f, 95.616943f},  {262.968750f, 95.801514f},  {262.825684f, 96.039062f},
        {262.708984f, 96.329346f},  {262.838379f, 96.550537f},  {262.981445f, 96.688232f},  {263.135254f, 96.761963f},
        {263.299316f, 96.790527f},  {263.470703f, 96.792725f},  {263.647949f, 96.788086f},  {263.829590f, 96.795654f},
        {264.012695f, 96.834717f},  {264.196289f, 96.923584f},  {264.038086f, 97.048096f},  {263.876465f, 97.132812f},
        {263.713379f, 97.181396f},  {263.548828f, 97.197754f},  {263.381836f, 97.185059f},  {263.214355f, 97.147705f},
        {263.044922f, 97.089600f},  {262.875488f, 97.014160f},  {262.705566f, 96.925049f},  {262.076660f, 96.800293f},
        {261.458496f, 96.738281f},  {260.848633f, 96.726074f},  {260.248047f, 96.752686f},  {259.653320f, 96.804199f},
        {259.063965f, 96.869629f},  {258.478516f, 96.936035f},  {257.895020f, 96.990967f},  {257.313477f, 97.022949f},
        {257.017578f, 97.028564f},  {256.769043f, 97.060303f},  {256.563965f, 97.116211f},  {256.399414f, 97.194580f},
        {256.271973f, 97.293457f},  {256.177246f, 97.411621f},  {256.112305f, 97.546143f},  {256.073242f, 97.696289f},
        {256.056152f, 97.859619f},  {256.058594f, 98.102051f},  {256.040527f, 98.321777f},  {256.003906f, 98.520996f},
        {255.950684f, 98.700439f},  {255.880859f, 98.862305f},  {255.797363f, 99.007568f},  {255.700195f, 99.138184f},
        {255.590332f, 99.255371f},  {255.471191f, 99.361084f},  {255.254395f, 99.486572f},  {255.047363f, 99.559082f},
        {254.855469f, 99.582275f},  {254.681152f, 99.560059f},  {254.529297f, 99.495117f},  {254.404785f, 99.391602f},
        {254.310547f, 99.252197f},  {254.250977f, 99.080566f},  {254.229980f, 98.880615f},  {254.294434f, 98.411133f},
        {254.306152f, 98.014404f},  {254.268066f, 97.683594f},  {254.184082f, 97.412109f},  {254.058105f, 97.192627f},
        {253.892578f, 97.018555f},  {253.692383f, 96.883545f},  {253.459961f, 96.780029f},  {253.198730f, 96.701904f},
        {252.817383f, 96.615479f},  {252.457031f, 96.507568f},  {252.113281f, 96.386475f},  {251.782715f, 96.259766f},
        {251.461914f, 96.135010f},  {251.147461f, 96.020508f},  {250.834961f, 95.923584f},  {250.521484f, 95.852295f},
        {250.203613f, 95.814209f},  {249.769043f, 95.838867f},  {249.354980f, 95.859863f},  {248.957520f, 95.882324f},
        {248.576660f, 95.913330f},  {248.208984f, 95.958496f},  {247.854492f, 96.022949f},  {247.509766f, 96.113770f},
        {247.174805f, 96.236084f},  {246.846680f, 96.395752f},  {246.544434f, 96.589844f},  {246.252441f, 96.753662f},
        {245.968750f, 96.889404f},  {245.693359f, 96.998779f},  {245.423340f, 97.083984f},  {245.159668f, 97.146973f},
        {244.899414f, 97.189453f},  {244.643066f, 97.213623f},  {244.388672f, 97.221191f},  {244.197266f, 97.213623f},
        {244.019531f, 97.208252f},  {243.853516f, 97.207764f},  {243.699219f, 97.213135f},  {243.554688f, 97.227051f},
        {243.418457f, 97.250244f},  {243.290527f, 97.284912f},  {243.168945f, 97.333008f},  {243.052734f, 97.395752f},
        {243.033203f, 97.711670f},  {243.071289f, 98.028564f},  {243.161621f, 98.339111f},  {243.297363f, 98.637207f},
        {243.473633f, 98.915771f},  {243.685059f, 99.168457f},  {243.925781f, 99.388428f},  {244.189941f, 99.569092f},
        {244.472656f, 99.703857f},  {244.772461f, 99.762695f},  {245.058105f, 99.809570f},  {245.329590f, 99.843262f},
        {245.587891f, 99.860840f},  {245.834961f, 99.860352f},  {246.072266f, 99.840088f},  {246.299805f, 99.797852f},
        {246.520020f, 99.731201f},  {246.732910f, 99.638916f},  {246.959961f, 99.504883f},  {247.163086f, 99.409668f},
        {247.344238f, 99.353027f},  {247.504395f, 99.335938f},  {247.645508f, 99.357422f},  {247.769531f, 99.417969f},
        {247.878418f, 99.517578f},  {247.973145f, 99.656006f},  {248.055664f, 99.833984f},  {248.120605f, 100.032471f},
        {248.189941f, 100.211914f}, {248.264160f, 100.373779f}, {248.343262f, 100.519043f}, {248.428223f, 100.648438f},
        {248.519043f, 100.763672f}, {248.615234f, 100.864746f}, {248.718262f, 100.953369f}, {248.827637f, 101.030273f},
        {249.285156f, 101.130371f}, {249.736816f, 101.198730f}, {250.183594f, 101.240967f}, {250.625977f, 101.262451f},
        {251.063965f, 101.268799f}, {251.499023f, 101.264893f}, {251.931152f, 101.256592f}, {252.361328f, 101.249268f},
        {252.790039f, 101.248291f}, {253.127441f, 101.235596f}, {253.442871f, 101.227051f}, {253.737305f, 101.221924f},
        {254.013184f, 101.219971f}, {254.274414f, 101.220215f}, {254.522461f, 101.222412f}, {254.760742f, 101.225586f},
        {254.990723f, 101.229736f}, {255.215820f, 101.233887f}, {255.486816f, 101.240234f}, {255.745605f, 101.244385f},
        {255.993652f, 101.245850f}, {256.232422f, 101.245850f}, {256.462402f, 101.244141f}, {256.687012f, 101.241211f},
        {256.904785f, 101.237549f}, {257.119629f, 101.233154f}, {257.331543f, 101.229004f}, {257.561035f, 101.207520f},
        {257.779297f, 101.184814f}, {257.987305f, 101.162354f}, {258.186523f, 101.141113f}, {258.378418f, 101.123047f},
        {258.564453f, 101.109619f}, {258.745117f, 101.102539f}, {258.923340f, 101.103516f}, {259.098145f, 101.113770f},
        {259.195801f, 101.118896f}, {259.283691f, 101.120850f}, {259.362793f, 101.119385f}, {259.434570f, 101.114990f},
        {259.499512f, 101.107422f}, {259.558594f, 101.097412f}, {259.613770f, 101.084229f}, {259.664551f, 101.068604f},
        {259.713867f, 101.050537f}, {260.023926f, 100.843750f}, {260.301270f, 100.597168f}, {260.552246f, 100.318604f},
        {260.785645f, 100.014160f}, {261.008301f, 99.691162f},  {261.229004f, 99.355957f},  {261.453613f, 99.015137f},
        {261.691406f, 98.676514f},  {261.948730f, 98.345947f},  {262.029785f, 98.580078f},  {262.093750f, 98.821533f},
        {262.145508f, 99.068604f},  {262.188965f, 99.319824f},  {262.230469f, 99.573486f},  {262.273438f, 99.828369f},
        {262.322754f, 100.082764f}, {262.383789f, 100.335693f}, {262.460449f, 100.585449f}, {262.504883f, 100.686523f},
        {262.544922f, 100.773438f}, {262.581055f, 100.847656f}, {262.613770f, 100.910645f}, {262.644043f, 100.964111f},
        {262.672363f, 101.009521f}, {262.698730f, 101.048096f}, {262.724121f, 101.081543f}, {262.749512f, 101.111328f},
        {262.874512f, 101.212646f}, {263.001953f, 101.295410f}, {263.130859f, 101.360596f},

        {263.261719f, 101.410156f}, {263.394043f, 101.445312f}, {263.526855f, 101.467529f}, {263.660156f, 101.479004f},
        {263.793457f, 101.480469f}, {263.926758f, 101.474121f}, {264.416992f, 101.445557f}, {264.885254f, 101.471680f},
        {265.333496f, 101.547119f}, {265.763672f, 101.666748f}, {266.179688f, 101.825439f}, {266.582520f, 102.017822f},
        {266.974609f, 102.238525f}, {267.357910f, 102.482666f}, {267.734863f, 102.744629f}, {268.783203f, 103.019775f},
        {269.081055f, 103.170654f}, {269.346680f, 103.233154f}, {269.583984f, 103.218506f}, {269.796875f, 103.138672f},
        {269.990234f, 103.005127f}, {270.167480f, 102.829102f}, {270.333984f, 102.622070f}, {270.493164f, 102.396240f},
        {270.649902f, 102.162354f}, {270.734863f, 101.991455f}, {270.806152f, 101.832764f}, {270.863770f, 101.685059f},
        {270.906250f, 101.547119f}, {270.932617f, 101.417725f}, {270.942383f, 101.294922f}, {270.936035f, 101.177734f},
        {270.911621f, 101.064697f}, {270.869141f, 100.954346f},
    };  // data size = 317

    Vec2 vertices16[] = {
        {293.019043f, 98.785156f},  {293.019043f, 99.872314f},  {293.061035f, 99.809326f},  {293.102539f, 99.746338f},
        {293.143066f, 99.682617f},  {293.183594f, 99.619141f},  {293.225098f, 99.555664f},  {293.266602f, 99.492432f},
        {293.308594f, 99.429932f},  {293.351074f, 99.368652f},  {293.394531f, 99.307861f},  {293.534180f, 99.137451f},
        {293.665039f, 99.000732f},  {293.787598f, 98.899902f},  {293.902832f, 98.839111f},  {294.010742f, 98.821045f},
        {294.111816f, 98.848389f},  {294.206543f, 98.925537f},  {294.294922f, 99.054932f},  {294.377930f, 99.239746f},
        {294.452148f, 99.509277f},  {294.520996f, 99.766357f},  {294.586426f, 100.011963f}, {294.650391f, 100.247314f},
        {294.713867f, 100.472900f}, {294.779297f, 100.689453f}, {294.849609f, 100.898438f}, {294.925781f, 101.100586f},
        {295.010254f, 101.296387f}, {295.177246f, 101.609619f}, {295.341309f, 101.897217f}, {295.506836f, 102.153320f},
        {295.677734f, 102.372803f}, {295.857910f, 102.550537f}, {296.052734f, 102.680908f}, {296.265625f, 102.758789f},
        {296.500977f, 102.778564f}, {296.763672f, 102.735596f}, {296.941895f, 102.665283f}, {297.109375f, 102.610596f},
        {297.267578f, 102.572021f}, {297.416992f, 102.549316f}, {297.557617f, 102.541992f}, {297.690430f, 102.550781f},
        {297.815430f, 102.574951f}, {297.933105f, 102.614258f}, {298.043945f, 102.668945f}, {298.339355f, 102.865723f},
        {298.582031f, 102.971191f}, {298.777832f, 102.995605f}, {298.932129f, 102.949951f}, {299.051270f, 102.845215f},
        {299.139648f, 102.691650f}, {299.203613f, 102.500732f}, {299.249023f, 102.282959f}, {299.281738f, 102.048828f},
        {299.342285f, 101.556396f}, {299.418457f, 101.153809f}, {299.512695f, 100.838867f}, {299.627930f, 100.609619f},
        {299.767578f, 100.463623f}, {299.934570f, 100.399170f}, {300.131836f, 100.413574f}, {300.362305f, 100.505371f},
        {300.628906f, 100.671875f}, {301.179688f, 101.110107f}, {301.720703f, 101.499268f}, {302.256348f, 101.840088f},
        {302.787598f, 102.132568f}, {303.318848f, 102.377197f}, {303.851562f, 102.574219f}, {304.388672f, 102.724121f},
        {304.932617f, 102.827148f}, {305.487305f, 102.883301f}, {305.882324f, 102.887695f}, {306.247559f, 102.906494f},
        {306.585449f, 102.942383f}, {306.896973f, 102.996826f}, {307.184082f, 103.072266f}, {307.449707f, 103.170410f},
        {307.694824f, 103.293213f}, {307.921875f, 103.442871f}, {308.133301f, 103.621582f}, {308.360840f, 103.849854f},
        {308.585449f, 104.013428f}, {308.806641f, 104.122314f}, {309.024902f, 104.186768f}, {309.239258f, 104.217285f},
        {309.450195f, 104.223877f}, {309.657715f, 104.217285f}, {309.861816f, 104.207275f}, {310.061523f, 104.204346f},
        {310.390625f, 104.228516f}, {310.713379f, 104.226807f}, {311.027832f, 104.215088f}, {311.333496f, 104.207764f},
        {311.627930f, 104.220947f}, {311.909668f, 104.269287f}, {312.177734f, 104.368164f}, {312.429688f, 104.532715f},
        {312.665527f, 104.778320f}, {312.801758f, 104.979736f}, {312.951172f, 105.137207f}, {313.109375f, 105.253662f},
        {313.272461f, 105.331055f}, {313.436035f, 105.372559f}, {313.596191f, 105.379883f}, {313.748535f, 105.355713f},
        {313.890625f, 105.303223f}, {314.016602f, 105.224121f}, {314.330078f, 104.892334f}, {314.644531f, 104.619873f},
        {314.961914f, 104.404785f}, {315.282715f, 104.242432f}, {315.607422f, 104.131104f}, {315.936035f, 104.066895f},
        {316.269531f, 104.047119f}, {316.609375f, 104.068115f}, {316.955566f, 104.127197f}, {316.958008f, 103.923584f},
        {316.942871f, 103.713623f}, {316.912109f, 103.498291f}, {316.865723f, 103.279053f}, {316.806152f, 103.057373f},
        {316.734375f, 102.833740f}, {316.651855f, 102.610107f}, {316.559082f, 102.387695f}, {316.457520f, 102.167480f},
        {316.281738f, 101.879395f}, {316.088379f, 101.652344f}, {315.878906f, 101.485107f}, {315.654297f, 101.375488f},
        {315.416016f, 101.322754f}, {315.165039f, 101.324707f}, {314.903320f, 101.380371f}, {314.631836f, 101.487793f},
        {314.352051f, 101.645752f}, {314.183594f, 101.778076f}, {314.033203f, 101.905029f}, {313.898926f, 102.026123f},
        {313.779297f, 102.142090f}, {313.670410f, 102.253662f}, {313.572266f, 102.361084f}, {313.481934f, 102.464600f},
        {313.395996f, 102.565186f}, {313.314941f, 102.662354f}, {313.191406f, 102.796387f}, {313.071777f, 102.904297f},
        {312.954590f, 102.987549f}, {312.838867f, 103.046875f}, {312.724121f, 103.083496f}, {312.607910f, 103.098389f},
        {312.490234f, 103.092041f}, {312.370117f, 103.065918f}, {312.246094f, 103.020996f}, {311.592285f, 102.683105f},
        {310.939453f, 102.377686f}, {310.287598f, 102.105957f}, {309.634766f, 101.868652f}, {308.980469f, 101.666992f},
        {308.323242f, 101.501953f}, {307.662598f, 101.374512f}, {306.997559f, 101.285645f}, {306.326660f, 101.236084f},
        {305.755859f, 101.225098f}, {305.228027f, 101.185303f}, {304.738770f, 101.118164f}, {304.283691f, 101.024414f},
        {303.858887f, 100.906494f}, {303.459473f, 100.765381f}, {303.081055f, 100.602295f}, {302.720215f, 100.418945f},
        {302.371582f, 100.216309f}, {302.095215f, 100.023926f}, {301.836914f, 99.831055f},  {301.595215f, 99.642578f},
        {301.367188f, 99.463135f},  {301.150879f, 99.297607f},  {300.945312f, 99.150391f},  {300.746582f, 99.026611f},
        {300.554199f, 98.931152f},  {300.365723f, 98.868408f},  {300.029297f, 98.856934f},  {299.706055f, 98.849854f},
        {299.394531f, 98.842773f},  {299.092285f, 98.831299f},  {298.798340f, 98.810059f},  {298.511719f, 98.775146f},
        {298.229004f, 98.721436f},  {297.950195f, 98.644775f},  {297.672852f, 98.540039f},  {297.522461f, 98.489258f},
        {297.395020f, 98.500732f},  {297.288086f, 98.564453f},  {297.198730f, 98.669922f},  {297.124023f, 98.808105f},
        {297.062500f, 98.967773f},  {297.010742f, 99.139404f},  {296.965820f, 99.313232f},  {296.925781f, 99.478760f},
        {296.884277f, 99.648438f},  {296.850586f, 99.814209f},  {296.819336f, 99.973145f},  {296.788086f, 100.122070f},
        {296.750000f, 100.257812f}, {296.701660f, 100.377930f}, {296.639160f, 100.478516f}, {296.557129f, 100.556885f},
        {296.451660f, 100.610107f}, {296.278809f, 100.610352f}, {296.129395f, 100.580811f}, {296.000488f, 100.525635f},
        {295.889160f, 100.448242f}, {295.792480f, 100.352295f}, {295.708008f, 100.242188f}, {295.632812f, 100.120850f},
        {295.564941f, 99.992676f},  {295.499512f, 99.861328f},  {295.413086f, 99.657227f},  {295.353027f, 99.453369f},
        {295.311523f, 99.250488f},  {295.282227f, 99.049805f},  {295.257812f, 98.852295f},  {295.231934f, 98.658691f},
        {295.196777f, 98.471191f},  {295.146484f, 98.289795f},  {295.072754f, 98.116211f},  {294.965332f, 97.957764f},
        {294.866699f, 97.802979f},  {294.774902f, 97.655518f},  {294.686523f, 97.517090f},  {294.598145f, 97.391113f},
        {294.507812f, 97.280273f},  {294.412109f, 97.187012f},  {294.307617f, 97.114502f},  {294.192383f, 97.064941f},
        {294.006348f, 97.065918f},  {293.855469f, 97.103271f},  {293.734375f, 97.171143f},  {293.638672f, 97.264404f},
        {293.562500f, 97.377686f},  {293.502441f, 97.505371f},  {293.453125f, 97.642334f},  {293.408203f, 97.782959f},
        {293.364746f, 97.922119f},  {293.321777f, 98.030762f},  {293.281250f, 98.132568f},  {293.243652f, 98.227783f},
        {293.208008f, 98.317627f},  {293.174316f, 98.402588f},  {293.141602f, 98.483643f},  {293.109863f, 98.561523f},
        {293.079590f, 98.636963f},  {293.049316f, 98.710938f},
    };  // data size = 254

    Vec2 vertices17[] = {
        {223.400391f, 126.521484f}, {223.342773f, 126.621338f}, {223.286621f, 126.723145f}, {223.231445f, 126.825684f},
        {223.175781f, 126.928467f}, {223.120117f, 127.030762f}, {223.062500f, 127.131104f}, {223.003418f, 127.229004f},
        {222.941406f, 127.323486f}, {222.876953f, 127.413330f}, {222.699219f, 127.607910f}, {222.523926f, 127.777832f},
        {222.348633f, 127.917969f}, {222.172852f, 128.024902f}, {221.995605f, 128.093506f}, {221.815918f, 128.119141f},
        {221.632324f, 128.098145f}, {221.443848f, 128.024902f}, {221.250000f, 127.895996f}, {220.995117f, 127.633301f},
        {220.745605f, 127.390869f}, {220.500488f, 127.168457f}, {220.256836f, 126.966797f}, {220.013672f, 126.786133f},
        {219.769043f, 126.627197f}, {219.520508f, 126.489990f}, {219.266602f, 126.375244f}, {219.005371f, 126.283447f},
        {218.822754f, 126.235840f}, {218.659668f, 126.178711f}, {218.516113f, 126.111084f}, {218.395020f, 126.032227f},
        {218.295898f, 125.940430f}, {218.220703f, 125.834717f}, {218.169922f, 125.714600f}, {218.145996f, 125.578125f},
        {218.148926f, 125.425049f}, {218.183594f, 125.224365f}, {218.191406f, 125.045166f}, {218.175293f, 124.885742f},
        {218.139160f, 124.741943f}, {218.088379f, 124.611816f}, {218.027344f, 124.492188f}, {217.958984f, 124.380127f},
        {217.888672f, 124.272705f}, {217.821289f, 124.167480f}, {217.697754f, 123.962646f}, {217.581543f, 123.818115f},
        {217.472656f, 123.728271f}, {217.370605f, 123.688965f}, {217.275391f, 123.695312f}, {217.186035f, 123.741943f},
        {217.104492f, 123.824707f}, {217.030273f, 123.938721f}, {216.961914f, 124.078613f}, {216.820801f, 124.431396f},
        {216.653809f, 124.745361f}, {216.463379f, 125.018311f}, {216.253418f, 125.247559f}, {216.025391f, 125.431396f},
        {215.782227f, 125.566406f}, {215.526367f, 125.651123f}, {215.260742f, 125.682861f}, {214.987793f, 125.659424f},
        {214.679688f, 125.553223f}, {214.382812f, 125.461670f}, {214.097168f, 125.379639f}, {213.823242f, 125.300781f},
        {213.561035f, 125.218994f}, {213.309570f, 125.128906f}, {213.069824f, 125.023926f}, {212.841309f, 124.898926f},
        {212.624023f, 124.747314f}, {212.469727f, 124.610596f}, {212.325195f, 124.506104f}, {212.188477f, 124.431641f},
        {212.060059f, 124.385986f}, {211.937012f, 124.366699f}, {211.820801f, 124.372070f}, {211.708008f, 124.399658f},
        {211.599609f, 124.447998f}, {211.494141f, 124.515137f}, {211.367188f, 124.624756f}, {211.245117f, 124.729492f},
        {211.127441f, 124.829102f}, {211.013672f, 124.924072f}, {210.902832f, 125.015137f}, {210.794434f, 125.102051f},
        {210.687500f, 125.185547f}, {210.582031f, 125.265869f}, {210.477051f, 125.343262f}, {210.331055f, 125.451416f},
        {210.218262f, 125.551270f}, {210.136719f, 125.644775f}, {210.085449f, 125.733398f}, {210.063965f, 125.819336f},
        {210.071289f, 125.904297f}, {210.105957f, 125.989746f}, {210.167480f, 126.077637f}, {210.254883f, 126.169434f},
        {210.538086f, 126.434326f}, {210.759277f, 126.708496f}, {210.919922f, 126.989746f}, {211.020996f, 127.275879f},
        {211.062988f, 127.564453f}, {211.047363f, 127.853760f}, {210.975586f, 128.141357f}, {210.848633f, 128.425293f},
        {210.667480f, 128.703369f}, {210.485352f, 128.876465f}, {210.317871f, 128.997803f}, {210.163574f, 129.073730f},
        {210.021484f, 129.110840f}, {209.891602f, 129.115234f}, {209.773926f, 129.093262f}, {209.666504f, 129.051758f},
        {209.570801f, 128.996826f}, {209.483887f, 128.934814f}, {209.298340f, 128.785400f}, {209.113281f, 128.643555f},
        {208.929199f, 128.506104f}, {208.750000f, 128.368652f}, {208.576660f, 128.227783f}, {208.411621f, 128.079346f},
        {208.257812f, 127.919922f}, {208.116699f, 127.745361f}, {207.990234f, 127.551758f}, {207.724121f, 127.170166f},
        {207.453613f, 126.865723f}, {207.179688f, 126.638184f}, {206.903809f, 126.486328f}, {206.626953f, 126.410156f},
        {206.350098f, 126.409424f}, {206.073730f, 126.482910f}, {205.798828f, 126.630127f}, {205.526855f, 126.850830f},
        {205.196777f, 127.208984f}, {204.875488f, 127.481445f}, {204.562500f, 127.677246f}, {204.255859f, 127.804443f},
        {203.954590f, 127.871826f}, {203.657715f, 127.887695f}, {203.363281f, 127.860596f}, {203.070801f, 127.799316f},
        {202.777832f, 127.711914f}, {202.577637f, 127.452393f}, {202.393555f, 127.261230f}, {202.221191f, 127.133545f},
        {202.060547f, 127.063232f}, {201.907227f, 127.044678f}, {201.760254f, 127.072510f}, {201.616699f, 127.140869f},
        {201.474609f, 127.244141f}, {201.331543f, 127.376465f}, {200.978516f, 127.736816f}, {200.632324f, 128.030273f},
        {200.291504f, 128.258057f}, {199.955566f, 128.422607f}, {199.623535f, 128.524414f}, {199.293945f, 128.565430f},
        {198.966797f, 128.547119f}, {198.640137f, 128.470947f}, {198.312988f, 128.338623f}, {198.085449f, 128.178955f},
        {197.880371f, 128.024902f}, {197.694336f, 127.875244f}, {197.524902f, 127.728760f}, {197.371582f, 127.583984f},
        {197.230469f, 127.440186f}, {197.100586f, 127.295898f}, {196.979004f, 127.149902f}, {196.863770f, 127.000732f},
        {196.706543f, 126.793945f}, {196.548340f, 126.615967f}, {196.389648f, 126.472168f}, {196.229980f, 126.366699f},
        {196.070312f, 126.303955f}, {195.911621f, 126.288818f}, {195.753418f, 126.325195f}, {195.596191f, 126.418213f},
        {195.440918f, 126.572021f}, {195.316406f, 126.697510f}, {195.202637f, 126.815918f}, {195.096191f, 126.926758f},
        {194.996582f, 127.027344f}, {194.900391f, 127.115967f}, {194.807129f, 127.191162f}, {194.713379f, 127.250732f},
        {194.618164f, 127.293213f}, {194.518555f, 127.317139f}, {194.069824f, 127.313477f}, {193.638184f, 127.356689f},
        {193.222168f, 127.440918f}, {192.819824f, 127.560303f}, {192.427734f, 127.709229f}, {192.045410f, 127.881592f},
        {191.670410f, 128.072266f}, {191.299316f, 128.274902f}, {190.931641f, 128.484131f}, {189.889160f, 128.693604f},
        {189.820312f, 128.848633f}, {189.740234f, 128.971924f}, {189.650391f, 129.066895f}, {189.551758f, 129.137207f},
        {189.444824f, 129.186279f}, {189.332520f, 129.217529f}, {189.214844f, 129.234863f}, {189.092773f, 129.241455f},
        {188.969727f, 129.241211f}, {188.797363f, 129.238525f}, {188.634766f, 129.244629f}, {188.481934f, 129.260986f},
        {188.337402f, 129.289062f}, {188.201660f, 129.330078f}, {188.074219f, 129.385742f}, {187.954102f, 129.457275f},
        {187.842285f, 129.545898f}, {187.737793f, 129.653564f}, {188.032227f, 129.972656f}, {188.378418f, 130.240967f},
        {188.764160f, 130.456299f}, {189.177734f, 130.615479f}, {189.608398f, 130.715576f}, {190.043457f, 130.754150f},
        {190.471191f, 130.728027f}, {190.880371f, 130.634521f}, {191.258789f, 130.470703f}, {191.708008f, 130.126953f},
        {192.154297f, 129.848877f}, {192.595703f, 129.622803f}, {193.029297f, 129.436035f}, {193.456055f, 129.275391f},
        {193.873047f, 129.127197f}, {194.279785f, 128.978760f}, {194.674316f, 128.816895f}, {195.055664f, 128.628418f},
        {195.220215f, 128.527588f}, {195.364746f, 128.452393f}, {195.492188f, 128.400635f}, {195.603027f, 128.370117f},
        {195.700684f, 128.358887f}, {195.785645f, 128.364990f}, {195.860840f, 128.385986f}, {195.927246f, 128.419678f},
        {195.988281f, 128.464844f}, {196.159180f, 128.633301f}, {196.333984f, 128.786621f}, {196.511230f, 128.928467f},
        {196.688965f, 129.062500f}, {196.866699f, 129.192627f}, {197.041992f, 129.322021f}, {197.214355f, 129.454590f},
        {197.381348f, 129.593506f}, {197.542480f, 129.743164f}, {197.859863f, 130.065430f}, {198.183594f, 130.320557f},
        {198.511719f, 130.510010f}, {198.840332f, 130.633545f}, {199.169434f, 130.692627f}, {199.494629f, 130.687744f},
        {199.815430f, 130.619873f}, {200.129395f, 130.489258f}, {200.433105f, 130.296875f}, {200.769531f, 129.980713f},
        {201.090332f, 129.699463f}, {201.400391f, 129.457764f}, {201.703125f, 129.261230f}, {202.000977f, 129.114502f},
        {202.298828f, 129.023193f}, {202.600098f, 128.992188f}, {202.908691f, 129.026367f}, {203.228027f, 129.131592f},
        {203.459961f, 129.251953f}, {203.672852f, 129.326416f}, {203.869141f, 129.361328f}, {204.051270f, 129.363281f},
        {204.220215f, 129.338135f}, {204.379395f, 129.292725f}, {204.529297f, 129.233154f}, {204.673340f, 129.165527f},
        {204.812988f, 129.096680f}, {205.032227f, 128.982178f}, {205.238770f, 128.845459f}, {205.435547f, 128.697021f},
        {205.625488f, 128.547119f}, {205.811523f, 128.407227f}, {205.995605f, 128.286621f}, {206.181641f, 128.196777f},
        {206.372559f, 128.147949f}, {206.569336f, 128.150635f}, {206.915527f, 128.303223f}, {207.250000f, 128.455322f},
        {207.573730f, 128.610840f}, {207.884277f, 128.774658f}, {208.181152f, 128.950439f}, {208.462891f, 129.142090f},
        {208.729004f, 129.354004f}, {208.979004f, 129.590332f}, {209.210449f, 129.855225f}, {209.295410f, 129.979004f},
        {209.368652f, 130.087402f}, {209.430176f, 130.181885f}, {209.482910f, 130.264160f}, {209.527344f, 130.336182f},
        {209.565430f, 130.399414f}, {209.598145f, 130.455322f}, {209.627441f, 130.505859f}, {209.653809f, 130.552979f},
        {209.661133f, 130.696289f}, {209.672852f, 130.832275f}, {209.690430f, 130.958740f}, {209.717285f, 131.073975f},
        {209.755859f, 131.174561f}, {209.808105f, 131.259277f}, {209.877441f, 131.325195f}, {209.965820f, 131.370361f},
        {210.076660f, 131.392090f}, {210.228027f, 131.368652f}, {210.356445f, 131.329346f}, {210.464355f, 131.275391f},
        {210.553223f, 131.207275f}, {210.625488f, 131.126465f}, {210.683105f, 131.033203f}, {210.728516f, 130.928711f},
        {210.762207f, 130.813477f}, {210.787598f, 130.688965f}, {210.829102f, 130.357422f}, {210.877441f, 130.035156f},
        {210.932129f, 129.722412f}, {210.995117f, 129.418457f}, {211.067871f, 129.124023f}, {211.151855f, 128.838379f},
        {211.248535f, 128.562500f}, {211.358887f, 128.294922f}, {211.484863f, 128.036621f}, {211.687500f, 127.726562f},
        {211.874512f, 127.486816f}, {212.047852f, 127.315186f}, {212.209961f, 127.210693f}, {212.361328f, 127.171631f},
        {212.504883f, 127.196045f}, {212.641602f, 127.282715f}, {212.772949f, 127.429932f}, {212.900879f, 127.635742f},
        {212.970703f, 127.790039f}, {213.034180f, 127.930664f}, {213.090332f, 128.059082f}, {213.141113f, 128.176025f},
        {213.187988f, 128.283691f}, {213.230957f, 128.383057f}, {213.271484f, 128.475586f}, {213.310547f, 128.563232f},
        {213.349609f, 128.646729f}, {213.636719f, 129.184570f}, {213.920410f, 129.613281f}, {214.204590f, 129.934570f},
        {214.492676f, 130.148926f}, {214.789062f, 130.257080f}, {215.096680f, 130.260742f}, {215.421387f, 130.160645f},
        {215.764648f, 129.957764f}, {216.131348f, 129.652832f}, {216.369629f, 129.394287f}, {216.583496f, 129.154541f},
        {216.776855f, 128.932129f}, {216.953125f, 128.725098f}, {217.114258f, 128.532471f}, {217.264160f, 128.352051f},
        {217.405273f, 128.182373f}, {217.540527f, 128.021729f}, {217.672852f, 127.868408f}, {217.922852f, 127.611572f},
        {218.150391f, 127.412354f}, {218.358887f, 127.271240f}, {218.551758f, 127.187012f}, {218.731934f, 127.160400f},
        {218.902832f, 127.190918f}, {219.068359f, 127.277832f}, {219.230957f, 127.421631f}, {219.393555f, 127.621826f},
        {219.656250f, 128.000977f}, {219.932617f, 128.308350f}, {220.220215f, 128.556152f}, {220.516113f, 128.755615f},
        {220.815918f, 128.918945f}, {221.118164f, 129.058350f}, {221.418457f, 129.185059f}, {221.713379f, 129.312012f},
        {222.000488f, 129.450439f}, {222.375488f, 129.197021f}, {222.729980f, 129.057617f}, {223.066895f, 129.013916f},
        {223.388672f, 129.044922f}, {223.698242f, 129.131592f}, {223.999023f, 129.254395f}, {224.292969f, 129.393311f},
        {224.582520f, 129.528564f}, {224.872070f, 129.641113f}, {225.327148f, 129.716553f}, {225.774414f, 129.786865f},
        {226.210449f, 129.841553f}, {226.635254f, 129.869141f}, {227.046875f, 129.858154f}, {227.444336f, 129.797852f},
        {227.826660f, 129.677002f}, {228.191895f, 129.484375f}, {228.538574f, 129.209229f}, {228.661621f, 129.072754f},
        {228.774902f, 128.961914f}, {228.879395f, 128.874512f}, {228.975586f, 128.808350f}, {229.062500f, 128.760498f},
        {229.143066f, 128.728271f}, {229.215820f, 128.709717f}, {229.282227f, 128.701660f}, {229.342773f, 128.701660f},
        {229.582520f, 128.719971f}, {229.804199f, 128.707031f}, {230.009277f, 128.663574f}, {230.197266f, 128.591309f},
        {230.370605f, 128.491211f}, {230.530273f, 128.363770f}, {230.676758f, 128.210693f}, {230.810547f, 128.033203f},
        {230.933105f, 127.832031f}, {230.970703f, 127.654053f}, {230.993652f, 127.490479f}, {231.003418f, 127.339844f},
        {231.001953f, 127.200684f}, {230.990234f, 127.071533f}, {230.969238f, 126.950684f}, {230.940918f, 126.836670f},
        {230.905762f, 126.728271f}, {230.865723f, 126.623779f}, {230.146484f, 126.521484f}, {230.042969f, 126.355469f},
        {229.971680f, 126.197021f}, {229.931152f, 126.045654f}, {229.919434f, 125.901611f}, {229.935059f, 125.763916f},
        {229.976562f, 125.632568f}, {230.042480f, 125.507080f}, {230.130859f, 125.386963f}, {230.241211f, 125.271973f},
        {230.343750f, 125.187988f}, {230.439453f, 125.109619f}, {230.529297f, 125.036621f}, {230.612793f, 124.968262f},
        {230.692383f, 124.903809f}, {230.768066f, 124.842773f}, {230.840332f, 124.784424f}, {230.910156f, 124.727783f},
        {230.978516f, 124.672852f}, {231.024414f, 124.613525f}, {231.062012f, 124.555908f}, {231.090332f, 124.499512f},
        {231.112793f, 124.443848f}, {231.128906f, 124.388916f}, {231.139648f, 124.334961f}, {231.146973f, 124.281250f},
        {231.151367f, 124.228027f}, {231.153809f, 124.174805f}, {231.161133f, 123.981445f}, {231.174805f, 123.790039f},
        {231.197266f, 123.603516f}, {231.229492f, 123.424561f}, {231.272949f, 123.256348f}, {231.331055f, 123.101807f},
        {231.405273f, 122.963135f}, {231.497070f, 122.843750f}, {231.608398f, 122.746094f}, {231.797852f, 122.683838f},
        {231.966797f, 122.669189f}, {232.118164f, 122.696289f}, {232.253418f, 122.758301f}, {232.374512f, 122.849365f},
        {232.484375f, 122.964111f}, {232.583984f, 123.095459f}, {232.676270f, 123.237549f}, {232.762695f, 123.384766f},
        {232.881348f, 123.642090f}, {233.010254f, 123.855225f}, {233.149902f, 124.027344f}, {233.298828f, 124.163330f},
        {233.455078f, 124.266357f}, {233.619629f, 124.341064f}, {233.790527f, 124.390869f}, {233.967285f, 124.420166f},
        {234.149414f, 124.432861f}, {234.480469f, 124.427734f}, {234.800293f, 124.429443f}, {235.110352f, 124.439209f},
        {235.411133f, 124.458984f}, {235.704102f, 124.490479f}, {235.990234f, 124.534912f}, {236.270020f, 124.594727f},
        {236.546387f, 124.670654f}, {236.817871f, 124.765137f}, {237.019043f, 124.856201f}, {237.203125f, 124.942627f},
        {237.370117f, 125.026611f}, {237.521484f, 125.111816f}, {237.657715f, 125.200928f}, {237.778809f, 125.296387f},
        {237.886719f, 125.401367f}, {237.981445f, 125.518799f}, {238.063477f, 125.651367f}, {238.214355f, 125.974609f},
        {238.366699f, 126.219971f}, {238.520996f, 126.393066f}, {238.678223f, 126.498535f}, {238.838379f, 126.542236f},
        {239.001953f, 126.529297f}, {239.170410f, 126.464844f}, {239.345215f, 126.354492f}, {239.525391f, 126.203613f},
        {239.890137f, 125.843750f}, {240.216309f, 125.577881f}, {240.505371f, 125.405762f}, {240.762207f, 125.326904f},
        {240.989258f, 125.340332f}, {241.190918f, 125.445801f}, {241.369629f, 125.642822f}, {241.529785f, 125.930664f},
        {241.673828f, 126.308594f}, {241.741211f, 126.560791f}, {241.804688f, 126.791992f}, {241.865723f, 127.000000f},
        {241.926758f, 127.183350f}, {241.988770f, 127.340088f}, {242.054199f, 127.468262f}, {242.123535f, 127.566406f},
        {242.200195f, 127.632568f}, {242.284180f, 127.664551f}, {242.622559f, 127.623535f}, {242.952148f, 127.631836f},
        {243.273926f, 127.676514f}, {243.590332f, 127.743652f}, {243.902344f, 127.820312f}, {244.210449f, 127.893066f},
        {244.517578f, 127.948486f}, {244.823730f, 127.973877f}, {245.131348f, 127.955078f}, {245.237793f, 127.907227f},
        {245.327148f, 127.863525f}, {245.401855f, 127.823730f}, {245.463867f, 127.786865f}, {245.514160f, 127.752686f},
        {245.556152f, 127.721191f}, {245.589844f, 127.691162f}, {245.618164f, 127.662598f}, {245.642578f, 127.634766f},
        {245.635254f, 127.467285f}, {245.610840f, 127.314697f}, {245.569824f, 127.177002f}, {245.515137f, 127.052246f},
        {245.448242f, 126.939697f}, {245.370117f, 126.837891f}, {245.282227f, 126.745605f}, {245.186035f, 126.662109f},
        {245.083008f, 126.585938f}, {244.934570f, 126.482910f}, {244.817871f, 126.377686f}, {244.730957f, 126.270508f},
        {244.670898f, 126.160645f}, {244.636230f, 126.047852f}, {244.624023f, 125.931885f}, {244.633301f, 125.812744f},
        {244.661133f, 125.689941f}, {244.706055f, 125.563232f}, {244.360352f, 125.707031f}, {244.034668f, 125.765137f},
        {243.726074f, 125.748291f}, {243.432129f, 125.666504f}, {243.150879f, 125.530762f}, {242.878906f, 125.350830f},
        {242.613281f, 125.137451f}, {242.352051f, 124.900635f}, {242.092773f, 124.650635f}, {241.902344f, 124.478760f},
        {241.717773f, 124.332031f}, {241.538086f, 124.210693f}, {241.364258f, 124.114258f}, {241.196777f, 124.042236f},
        {241.034668f, 123.994385f}, {240.879395f, 123.970703f}, {240.730469f, 123.970703f}, {240.588379f, 123.993896f},
        {240.099121f, 124.154785f}, {239.636230f, 124.211670f}, {239.195801f, 124.181641f}, {238.773926f, 124.083252f},
        {238.366211f, 123.934082f}, {237.968750f, 123.751709f}, {237.577637f, 123.553711f}, {237.187988f, 123.358398f},
        {236.796875f, 123.182617f}, {236.535156f, 123.094238f}, {236.294434f, 123.025879f}, {236.071777f, 122.975586f},
        {235.865723f, 122.940430f}, {235.673340f, 122.918457f}, {235.492188f, 122.907227f}, {235.320801f, 122.904297f},
        {235.156250f, 122.907715f}, {234.996582f, 122.915039f}, {234.572266f, 122.927246f}, {234.206543f, 122.912109f},
        {233.891602f, 122.864990f}, {233.620117f, 122.781006f}, {233.384766f, 122.654541f}, {233.178223f, 122.481934f},
        {232.992676f, 122.256836f}, {232.821289f, 121.975342f}, {232.655273f, 121.632324f}, {232.564453f, 121.395752f},
        {232.484863f, 121.180908f}, {232.411133f, 120.988037f}, {232.341309f, 120.819092f}, {232.269531f, 120.674561f},
        {232.192383f, 120.555908f}, {232.106934f, 120.464355f}, {232.008301f, 120.400391f}, {231.893066f, 120.365723f},
        {231.731445f, 120.384033f}, {231.587402f, 120.420898f}, {231.458984f, 120.474854f}, {231.345703f, 120.544434f},
        {231.247559f, 120.627930f}, {231.164062f, 120.723633f}, {231.093262f, 120.830078f}, {231.035156f, 120.945801f},
        {230.990234f, 121.069092f}, {230.812012f, 121.717285f}, {230.582031f, 122.318848f}, {230.311523f, 122.884033f},
        {230.013184f, 123.422363f}, {229.698242f, 123.943848f}, {229.378418f, 124.458740f}, {229.065430f, 124.976562f},
        {228.771484f, 125.507568f}, {228.507324f, 126.061523f}, {228.243164f, 126.623779f}, {227.885254f, 127.066162f},
        {227.456543f, 127.393799f}, {226.978516f, 127.610107f}, {226.474121f, 127.720703f}, {225.964355f, 127.729492f},
        {225.471191f, 127.641357f}, {225.017090f, 127.460693f}, {224.624023f, 127.191650f}, {224.461914f, 126.981445f},
        {224.317383f, 126.799072f}, {224.187012f, 126.645752f}, {224.067871f, 126.523682f}, {223.956055f, 126.433838f},
        {223.848633f, 126.377441f}, {223.742188f, 126.356445f}, {223.634277f, 126.372314f}, {223.521484f, 126.426514f},
    };  // data size = 660

    Vec2 vertices18[] = {
        {286.350586f, 146.418457f}, {286.858887f, 146.610596f}, {287.375488f, 146.721436f}, {287.898438f, 146.771484f},
        {288.425293f, 146.782471f}, {288.954590f, 146.775391f}, {289.483398f, 146.770752f}, {290.009766f, 146.790283f},
        {290.531250f, 146.854492f}, {291.046875f, 146.984863f}, {291.488281f, 147.177979f}, {291.958984f, 147.337891f},
        {292.449219f, 147.464844f}, {292.947266f, 147.560791f}, {293.443359f, 147.625244f}, {293.927246f, 147.660156f},
        {294.387695f, 147.665039f}, {294.813965f, 147.641357f}, {295.196289f, 147.590088f}, {295.456055f, 147.517334f},
        {295.697754f, 147.455566f}, {295.922852f, 147.404541f}, {296.134277f, 147.366455f}, {296.334473f, 147.341797f},
        {296.526855f, 147.331543f}, {296.712891f, 147.336914f}, {296.895996f, 147.359131f}, {297.078125f, 147.398926f},
        {297.482422f, 147.520508f}, {297.875488f, 147.593018f}, {298.258301f, 147.621094f}, {298.632324f, 147.608887f},
        {298.996582f, 147.561279f}, {299.353516f, 147.483398f}, {299.703613f, 147.378906f}, {300.047363f, 147.253174f},
        {300.386230f, 147.110107f}, {300.641602f, 146.992920f}, {300.879883f, 146.892578f}, {301.101562f, 146.810303f},
        {301.309082f, 146.746094f}, {301.504395f, 146.700684f}, {301.688477f, 146.674561f}, {301.864258f, 146.668213f},
        {302.032227f, 146.681641f}, {302.194824f, 146.715820f}, {302.486816f, 146.820557f}, {302.747559f, 146.882080f},
        {302.979004f, 146.900146f}, {303.183105f, 146.874756f}, {303.362305f, 146.805908f}, {303.518555f, 146.692871f},
        {303.653809f, 146.535889f}, {303.770996f, 146.334229f}, {303.872070f, 146.087891f}, {303.935059f, 145.873291f},
        {304.002441f, 145.677490f}, {304.072266f, 145.498047f}, {304.144531f, 145.333496f}, {304.218262f, 145.180420f},
        {304.291504f, 145.037354f}, {304.363770f, 144.901611f}, {304.435059f, 144.770996f}, {304.503418f, 144.643311f},
        {304.231445f, 144.902832f}, {303.945312f, 145.123047f}, {303.646973f, 145.304443f}, {303.335938f, 145.448975f},
        {303.013184f, 145.557861f}, {302.679688f, 145.632812f}, {302.336426f, 145.674561f}, {301.983398f, 145.685303f},
        {301.622559f, 145.665771f}, {301.409180f, 145.644287f}, {301.218750f, 145.644531f}, {301.047852f, 145.663818f},
        {300.895996f, 145.698242f}, {300.759277f, 145.745605f}, {300.635254f, 145.802734f}, {300.521484f, 145.865967f},
        {300.415527f, 145.932861f}, {300.314453f, 146.000000f}, {299.940430f, 146.219727f}, {299.569336f, 146.400146f},
        {299.202637f, 146.540039f}, {298.838379f, 146.637451f}, {298.476074f, 146.691162f}, {298.115723f, 146.699707f},
        {297.756836f, 146.661621f}, {297.398438f, 146.575195f}, {297.041016f, 146.438965f}, {296.816406f, 146.319580f},
        {296.620117f, 146.231934f}, {296.449219f, 146.174561f}, {296.298340f, 146.145508f}, {296.164551f, 146.143311f},
        {296.043945f, 146.166016f}, {295.932617f, 146.211670f}, {295.826660f, 146.279297f}, {295.722168f, 146.366699f},
        {295.311523f, 146.777588f}, {294.950684f, 147.101074f}, {294.626953f, 147.340332f}, {294.326660f, 147.498535f},
        {294.037598f, 147.577637f}, {293.745605f, 147.581787f}, {293.438477f, 147.512451f}, {293.104004f, 147.374023f},
        {292.728027f, 147.168213f}, {292.444336f, 146.985840f}, {292.184082f, 146.818115f}, {291.942871f, 146.663818f},
        {291.719238f, 146.522949f}, {291.510254f, 146.394531f}, {291.312500f, 146.277832f}, {291.124023f, 146.172119f},
        {290.941406f, 146.076904f}, {290.762695f, 145.991455f},

        {290.475098f, 145.872559f}, {290.195801f, 145.761230f}, {289.924805f, 145.666016f}, {289.661133f, 145.596924f},
        {289.406250f, 145.562988f}, {289.159668f, 145.573730f}, {288.920898f, 145.637939f}, {288.689941f, 145.765625f},
        {288.466797f, 145.966064f}, {288.345703f, 146.122070f}, {288.229004f, 146.241455f}, {288.116211f, 146.326660f},
        {288.008301f, 146.379395f}, {287.904785f, 146.402832f}, {287.807129f, 146.397949f}, {287.714844f, 146.367920f},
        {287.628906f, 146.314453f}, {287.548828f, 146.239990f}, {287.329590f, 146.043457f}, {287.106934f, 145.878174f},
        {286.880859f, 145.740967f}, {286.652344f, 145.628662f}, {286.422363f, 145.538330f}, {286.190430f, 145.467041f},
        {285.958008f, 145.411865f}, {285.724121f, 145.369385f}, {285.491699f, 145.336914f}, {285.147949f, 145.286621f},
        {284.834961f, 145.209961f}, {284.552246f, 145.107178f}, {284.297363f, 144.977783f}, {284.068359f, 144.821777f},
        {283.863281f, 144.638916f}, {283.681641f, 144.428711f}, {283.520020f, 144.191650f}, {283.377441f, 143.927246f},
        {283.228516f, 143.564697f}, {283.078125f, 143.235107f}, {282.921875f, 142.940430f}, {282.757812f, 142.682861f},
        {282.582520f, 142.463867f}, {282.391113f, 142.285156f}, {282.181641f, 142.149170f}, {281.950195f, 142.057861f},
        {281.694336f, 142.012695f}, {281.321289f, 142.063965f}, {280.991211f, 142.156006f}, {280.700684f, 142.285645f},
        {280.445801f, 142.449219f}, {280.223145f, 142.644043f}, {280.027832f, 142.866943f}, {279.857422f, 143.114746f},
        {279.706543f, 143.383789f}, {279.571777f, 143.671631f}, {279.499512f, 143.865967f}, {279.437988f, 144.045654f},
        {279.385742f, 144.212646f}, {279.342285f, 144.367920f}, {279.304199f, 144.513428f}, {279.271973f, 144.650146f},
        {279.242676f, 144.780029f}, {279.215332f, 144.904053f}, {279.188477f, 145.024414f}, {279.055176f, 145.523926f},
        {278.927246f, 145.931152f}, {278.794922f, 146.252441f}, {278.650391f, 146.495117f}, {278.484375f, 146.665527f},
        {278.289062f, 146.771240f}, {278.054199f, 146.818848f}, {277.771484f, 146.815186f}, {277.433594f, 146.767578f},
        {277.200684f, 146.715332f}, {276.986328f, 146.667969f}, {276.790039f, 146.626709f}, {276.611328f, 146.593262f},
        {276.446289f, 146.569824f}, {276.296387f, 146.557373f}, {276.159180f, 146.558350f}, {276.033203f, 146.573730f},
        {275.917969f, 146.605957f}, {275.535645f, 146.792969f}, {275.168457f, 146.912354f}, {274.814941f, 146.969971f},
        {274.473633f, 146.972168f}, {274.141113f, 146.925049f}, {273.817383f, 146.834961f}, {273.500000f, 146.708496f},
        {273.187500f, 146.551514f}, {272.877930f, 146.370361f}, {272.645996f, 146.229736f}, {272.430664f, 146.122559f},
        {272.229980f, 146.046143f}, {272.041016f, 145.996826f}, {271.862305f, 145.972900f}, {271.691895f, 145.970215f},
        {271.527832f, 145.987305f}, {271.368164f, 146.020020f}, {271.210938f, 146.065918f}, {270.833984f, 146.193604f},
        {270.474609f, 146.279053f}, {270.131348f, 146.320068f}, {269.804688f, 146.313721f}, {269.494629f, 146.257324f},
        {269.199707f, 146.147705f}, {268.920898f, 145.981934f}, {268.656250f, 145.757812f}, {268.406738f, 145.472412f},
        {268.243652f, 145.216309f}, {268.086426f, 144.985107f}, {267.932617f, 144.782959f}, {267.779785f, 144.615723f},
        {267.626465f, 144.487549f}, {267.469727f, 144.404053f}, {267.308594f, 144.369873f}, {267.139648f, 144.390381f},
        {266.961914f, 144.470215f}, {266.886719f, 144.543213f}, {266.824219f, 144.609863f}, {266.771973f, 144.670410f},
        {266.729492f, 144.726074f}, {266.696289f, 144.777832f}, {266.669434f, 144.825684f}, {266.649414f, 144.871582f},
        {266.634766f, 144.915527f}, {266.623047f, 144.958984f}, {266.618164f, 145.039062f}, {266.616699f, 145.115234f},
        {266.620117f, 145.187988f}, {266.628418f, 145.256836f}, {266.641113f, 145.322266f}, {266.658203f, 145.384521f},
        {266.681152f, 145.443604f}, {266.709473f, 145.499512f}, {266.743164f, 145.552979f}, {266.884766f, 145.483154f},
        {267.016113f, 145.435547f}, {267.137695f, 145.411377f}, {267.247559f, 145.412109f}, {267.347656f, 145.439209f},
        {267.437012f, 145.495117f}, {267.515625f, 145.580566f}, {267.583984f, 145.697266f}, {267.641602f, 145.847168f},
        {267.687988f, 146.040771f}, {267.737793f, 146.220215f}, {267.792480f, 146.386719f}, {267.851074f, 146.541748f},
        {267.913574f, 146.686035f}, {267.980469f, 146.821533f}, {268.051758f, 146.949219f}, {268.126953f, 147.070557f},
        {268.207031f, 147.186768f}, {268.355469f, 147.387695f}, {268.495117f, 147.589844f}, {268.627441f, 147.791016f},
        {268.755371f, 147.988281f}, {268.881348f, 148.180420f}, {269.006348f, 148.364014f}, {269.133789f, 148.537354f},
        {269.265137f, 148.697754f}, {269.403320f, 148.843018f}, {269.633301f, 148.986328f}, {269.834961f, 149.037598f},
        {270.014648f, 149.013916f}, {270.176758f, 148.932373f}, {270.325195f, 148.810059f}, {270.467285f, 148.664062f},
        {270.605957f, 148.510986f}, {270.747070f, 148.368408f}, {270.896484f, 148.252930f}, {271.119141f, 148.196289f},
        {271.326172f, 148.162598f}, {271.519043f, 148.153076f}, {271.697266f, 148.168457f}, {271.860840f, 148.208984f},
        {272.011230f, 148.276367f}, {272.148438f, 148.370605f}, {272.272949f, 148.493164f}, {272.384766f, 148.644775f},
        {272.474609f, 148.814697f}, {272.562988f, 148.965576f}, {272.650391f, 149.099365f}, {272.738281f, 149.217041f},
        {272.827148f, 149.320557f}, {272.917480f, 149.411865f}, {273.009766f, 149.491943f}, {273.104492f, 149.562500f},
        {273.202637f, 149.625732f}, {273.296875f, 149.644287f}, {273.386230f, 149.658447f}, {273.470215f, 149.671143f},
        {273.549316f, 149.684326f}, {273.623047f, 149.700684f}, {273.691406f, 149.722900f}, {273.754395f, 149.753662f},
        {273.812500f, 149.795654f}, {273.863770f, 149.851318f}, {274.098633f, 150.251709f}, {274.333496f, 150.590332f},
        {274.572754f, 150.868408f}, {274.821289f, 151.087158f}, {275.082031f, 151.248047f}, {275.360352f, 151.352295f},
        {275.660156f, 151.401367f}, {275.985352f, 151.396484f}, {276.340820f, 151.338867f}, {276.742676f, 151.212402f},
        {277.122559f, 151.086670f}, {277.475586f, 150.952148f}, {277.797363f, 150.798340f}, {278.084473f, 150.616211f},
        {278.330566f, 150.395752f}, {278.532715f, 150.126953f}, {278.685547f, 149.801025f}, {278.784180f, 149.407227f},
        {278.807617f, 149.168701f}, {278.848145f, 148.955322f}, {278.901855f, 148.764404f}, {278.967285f, 148.593750f},
        {279.041504f, 148.440430f}, {279.120605f, 148.302002f}, {279.202637f, 148.176025f}, {279.285156f, 148.060059f},
        {279.365234f, 147.951660f}, {279.584961f, 147.635498f}, {279.798828f, 147.323975f}, {280.004395f, 147.014893f},
        {280.199707f, 146.704590f}, {280.382812f, 146.390869f}, {280.550293f, 146.070801f}, {280.701172f, 145.741211f},
        {280.833496f, 145.399902f}, {280.943359f, 145.043945f}, {280.993652f, 144.815674f}, {281.044434f, 144.605225f},
        {281.099121f, 144.414062f}, {281.158691f, 144.243896f}, {281.225586f, 144.096680f}, {281.301270f, 143.973877f},
        {281.387695f, 143.877441f}, {281.487793f, 143.809082f}, {281.603027f, 143.770752f}, {281.752441f, 143.790771f},
        {281.864258f, 143.835693f}, {281.943848f, 143.901611f}, {281.998047f, 143.983887f}, {282.031250f, 144.079590f},
        {282.049805f, 144.183838f}, {282.059570f, 144.292969f}, {282.064941f, 144.403564f}, {282.073730f, 144.510986f},
        {282.183594f, 144.874023f}, {282.334473f, 145.206299f}, {282.521973f, 145.505371f}, {282.741699f, 145.768799f},
        {282.988281f, 145.993408f}, {283.256836f, 146.177246f}, {283.541992f, 146.317139f}, {283.838867f, 146.411133f},
        {284.143066f, 146.456055f}, {284.414551f, 146.437500f}, {284.670410f, 146.424561f}, {284.911621f, 146.416992f},
        {285.140625f, 146.413330f}, {285.358887f, 146.412842f}, {285.567383f, 146.414551f}, {285.769531f, 146.416748f},
        {285.965820f, 146.419434f}, {286.158203f, 146.421143f},
    };  // data size = 388

    Vec2 vertices19[] = {
        {267.111816f, 128.220947f}, {267.300293f, 128.100342f}, {267.468750f, 128.042969f}, {267.618652f, 128.041016f},
        {267.752930f, 128.085205f}, {267.873535f, 128.167480f}, {267.983398f, 128.279053f}, {268.084961f, 128.412109f},
        {268.181152f, 128.557617f}, {268.273438f, 128.707031f}, {268.544922f, 129.094727f}, {268.821289f, 129.429688f},
        {269.104004f, 129.710449f}, {269.392578f, 129.934814f}, {269.687500f, 130.100586f}, {269.990234f, 130.206055f},
        {270.300293f, 130.248535f}, {270.617676f, 130.226562f}, {270.944336f, 130.138184f}, {271.354004f, 129.946533f},
        {271.727051f, 129.832031f}, {272.067383f, 129.785645f}, {272.379883f, 129.798096f}, {272.667969f, 129.861328f},
        {272.936035f, 129.965576f}, {273.188477f, 130.102295f}, {273.430176f, 130.262451f}, {273.665039f, 130.437256f},
        {273.875488f, 130.595703f}, {274.067383f, 130.728027f}, {274.242676f, 130.833008f}, {274.405762f, 130.909912f},
        {274.559570f, 130.957275f}, {274.707031f, 130.974609f}, {274.852051f, 130.959961f}, {274.996094f, 130.912842f},
        {275.144043f, 130.832031f}, {275.398926f, 130.645264f}, {275.652344f, 130.505127f}, {275.903809f, 130.407227f},
        {276.152344f, 130.346924f}, {276.397461f, 130.319824f}, {276.639160f, 130.321533f}, {276.876953f, 130.347412f},
        {277.109863f, 130.393066f}, {277.338379f, 130.453857f}, {277.734863f, 130.576172f}, {278.084473f, 130.652344f},
        {278.390137f, 130.679199f}, {278.656250f, 130.653809f}, {278.888184f, 130.573242f}, {279.088867f, 130.434814f},
        {279.264160f, 130.234863f}, {279.417480f, 129.971191f}, {279.552734f, 129.640381f}, {279.623535f, 129.376953f},
        {279.680664f, 129.132324f}, {279.727051f, 128.905029f}, {279.766113f, 128.693604f}, {279.800293f, 128.496338f},
        {279.830566f, 128.311523f}, {279.860840f, 128.137939f}, {279.894531f, 127.973877f}, {279.931641f, 127.817383f},
        {280.042480f, 127.500732f}, {280.159668f, 127.201172f}, {280.285156f, 126.921387f}, {280.423340f, 126.664551f},
        {280.577148f, 126.433105f}, {280.749023f, 126.231201f}, {280.941895f, 126.060303f}, {281.158691f, 125.924561f},
        {281.402832f, 125.826660f}, {281.688965f, 125.796387f}, {281.946777f, 125.794434f}, {282.178223f, 125.820801f},
        {282.384766f, 125.876221f}, {282.567383f, 125.960449f}, {282.727539f, 126.074707f}, {282.867188f, 126.218750f},
        {282.987305f, 126.393311f}, {283.089844f, 126.598389f}, {283.248047f, 127.059326f}, {283.418457f, 127.476562f},
        {283.604980f, 127.848877f}, {283.810059f, 128.175049f}, {284.037109f, 128.453125f}, {284.290039f, 128.682373f},
        {284.571777f, 128.861328f}, {284.885254f, 128.988525f}, {285.234863f, 129.062988f}, {285.557129f, 129.074463f},
        {285.859375f, 129.102295f}, {286.142090f, 129.143799f}, {286.409668f, 129.196533f}, {286.663574f, 129.257080f},
        {286.904785f, 129.323242f}, {287.137695f, 129.391113f}, {287.362793f, 129.458252f}, {287.583984f, 129.521973f},
        {287.629883f, 129.392822f}, {287.645508f, 129.282227f}, {287.634766f, 129.187256f}, {287.601074f, 129.105713f},
        {287.548828f, 129.035889f}, {287.481934f, 128.975098f}, {287.403320f, 128.921143f}, {287.317871f, 128.871582f},
        {287.227539f, 128.824463f}, {287.058105f, 128.728760f}, {286.900391f, 128.630859f}, {286.754395f, 128.528320f},
        {286.621582f, 128.418701f}, {286.501465f, 128.298828f}, {286.395508f, 128.167236f}, {286.303223f, 128.020996f},
        {286.226562f, 127.858154f}, {286.164551f, 127.675537f}, {286.125000f, 127.490234f}, {286.079102f, 127.317871f},
        {286.024902f, 127.160156f}, {285.962891f, 127.019043f}, {285.892090f, 126.895508f}, {285.811035f, 126.791992f},
        {285.718750f, 126.709473f}, {285.614746f, 126.650146f}, {285.498047f, 126.615479f}, {284.967285f, 126.585205f},
        {284.483398f, 126.469238f}, {284.039551f, 126.280029f}, {283.630371f, 126.030273f}, {283.248535f, 125.732422f},
        {282.888184f, 125.399414f}, {282.541992f, 125.043457f}, {282.203613f, 124.677979f}, {281.866699f, 124.315186f},
        {281.667969f, 124.115723f}, {281.492188f, 123.936035f}, {281.334473f, 123.777100f}, {281.190918f, 123.639893f},
        {281.057617f, 123.525391f}, {280.930176f, 123.434326f}, {280.804688f, 123.368164f}, {280.676758f, 123.327148f},
        {280.542480f, 123.312012f}, {280.426758f, 123.324707f}, {280.317383f, 123.332275f}, {280.213867f, 123.338623f},
        {280.118652f, 123.347412f}, {280.032227f, 123.363281f}, {279.954590f, 123.389893f}, {279.887207f, 123.431152f},
        {279.831543f, 123.491455f}, {279.787598f, 123.574463f}, {279.767578f, 123.691895f}, {279.761230f, 123.798340f},
        {279.768066f, 123.895020f}, {279.785156f, 123.982422f}, {279.813477f, 124.061279f}, {279.850098f, 124.131836f},
        {279.894531f, 124.194580f}, {279.944824f, 124.250977f}, {280.000488f, 124.300781f}, {280.243164f, 124.489014f},
        {280.407227f, 124.664062f}, {280.501465f, 124.827637f}, {280.534180f, 124.981201f}, {280.514648f, 125.126221f},
        {280.450684f, 125.264160f}, {280.351562f, 125.396484f}, {280.226074f, 125.524658f}, {280.082520f, 125.649902f},
        {279.716797f, 126.025146f}, {279.349121f, 126.354004f}, {278.977539f, 126.636963f}, {278.600586f, 126.874023f},
        {278.217773f, 127.065430f}, {277.826660f, 127.210938f}, {277.426270f, 127.310547f}, {277.015625f, 127.364746f},
        {276.593262f, 127.373291f}, {276.263184f, 127.339844f}, {275.957520f, 127.321777f}, {275.674316f, 127.321045f},
        {275.413086f, 127.341797f}, {275.172363f, 127.386230f}, {274.949219f, 127.457520f}, {274.744141f, 127.558105f},
        {274.553711f, 127.691650f}, {274.378418f, 127.860596f}, {274.193848f, 128.088623f}, {274.016602f, 128.249023f},
        {273.845703f, 128.349609f}, {273.681641f, 128.398193f}, {273.523438f, 128.401855f}, {273.372070f, 128.368408f},
        {273.227051f, 128.305420f}, {273.086914f, 128.220215f}, {272.953125f, 128.121094f}, {272.681152f, 127.905762f},
        {272.417480f, 127.732666f}, {272.160645f, 127.601562f}, {271.909668f, 127.513672f}, {271.662598f, 127.469482f},
        {271.419434f, 127.469727f}, {271.178223f, 127.514893f}, {270.937988f, 127.605469f}, {270.696777f, 127.742676f},
        {270.467285f, 127.915039f}, {270.258789f, 128.038574f}, {270.070312f, 128.115234f}, {269.899902f, 128.146729f},
        {269.746582f, 128.135254f}, {269.609375f, 128.082275f}, {269.486816f, 127.990234f}, {269.377930f, 127.860107f},
        {269.280762f, 127.694824f}, {269.189941f, 127.480469f}, {269.094727f, 127.286621f}, {268.996094f, 127.110596f},
        {268.894531f, 126.948975f}, {268.792480f, 126.799316f}, {268.689941f, 126.658447f}, {268.588379f, 126.523193f},
        {268.489746f, 126.391602f}, {268.394043f, 126.259521f}, {268.292969f, 126.109619f}, {268.195312f, 125.976074f},
        {268.099609f, 125.859375f}, {268.004395f, 125.760742f}, {267.907715f, 125.680908f}, {267.809570f, 125.620605f},
        {267.707520f, 125.581055f}, {267.600098f, 125.562744f}, {267.486328f, 125.566406f}, {267.329102f, 125.625977f},
        {267.201660f, 125.702148f}, {267.100586f, 125.793701f}, {267.022461f, 125.898193f}, {266.963867f, 126.012939f},
        {266.920410f, 126.136230f}, {266.889160f, 126.265625f}, {266.865723f, 126.398682f}, {266.847656f, 126.533447f},
        {266.836914f, 126.623047f}, {266.828613f, 126.706055f}, {266.821777f, 126.782471f}, {266.817383f, 126.853516f},
        {266.814453f, 126.919922f}, {266.812500f, 126.982422f}, {266.811523f, 127.041504f}, {266.811523f, 127.098389f},
        {266.812012f, 127.153809f}, {266.818359f, 127.279785f}, {266.826172f, 127.402344f}, {266.836914f, 127.521484f},
        {266.851074f, 127.636230f}, {266.871582f, 127.746338f}, {266.899414f, 127.852051f}, {266.935547f, 127.952637f},
        {266.981445f, 128.047852f}, {267.039062f, 128.137451f},
    };  // data size = 262

    Vec2 vertices20[] = {
        {85.934570f, 74.998779f},  {85.704102f, 75.262207f},  {85.478516f, 75.527344f},  {85.261719f, 75.798584f},
        {85.056641f, 76.078369f},  {84.866211f, 76.370850f},  {84.694336f, 76.679443f},  {84.544922f, 77.007080f},
        {84.419434f, 77.357666f},  {84.323242f, 77.734131f},  {84.270996f, 78.128418f},  {84.215820f, 78.501709f},
        {84.154297f, 78.854492f},  {84.082031f, 79.185791f},  {83.996094f, 79.495605f},  {83.892578f, 79.783203f},
        {83.768555f, 80.048828f},  {83.620117f, 80.291504f},  {83.443359f, 80.510986f},  {83.174805f, 80.693359f},
        {82.946289f, 80.885498f},  {82.755371f, 81.087646f},  {82.600098f, 81.300049f},  {82.476562f, 81.522217f},
        {82.382324f, 81.754639f},  {82.314941f, 81.997070f},  {82.270020f, 82.250000f},  {82.246582f, 82.513184f},
        {81.956055f, 83.330566f},  {81.659668f, 84.128662f},  {81.352539f, 84.903320f},  {81.027344f, 85.650635f},
        {80.677246f, 86.365967f},  {80.295410f, 87.045654f},  {79.875977f, 87.685303f},  {79.411621f, 88.281006f},
        {78.895996f, 88.828613f},  {78.703613f, 88.993164f},  {78.543457f, 89.132812f},  {78.412109f, 89.251221f},
        {78.306152f, 89.349854f},  {78.221191f, 89.432129f},  {78.153320f, 89.500488f},  {78.100586f, 89.557373f},
        {78.057617f, 89.605713f},  {78.021484f, 89.647705f},  {77.692383f, 90.062500f},  {77.449219f, 90.440430f},
        {77.291016f, 90.785889f},  {77.219727f, 91.102783f},  {77.235352f, 91.394775f},  {77.338867f, 91.665283f},
        {77.530762f, 91.918701f},  {77.812012f, 92.158691f},  {78.182617f, 92.389404f},  {78.306152f, 92.582764f},
        {78.385254f, 92.744141f},  {78.426758f, 92.877197f},  {78.434082f, 92.985840f},  {78.414551f, 93.073975f},
        {78.372070f, 93.144775f},  {78.312988f, 93.202881f},  {78.242676f, 93.251221f},  {78.166504f, 93.293945f},
        {77.684082f, 93.596924f},  {77.256348f, 93.937988f},  {76.880859f, 94.316895f},  {76.554688f, 94.731934f},
        {76.276367f, 95.181885f},  {76.041504f, 95.665771f},  {75.849609f, 96.181641f},  {75.696289f, 96.729004f},
        {75.579102f, 97.306152f},  {75.522949f, 97.805176f},  {75.470215f, 98.272217f},  {75.412598f, 98.705566f},
        {75.343750f, 99.104492f},  {75.255859f, 99.468018f},  {75.141113f, 99.794922f},  {74.992188f, 100.084229f},
        {74.801270f, 100.334961f}, {74.560547f, 100.545410f}, {74.460449f, 100.602051f}, {74.375488f, 100.651855f},
        {74.305176f, 100.696289f}, {74.248535f, 100.735107f}, {74.203125f, 100.770020f}, {74.168945f, 100.801025f},
        {74.143066f, 100.828857f}, {74.125000f, 100.854492f}, {74.113770f, 100.878662f}, {73.986328f, 101.395752f},
        {73.812988f, 101.872070f}, {73.601074f, 102.314209f}, {73.359863f, 102.729980f}, {73.097168f, 103.126221f},
        {72.820312f, 103.509766f}, {72.538574f, 103.888428f}, {72.259766f, 104.268311f}, {71.992188f, 104.657227f},
        {71.772949f, 105.084961f}, {71.610352f, 105.507568f}, {71.498535f, 105.925293f}, {71.430176f, 106.336670f},
        {71.399902f, 106.741699f}, {71.399902f, 107.138916f}, {71.424316f, 107.527588f}, {71.466797f, 107.907227f},
        {71.520996f, 108.276855f}, {71.574219f, 108.645264f}, {71.603027f, 108.966064f}, {71.606934f, 109.244385f},
        {71.583984f, 109.484375f}, {71.534180f, 109.691650f}, {71.456055f, 109.870605f}, {71.348633f, 110.025635f},
        {71.211426f, 110.162109f}, {71.042969f, 110.284424f}, {70.624023f, 110.516113f}, {70.289551f, 110.739990f},
        {70.038574f, 110.962158f}, {69.867676f, 111.187744f}, {69.775391f, 111.423340f}, {69.759277f, 111.674561f},
        {69.816406f, 111.947266f}, {69.945312f, 112.246826f}, {70.142578f, 112.579590f}, {70.326660f, 112.836182f},
        {70.478516f, 113.067627f}, {70.597168f, 113.277344f}, {70.681641f, 113.467773f}, {70.729492f, 113.641602f},
        {70.739258f, 113.802002f}, {70.709473f, 113.951904f}, {70.638672f, 114.093994f}, {70.524414f, 114.230713f},
        {70.441895f, 114.295898f}, {70.365723f, 114.354248f}, {70.295898f, 114.406494f}, {70.233887f, 114.454102f},
        {70.179199f, 114.498047f}, {70.131836f, 114.539551f}, {70.092285f, 114.579834f}, {70.061523f, 114.619873f},
        {70.038574f, 114.660889f}, {69.812988f, 115.433350f}, {69.497070f, 116.140625f}, {69.116699f, 116.801758f},
        {68.696777f, 117.433594f}, {68.264160f, 118.055176f}, {67.843262f, 118.684570f}, {67.460938f, 119.339600f},
        {67.142090f, 120.038330f}, {66.911621f, 120.799316f}, {66.839355f, 121.371582f}, {66.736328f, 121.884521f},
        {66.609863f, 122.348389f}, {66.469238f, 122.770508f}, {66.321777f, 123.159912f}, {66.177246f, 123.525635f},
        {66.042480f, 123.875732f}, {65.926758f, 124.219238f}, {65.837891f, 124.564453f}, {65.806152f, 124.874268f},
        {65.783203f, 125.158936f}, {65.771973f, 125.420654f}, {65.774414f, 125.661133f}, {65.793945f, 125.881836f},
        {65.832031f, 126.084961f}, {65.893066f, 126.271973f}, {65.978027f, 126.444092f},

        {66.089844f, 126.604004f}, {66.154785f, 126.668701f}, {66.211914f, 126.725098f}, {66.263184f, 126.773438f},
        {66.308594f, 126.815186f}, {66.349121f, 126.851074f}, {66.385254f, 126.882080f}, {66.418945f, 126.908691f},
        {66.449707f, 126.932617f}, {66.479004f, 126.954102f}, {66.583496f, 127.021729f}, {66.667480f, 127.095459f},
        {66.730957f, 127.175049f}, {66.776855f, 127.260010f}, {66.805664f, 127.350098f}, {66.818359f, 127.445312f},
        {66.816406f, 127.545166f}, {66.801270f, 127.649658f}, {66.773438f, 127.758789f}, {66.720215f, 127.900879f},
        {66.667969f, 128.036865f}, {66.616211f, 128.167236f}, {66.564941f, 128.291992f}, {66.514160f, 128.411133f},
        {66.462402f, 128.525391f}, {66.409180f, 128.634033f}, {66.354492f, 128.738037f}, {66.297852f, 128.836914f},
        {65.916504f, 129.480225f}, {65.610840f, 130.135742f}, {65.372559f, 130.802979f}, {65.194824f, 131.480713f},
        {65.071289f, 132.168213f}, {64.994629f, 132.864746f}, {64.958496f, 133.569092f}, {64.955078f, 134.280029f},
        {64.978027f, 134.997559f}, {65.000488f, 135.317139f}, {65.023926f, 135.595215f}, {65.049805f, 135.836426f},
        {65.078125f, 136.045410f}, {65.107422f, 136.227051f}, {65.139160f, 136.385498f}, {65.173340f, 136.525635f},
        {65.209961f, 136.652344f}, {65.248535f, 136.769775f}, {65.373535f, 137.110107f}, {65.491211f, 137.446045f},
        {65.601074f, 137.778564f}, {65.702637f, 138.108887f}, {65.794922f, 138.438477f}, {65.877930f, 138.767578f},
        {65.951660f, 139.097656f}, {66.015137f, 139.429688f}, {66.067383f, 139.764648f}, {66.141113f, 140.239258f},
        {66.250488f, 140.664795f}, {66.395020f, 141.048340f}, {66.572266f, 141.396240f}, {66.779297f, 141.715332f},
        {67.014160f, 142.012451f}, {67.273926f, 142.294189f}, {67.557129f, 142.567627f}, {67.861816f, 142.839355f},
        {67.489258f, 142.992432f}, {67.167480f, 143.220459f}, {66.884277f, 143.507080f}, {66.627930f, 143.833496f},
        {66.385254f, 144.183105f}, {66.145508f, 144.537842f}, {65.895996f, 144.879883f}, {65.625000f, 145.192383f},
        {65.320801f, 145.457520f}, {65.059082f, 145.612305f}, {64.857910f, 145.792969f}, {64.709473f, 145.994629f},
        {64.607422f, 146.212646f}, {64.543457f, 146.442627f}, {64.512207f, 146.680176f}, {64.503906f, 146.920898f},
        {64.514160f, 147.159668f}, {64.534180f, 147.392578f}, {64.562988f, 147.612793f}, {64.603027f, 147.813232f},
        {64.654297f, 147.993164f}, {64.716797f, 148.151367f}, {64.791016f, 148.286621f}, {64.877441f, 148.397949f},
        {64.976562f, 148.483643f}, {65.087891f, 148.543457f}, {65.211914f, 148.575195f}, {65.550781f, 148.579834f},
        {65.820312f, 148.638672f}, {66.026855f, 148.744873f}, {66.175781f, 148.890625f}, {66.274902f, 149.068848f},
        {66.329102f, 149.271484f}, {66.346680f, 149.491699f}, {66.331543f, 149.721436f}, {66.291992f, 149.953613f},
        {66.162598f, 150.438232f}, {66.061523f, 150.907471f}, {65.986328f, 151.363770f}, {65.935547f, 151.810059f},
        {65.906250f, 152.248047f}, {65.896973f, 152.680664f}, {65.906250f, 153.110352f}, {65.932129f, 153.539307f},
        {65.971680f, 153.970703f}, {66.020020f, 154.508545f}, {66.018555f, 154.978027f}, {65.971191f, 155.383057f},
        {65.876953f, 155.727295f}, {65.738770f, 156.014648f}, {65.557617f, 156.249756f}, {65.335449f, 156.435547f},
        {65.073242f, 156.576660f}, {64.773926f, 156.676514f}, {64.634277f, 156.693115f}, {64.513184f, 156.706787f},
        {64.408203f, 156.717285f}, {64.317383f, 156.725342f}, {64.238281f, 156.731445f}, {64.169922f, 156.735352f},
        {64.108887f, 156.738037f}, {64.055176f, 156.739502f}, {64.004395f, 156.739746f}, {63.706055f, 156.686035f},
        {63.434570f, 156.569824f}, {63.182617f, 156.407471f}, {62.943848f, 156.215088f}, {62.711914f, 156.009033f},
        {62.480469f, 155.805176f}, {62.243652f, 155.620361f}, {61.994141f, 155.470947f}, {61.725098f, 155.372559f},
        {61.595215f, 155.366699f}, {61.481934f, 155.366699f}, {61.384277f, 155.371582f}, {61.299316f, 155.381104f},
        {61.226074f, 155.395020f}, {61.161621f, 155.412842f}, {61.105469f, 155.433838f}, {61.054688f, 155.458252f},
        {61.008789f, 155.484863f}, {60.870605f, 155.568115f}, {60.727051f, 155.641602f}, {60.582520f, 155.711426f},
        {60.442383f, 155.783447f}, {60.311035f, 155.863281f}, {60.193848f, 155.957031f}, {60.095703f, 156.070312f},
        {60.021484f, 156.209229f}, {59.976562f, 156.379395f}, {59.995117f, 156.646973f}, {60.042969f, 156.873779f},
        {60.115723f, 157.065186f}, {60.209961f, 157.225342f}, {60.322266f, 157.358643f}, {60.448730f, 157.470459f},
        {60.585938f, 157.564453f}, {60.730469f, 157.645752f}, {60.877930f, 157.718994f}, {60.980469f, 157.766846f},
        {61.074219f, 157.809814f}, {61.161621f, 157.849609f}, {61.243164f, 157.886230f}, {61.318848f, 157.920654f},
        {61.390137f, 157.953613f}, {61.458008f, 157.985840f}, {61.521484f, 158.018311f}, {61.583496f, 158.051270f},
        {61.653320f, 158.093994f}, {61.720215f, 158.134766f}, {61.784180f, 158.174072f}, {61.845215f, 158.212158f},
        {61.904297f, 158.249268f}, {61.961426f, 158.286377f}, {62.015625f, 158.322998f}, {62.069336f, 158.360596f},
        {62.120605f, 158.398682f}, {62.177734f, 158.459961f}, {62.224609f, 158.520264f}, {62.262695f, 158.579590f},
        {62.289062f, 158.638184f}, {62.304199f, 158.695068f}, {62.308105f, 158.750244f}, {62.298828f, 158.803711f},
        {62.275879f, 158.854736f}, {62.238770f, 158.903564f}, {62.151367f, 158.961426f}, {62.068359f, 158.995117f},
        {61.989746f, 159.007812f}, {61.915039f, 159.002930f}, {61.843750f, 158.983398f}, {61.774414f, 158.952393f},
        {61.708008f, 158.912842f}, {61.643066f, 158.867920f}, {61.579590f, 158.821045f}, {61.522461f, 158.773438f},
        {61.469238f, 158.728516f}, {61.417969f, 158.687012f}, {61.369629f, 158.647705f}, {61.322754f, 158.610596f},
        {61.278320f, 158.575928f}, {61.233887f, 158.542480f}, {61.190918f, 158.510986f}, {61.147949f, 158.480713f},
        {60.975586f, 158.380615f}, {60.804199f, 158.287842f}, {60.632812f, 158.202148f}, {60.462402f, 158.123779f},
        {60.291504f, 158.053223f}, {60.120605f, 157.990723f}, {59.947754f, 157.936279f}, {59.774414f, 157.890137f},
        {59.599121f, 157.853027f}, {59.264160f, 157.855225f}, {58.938477f, 157.844971f}, {58.620605f, 157.827393f},
        {58.310059f, 157.809570f}, {58.006348f, 157.796875f}, {57.708496f, 157.795898f}, {57.416016f, 157.812500f},
        {57.126953f, 157.852539f}, {56.842285f, 157.922852f}, {56.733398f, 157.981201f}, {56.643066f, 158.036133f},
        {56.570801f, 158.087891f}, {56.514648f, 158.137939f}, {56.472656f, 158.186035f}, {56.443359f, 158.233154f},
        {56.424316f, 158.280029f}, {56.415527f, 158.326660f}, {56.413574f, 158.374756f}, {56.429199f, 158.409668f},
        {56.444824f, 158.443604f}, {56.459961f, 158.475830f}, {56.475586f, 158.505615f}, {56.491699f, 158.532227f},
        {56.507812f, 158.555664f}, {56.523926f, 158.575195f}, {56.541016f, 158.590332f}, {56.558105f, 158.600342f},
        {57.105469f, 158.654297f}, {57.649902f, 158.717529f}, {58.189941f, 158.795410f}, {58.726074f, 158.892090f},
        {59.257324f, 159.012207f}, {59.781250f, 159.159912f}, {60.298828f, 159.340332f}, {60.808594f, 159.557861f},
        {61.310059f, 159.817139f}, {62.013672f, 159.716553f}, {62.691406f, 159.595947f}, {63.342773f, 159.447754f},
        {63.964355f, 159.264893f}, {64.554688f, 159.040771f}, {65.110840f, 158.767578f}, {65.630859f, 158.438477f},
        {66.112305f, 158.046387f}, {66.553223f, 157.584229f}, {66.880859f, 157.046875f}, {67.138184f, 156.515625f},
        {67.329102f, 155.990967f}, {67.458496f, 155.473145f}, {67.529297f, 154.962402f}, {67.546875f, 154.459229f},
        {67.514160f, 153.963867f}, {67.435547f, 153.476562f}, {67.314941f, 152.997803f}, {67.355469f, 152.297363f},
        {67.388184f, 151.623047f}, {67.411621f, 150.972168f}, {67.424805f, 150.341064f}, {67.427734f, 149.725830f},
        {67.417969f, 149.123535f}, {67.395020f, 148.530273f}, {67.358398f, 147.942871f}, {67.307129f, 147.357666f},
        {67.250488f, 146.713623f}, {67.252441f, 146.174561f}, {67.311523f, 145.736572f}, {67.423828f, 145.395996f},
        {67.588379f, 145.147949f}, {67.802734f, 144.989258f}, {68.063477f, 144.915283f}, {68.368652f, 144.922363f},
        {68.715820f, 145.006592f}, {68.931641f, 145.099121f}, {69.125488f, 145.176758f}, {69.299805f, 145.237061f},
        {69.455078f, 145.278564f}, {69.595215f, 145.300293f}, {69.721680f, 145.300293f}, {69.836914f, 145.277832f},
        {69.943848f, 145.230469f}, {70.043457f, 145.156982f}, {70.153320f, 145.012451f}, {70.238281f, 144.869873f},
        {70.300293f, 144.729248f}, {70.340332f, 144.590332f}, {70.360352f, 144.453613f}, {70.362793f, 144.318848f},
        {70.347168f, 144.186768f}, {70.316895f, 144.057129f}, {70.272461f, 143.929932f}, {70.137695f, 143.645020f},
        {70.019043f, 143.362549f}, {69.914551f, 143.082031f}, {69.823242f, 142.802734f}, {69.743164f, 142.524414f},
        {69.673340f, 142.246338f}, {69.612793f, 141.967529f}, {69.559082f, 141.688232f}, {69.512207f, 141.407959f},
        {69.450684f, 141.057617f}, {69.374023f, 140.738281f}, {69.281738f, 140.448486f}, {69.173828f, 140.185791f},
        {69.049316f, 139.948242f}, {68.908203f, 139.733643f}, {68.749023f, 139.539551f}, {68.572754f, 139.364502f},
        {68.378418f, 139.206055f}, {67.903809f, 138.880615f}, {67.506836f, 138.544922f}, {67.187012f, 138.195068f},
        {66.938965f, 137.826904f}, {66.760254f, 137.437256f}, {66.649414f, 137.022461f}, {66.603027f, 136.578125f},
        {66.618164f, 136.101318f}, {66.691895f, 135.588379f}, {66.760254f, 135.321045f}, {66.822266f, 135.083740f},
        {66.877441f, 134.872803f}, {66.924805f, 134.684814f}, {66.963867f, 134.516357f}, {66.992676f, 134.364014f},
        {67.011719f, 134.224365f}, {67.018555f, 134.094238f}, {67.013672f, 133.969971f}, {66.924805f, 133.401611f},
        {66.896484f, 132.859863f}, {66.921387f, 132.342285f}, {66.995117f, 131.846680f}, {67.109863f, 131.369629f},
        {67.260742f, 130.909424f}, {67.440918f, 130.463135f}, {67.645020f, 130.028076f}, {67.865723f, 129.601562f},
        {68.087402f, 129.186523f}, {68.269531f, 128.798584f}, {68.410645f, 128.434082f}, {68.508789f, 128.088867f},
        {68.563965f, 127.759766f}, {68.574219f, 127.442139f}, {68.538574f, 127.133057f}, {68.456055f, 126.828613f},
        {68.324219f, 126.524658f}, {68.140625f, 126.212646f}, {67.998047f, 125.911377f}, {67.893555f, 125.619873f},
        {67.826172f, 125.337646f}, {67.793457f, 125.064209f}, {67.793945f, 124.798828f}, {67.825195f, 124.540527f},
        {67.885254f, 124.288818f}, {67.972656f, 124.043213f}, {68.274902f, 123.408936f}, {68.545898f, 122.767578f},
        {68.796875f, 122.126465f}, {69.039062f, 121.492920f}, {69.285156f, 120.873779f}, {69.546875f, 120.276611f},
        {69.836914f, 119.708252f}, {70.165527f, 119.176758f}, {70.546875f, 118.688721f}, {70.690918f, 118.131836f},
        {70.860840f, 117.647705f}, {71.053711f, 117.226807f}, {71.266113f, 116.858887f}, {71.495605f, 116.535156f},
        {71.738281f, 116.245850f}, {71.992188f, 115.981445f}, {72.253418f, 115.732666f}, {72.519043f, 115.489746f},
        {72.785645f, 115.202637f}, {72.986328f, 114.905273f}, {73.124512f, 114.600342f}, {73.204590f, 114.290527f},
        {73.229492f, 113.978516f}, {73.203125f, 113.667236f}, {73.129395f, 113.358887f}, {73.011719f, 113.056641f},
        {72.853027f, 112.762695f}, {72.622559f, 112.434570f}, {72.450684f, 112.143311f}, {72.337402f, 111.886963f},
        {72.280273f, 111.661865f}, {72.279785f, 111.465820f}, {72.333496f, 111.295654f}, {72.441406f, 111.148682f},
        {72.603027f, 111.021973f}, {72.815918f, 110.912598f}, {73.093750f, 110.827393f}, {73.358398f, 110.751953f},
        {73.610352f, 110.681885f}, {73.849609f, 110.613037f}, {74.078125f, 110.540283f}, {74.294922f, 110.460205f},
        {74.502441f, 110.367920f}, {74.699707f, 110.259033f}, {74.888672f, 110.129150f}, {75.138184f, 109.877930f},
        {75.344238f, 109.631104f}, {75.504883f, 109.387451f}, {75.620605f, 109.146729f}, {75.687500f, 108.907227f},
        {75.706055f, 108.668945f}, {75.673828f, 108.430664f}, {75.589844f, 108.191650f}, {75.452637f, 107.950439f},
        {74.953613f, 107.359863f}, {74.586426f, 106.864746f}, {74.340332f, 106.444092f}, {74.201660f, 106.075928f},
        {74.157227f, 105.738525f}, {74.195312f, 105.410889f}, {74.301758f, 105.071045f}, {74.465332f, 104.697754f},
        {74.672852f, 104.269287f}, {74.996582f, 103.558105f}, {75.302734f, 102.873535f}, {75.589844f, 102.210938f},
        {75.857422f, 101.565674f}, {76.102539f, 100.932861f}, {76.325195f, 100.308105f}, {76.522461f, 99.686035f},
        {76.694336f, 99.062256f},  {76.837891f, 98.432129f},  {76.970215f, 97.800049f},  {77.145508f, 97.245850f},
        {77.354004f, 96.758057f},  {77.587891f, 96.324219f},  {77.839844f, 95.932861f},  {78.101562f, 95.572510f},
        {78.364258f, 95.230957f},  {78.619629f, 94.896973f},  {78.859863f, 94.558350f},  {78.963379f, 94.384033f},
        {79.054688f, 94.228516f},  {79.134766f, 94.089844f},  {79.206543f, 93.966064f},  {79.270508f, 93.855469f},
        {79.328125f, 93.755859f},  {79.381836f, 93.665039f},  {79.432129f, 93.581543f},  {79.481445f, 93.503418f},
        {79.754883f, 93.085205f},  {79.963867f, 92.736572f},  {80.105469f, 92.446777f},  {80.178223f, 92.202393f},
        {80.179199f, 91.991455f},  {80.106445f, 91.801270f},  {79.958496f, 91.620117f},  {79.732422f, 91.435547f},
        {79.425781f, 91.234863f},  {79.683594f, 90.932861f},  {79.915039f, 90.603271f},  {80.124512f, 90.250244f},
        {80.317383f, 89.877930f},  {80.497559f, 89.490723f},  {80.670410f, 89.092773f},  {80.840332f, 88.687988f},
        {81.011230f, 88.281006f},  {81.188477f, 87.875977f},  {81.600098f, 87.029053f},  {81.993164f, 86.200195f},
        {82.368164f, 85.386230f},  {82.724609f, 84.583496f},  {83.062012f, 83.788818f},  {83.380859f, 82.998535f},
        {83.680176f, 82.209229f},  {83.960938f, 81.417969f},  {84.222168f, 80.621094f},  {84.312012f, 80.331299f},
        {84.388184f, 80.084961f},  {84.450195f, 79.876709f},  {84.499512f, 79.701660f},  {84.536621f, 79.555176f},
        {84.562988f, 79.431641f},  {84.580078f, 79.326660f},  {84.588379f, 79.235352f},  {84.588379f, 79.152344f},
        {84.568359f, 78.811523f},  {84.561523f, 78.481445f},  {84.571289f, 78.162842f},  {84.601562f, 77.855957f},
        {84.654785f, 77.562012f},  {84.735840f, 77.281006f},  {84.846680f, 77.013184f},  {84.990723f, 76.760010f},
        {85.171875f, 76.521240f},  {85.327148f, 76.366699f},  {85.460449f, 76.213379f},  {85.572754f, 76.061279f},
        {85.666992f, 75.909668f},  {85.744141f, 75.758545f},  {85.805664f, 75.607178f},  {85.854004f, 75.456055f},
        {85.889648f, 75.303955f},  {85.915527f, 75.150635f},
    };  // data size = 685

    Vec2 vertices21[] = {
        {290.250000f, 98.1250000f}, {235.000000f, 90.8750000f}, {270.500000f, 109.875000f}, {235.000000f, 119.125000f},
        {275.250000f, 145.875000f}, {249.500000f, 145.875000f}, {249.500000f, 178.125000f}, {275.250000f, 187.375015f},
        {294.750488f, 168.333344f}, {311.250000f, 181.125000f}, {257.000000f, 213.625015f}, {338.500000f, 193.125000f},
        {300.000000f, 211.125015f}, {333.750000f, 211.125015f}, {368.250000f, 206.625000f}, {377.000000f, 178.125000f},
        {421.750000f, 170.125000f}, {416.250000f, 115.375000f}, {391.250000f, 157.875000f}, {338.500000f, 131.625000f},
        {362.750000f, 131.625000f}, {362.750000f, 106.875000f}, {306.500000f, 119.125000f}, {324.250000f, 85.1250000f},
        {227.500000f, 61.8750000}};

    Vec2 vertices22[] = {
        {149.233887f, 218.018799f}, {149.503906f, 217.996582f}, {149.753906f, 217.993164f}, {149.984375f, 218.015381f},
        {150.194824f, 218.071045f}, {150.385742f, 218.166504f}, {150.557617f, 218.309570f}, {150.709473f, 218.507080f},
        {150.842773f, 218.766602f}, {150.955566f, 219.094727f}, {151.050293f, 219.499023f}, {151.129883f, 219.812988f},
        {151.247070f, 220.123047f}, {151.402344f, 220.420410f}, {151.591797f, 220.697754f}, {151.815430f, 220.946289f},
        {152.070312f, 221.157959f}, {152.355469f, 221.324463f}, {152.669434f, 221.437988f}, {153.009766f, 221.489990f},
        {153.375488f, 221.472412f}, {153.593750f, 221.451904f}, {153.801758f, 221.455811f}, {153.999512f, 221.485352f},
        {154.187500f, 221.540283f}, {154.364258f, 221.620850f}, {154.531738f, 221.728027f}, {154.687988f, 221.861816f},
        {154.833496f, 222.022705f}, {154.968262f, 222.211670f}, {155.092285f, 222.428223f}, {155.154297f, 222.550537f},
        {155.213379f, 222.672363f}, {155.265625f, 222.795166f}, {155.307617f, 222.918945f}, {155.335938f, 223.044922f},
        {155.347168f, 223.173096f}, {155.337402f, 223.303711f}, {155.304199f, 223.438232f}, {155.243164f, 223.576172f},
        {155.151367f, 223.718994f}, {155.076660f, 223.828613f}, {155.010254f, 223.944336f}, {154.952148f, 224.065186f},
        {154.900391f, 224.190918f}, {154.854980f, 224.321045f}, {154.815430f, 224.455078f}, {154.780762f, 224.592285f},
        {154.750000f, 224.732422f}, {154.722168f, 224.874756f}, {154.696289f, 225.019043f}, {154.643555f, 225.258057f},
        {154.572754f, 225.470215f}, {154.484375f, 225.653076f}, {154.377930f, 225.805176f}, {154.253418f, 225.924561f},
        {154.113770f, 226.009766f}, {153.957031f, 226.058594f}, {153.784180f, 226.069336f}, {153.596191f, 226.040283f},
        {153.392578f, 225.969727f}, {153.266602f, 225.921631f}, {153.145508f, 225.889404f}, {153.027832f, 225.872559f},
        {152.914551f, 225.870117f}, {152.803711f, 225.882080f}, {152.695312f, 225.907227f}, {152.588379f, 225.945068f},
        {152.482910f, 225.995117f}, {152.378418f, 226.056885f}, {152.273926f, 226.129395f}, {152.165527f, 226.218994f},
        {152.074707f, 226.315186f}, {152.002930f, 226.415771f}, {151.952637f, 226.519775f}, {151.924805f, 226.625000f},
        {151.922363f, 226.729980f}, {151.946777f, 226.833496f}, {152.000000f, 226.932861f}, {152.084473f, 227.027344f},
        {152.201660f, 227.115234f}, {152.386230f, 227.252686f}, {152.529297f, 227.405029f}, {152.636719f, 227.570801f},
        {152.712891f, 227.747803f}, {152.763672f, 227.935303f}, {152.793457f, 228.130859f}, {152.808105f, 228.333008f},
        {152.812012f, 228.540771f}, {152.811523f, 228.751953f}, {152.811035f, 228.965332f}, {152.808594f, 229.304932f},
        {152.803223f, 229.644043f}, {152.801758f, 229.980713f}, {152.813477f, 230.313477f}, {152.844238f, 230.640137f},
        {152.902832f, 230.958496f}, {152.996582f, 231.267090f}, {153.131836f, 231.563965f}, {153.317383f, 231.846680f},
        {153.561035f, 232.114014f}, {153.664062f, 232.236572f}, {153.737305f, 232.376953f}, {153.784180f, 232.531250f},
        {153.809570f, 232.697021f}, {153.818359f, 232.871338f}, {153.813477f, 233.051025f}, {153.799805f, 233.232910f},
        {153.781738f, 233.413818f}, {153.763184f, 233.591553f}, {153.749512f, 233.762207f}, {153.742676f, 234.083984f},
        {153.767578f, 234.363770f}, {153.822266f, 234.603271f}, {153.906738f, 234.804688f}, {154.020508f, 234.969482f},
        {154.162598f, 235.099365f}, {154.332520f, 235.196289f}, {154.529785f, 235.262451f}, {154.754395f, 235.298828f},
        {155.004395f, 235.307617f}, {155.169434f, 235.302734f}, {155.334961f, 235.296387f}, {155.500488f, 235.291748f},
        {155.666016f, 235.292480f}, {155.830078f, 235.301514f}, {155.993164f, 235.322510f}, {156.154297f, 235.358887f},
        {156.312988f, 235.413574f}, {156.468750f, 235.490479f}, {156.622070f, 235.592285f}, {156.766113f, 234.704346f},
        {156.953613f, 233.824707f}, {157.166016f, 232.949951f}, {157.384277f, 232.076172f}, {157.591309f, 231.200195f},
        {157.768066f, 230.318359f}, {157.896973f, 229.427002f}, {157.959473f, 228.522705f}, {157.937988f, 227.602295f},
        {157.813477f, 226.661621f}, {158.010742f, 226.346191f}, {158.148926f, 226.019043f}, {158.237793f, 225.681396f},
        {158.287109f, 225.336182f}, {158.306152f, 224.984619f}, {158.305176f, 224.629150f}, {158.293457f, 224.271484f},
        {158.280762f, 223.913818f}, {158.276367f, 223.557617f}, {158.290527f, 223.205322f}, {158.435547f, 222.898926f},
        {158.535645f, 222.586670f}, {158.597656f, 222.269531f}, {158.628906f, 221.947998f}, {158.636719f, 221.623535f},
        {158.626953f, 221.297119f}, {158.608887f, 220.969727f}, {158.587402f, 220.641846f}, {158.570801f, 220.315186f},
        {158.566895f, 219.989990f}, {158.564941f, 219.874512f}, {158.555664f, 219.757080f}, {158.538574f, 219.640625f},
        {158.511719f, 219.528076f}, {158.475586f, 219.422607f}, {158.426758f, 219.326904f}, {158.366211f, 219.243652f},
        {158.291016f, 219.176514f}, {158.201660f, 219.128174f}, {158.095703f, 219.101318f}, {157.973633f, 219.099121f},
        {157.866211f, 219.124268f}, {157.772461f, 219.173828f}, {157.690430f, 219.244141f}, {157.619629f, 219.332031f},
        {157.558105f, 219.433838f}, {157.505371f, 219.546631f}, {157.459473f, 219.667480f}, {157.419434f, 219.791992f},
        {157.384277f, 219.917480f}, {157.335449f, 220.127441f}, {157.300293f, 220.339111f}, {157.277344f, 220.552490f},
        {157.263184f, 220.766602f}, {157.255859f, 220.981689f}, {157.253418f, 221.197510f}, {157.253906f, 221.413330f},
        {157.254883f, 221.629395f}, {157.253418f, 221.845215f}, {157.248047f, 222.060547f}, {157.243164f, 222.300781f},
        {157.245117f, 222.543701f}, {157.249023f, 222.790527f}, {157.252441f, 223.043213f}, {157.251465f, 223.302734f},
        {157.243164f, 223.571289f}, {157.223145f, 223.850586f}, {157.188477f, 224.141846f}, {157.135742f, 224.447021f},
        {157.061523f, 224.767090f}, {157.016113f, 224.466064f}, {156.981445f, 224.179688f}, {156.956055f, 223.906738f},
        {156.939453f, 223.646240f}, {156.929688f, 223.395996f}, {156.926758f, 223.154541f}, {156.929199f, 222.920166f},
        {156.936035f, 222.692383f}, {156.946289f, 222.468750f}, {156.958496f, 222.248047f}, {156.975098f, 221.615967f},
        {156.948730f, 221.003418f}, {156.880859f, 220.409668f}, {156.772461f, 219.834473f}, {156.624512f, 219.276123f},
        {156.438477f, 218.734131f}, {156.216309f, 218.208008f}, {155.958984f, 217.696289f}, {155.666992f, 217.199219f},
        {155.342773f, 216.714600f}, {155.167969f, 216.432373f}, {155.027344f, 216.133789f}, {154.915527f, 215.822510f},
        {154.826172f, 215.500244f}, {154.752930f, 215.170898f}, {154.691406f, 214.837158f}, {154.634277f, 214.501221f},
        {154.576172f, 214.166504f}, {154.510254f, 213.835938f}, {154.431641f, 213.511963f}, {154.344727f, 213.185303f},
        {154.259277f, 212.859375f}, {154.173828f, 212.534180f}, {154.086426f, 212.210693f}, {153.995605f, 211.889160f},
        {153.898926f, 211.569580f}, {153.795898f, 211.252930f}, {153.682129f, 210.939209f}, {153.557617f, 210.628906f},
        {153.420410f, 210.322754f}, {153.329102f, 210.120117f}, {153.245605f, 209.903320f}, {153.175293f, 209.677979f},
        {153.125000f, 209.449463f}, {153.100586f, 209.223877f}, {153.108398f, 209.006592f}, {153.155762f, 208.802979f},
        {153.249023f, 208.619385f}, {153.394043f, 208.460693f}, {153.597168f, 208.333252f}, {153.823242f, 208.257324f},
        {154.026367f, 208.249023f}, {154.207520f, 208.300049f}, {154.368652f, 208.402100f}, {154.511719f, 208.548096f},
        {154.638184f, 208.729492f}, {154.748535f, 208.938721f}, {154.845703f, 209.167480f}, {154.930664f, 209.407959f},
        {155.004395f, 209.652832f}, {155.038086f, 209.791016f}, {155.062988f, 209.930908f}, {155.080078f, 210.072754f},
        {155.091309f, 210.215576f}, {155.097656f, 210.359131f}, {155.102051f, 210.503662f}, {155.104492f, 210.648193f},
        {155.108398f, 210.792480f}, {155.113770f, 210.936768f}, {155.123047f, 211.080078f}, {155.133789f, 211.237549f},
        {155.143555f, 211.397705f}, {155.156738f, 211.557861f}, {155.176758f, 211.714111f}, {155.208008f, 211.863037f},
        {155.253418f, 212.002441f}, {155.317383f, 212.127930f}, {155.403809f, 212.237061f}, {155.516602f, 212.326172f},
        {155.659180f, 212.392334f}, {155.817383f, 212.430664f}, {155.963867f, 212.436035f}, {156.100098f, 212.411377f},
        {156.225586f, 212.359131f}, {156.341309f, 212.281738f}, {156.447754f, 212.182373f}, {156.545410f, 212.062988f},
        {156.634766f, 211.926270f}, {156.716309f, 211.774902f}, {156.790527f, 211.611328f}, {156.820801f, 211.036133f},
        {156.856934f, 210.461182f}, {156.894531f, 209.886230f}, {156.929688f, 209.311279f}, {156.958008f, 208.736084f},
        {156.973633f, 208.161133f}, {156.973633f, 207.585938f}, {156.953125f, 207.010498f}, {156.907227f, 206.435059f},
        {156.832031f, 205.859375f}, {156.737305f, 205.664795f}, {156.628418f, 205.505127f}, {156.505859f, 205.376221f},
        {156.372070f, 205.273926f}, {156.228516f, 205.194580f}, {156.077637f, 205.133789f}, {155.919434f, 205.087646f},
        {155.757812f, 205.051758f}, {155.592285f, 205.022461f}, {155.425781f, 204.995850f}, {155.004883f, 204.906250f},
        {154.632812f, 204.781006f}, {154.306152f, 204.616455f}, {154.023926f, 204.409912f}, {153.782227f, 204.158203f},
        {153.579590f, 203.858643f}, {153.413574f, 203.507568f}, {153.281250f, 203.103027f}, {153.180176f, 202.640869f},
        {153.107910f, 202.119141f}, {153.023926f, 201.550049f}, {152.897461f, 201.041016f}, {152.727539f, 200.590820f},
        {152.514648f, 200.199707f}, {152.256836f, 199.867188f}, {151.954102f, 199.592041f}, {151.605957f, 199.374756f},
        {151.210449f, 199.214111f}, {150.769043f, 199.109863f}, {150.278809f, 199.061523f}, {150.056641f, 199.037109f},
        {149.844727f, 198.985352f}, {149.640625f, 198.910645f}, {149.443848f, 198.816895f}, {149.251465f, 198.708740f},
        {149.063477f, 198.590576f}, {148.877441f, 198.466553f}, {148.691895f, 198.341309f}, {148.505859f, 198.219238f},
        {148.316406f, 198.104492f}, {148.237793f, 198.050781f}, {148.170898f, 197.988281f}, {148.115234f, 197.916748f},
        {148.073242f, 197.837891f}, {148.043457f, 197.752197f}, {148.027344f, 197.660400f}, {148.023926f, 197.563477f},
        {148.035156f, 197.462158f}, {148.060547f, 197.357178f}, {148.100098f, 197.249756f}, {148.149902f, 197.149170f},
        {148.205566f, 197.063721f}, {148.266113f, 196.993408f}, {148.332031f, 196.939697f}, {148.401855f, 196.902832f},
        {148.474609f, 196.883301f}, {148.551270f, 196.882324f}, {148.629883f, 196.900391f}, {148.710938f, 196.937988f},
        {148.792969f, 196.996094f}, {149.102539f, 197.201660f}, {149.401367f, 197.306396f}, {149.689941f, 197.326172f},
        {149.971191f, 197.278320f}, {150.245117f, 197.178955f}, {150.514648f, 197.044922f}, {150.781250f, 196.892090f},
        {151.045410f, 196.737793f}, {151.309570f, 196.598145f}, {151.575195f, 196.489502f}, {151.748535f, 196.409424f},
        {151.875000f, 196.302246f}, {151.957520f, 196.171631f}, {152.000977f, 196.023193f}, {152.006348f, 195.861572f},
        {151.979004f, 195.690918f}, {151.920898f, 195.516113f}, {151.836426f, 195.341797f}, {151.728027f, 195.172607f},
        {151.600098f, 195.013672f}, {151.513672f, 194.928955f}, {151.422852f, 194.859619f}, {151.328125f, 194.803223f},
        {151.229980f, 194.758057f}, {151.128906f, 194.721924f}, {151.025879f, 194.693115f}, {150.920410f, 194.669434f},
        {150.814453f, 194.648926f}, {150.708008f, 194.630127f}, {150.601562f, 194.610596f}, {150.239746f, 194.517090f},
        {149.934570f, 194.385498f}, {149.686523f, 194.217773f}, {149.496582f, 194.013672f}, {149.366211f, 193.774902f},
        {149.296875f, 193.502686f}, {149.288574f, 193.197754f}, {149.343262f, 192.861084f}, {149.461426f, 192.493652f},
        {149.644531f, 192.096924f}, {149.759766f, 191.864258f}, {149.857910f, 191.638184f}, {149.935059f, 191.417725f},
        {149.989258f, 191.201172f}, {150.018066f, 190.986572f}, {150.018555f, 190.772461f}, {149.989258f, 190.557617f},
        {149.926270f, 190.340576f}, {149.828125f, 190.119141f}, {149.692383f, 189.892578f}, {149.605957f, 189.741943f},
        {149.545410f, 189.585449f}, {149.504395f, 189.423340f}, {149.480957f, 189.257324f}, {149.469238f, 189.087646f},
        {149.466797f, 188.916016f}, {149.469238f, 188.742920f}, {149.471680f, 188.569824f}, {149.471191f, 188.397461f},
        {149.463379f, 188.226807f}, {149.418945f, 187.832031f}, {149.352539f, 187.502441f}, {149.261230f, 187.236328f},
        {149.145020f, 187.033203f}, {149.001465f, 186.891113f}, {148.829590f, 186.809570f}, {148.627930f, 186.787109f},
        {148.395020f, 186.822510f}, {148.129395f, 186.914795f}, {147.829590f, 187.062744f}, {147.795410f, 187.081787f},
        {147.777344f, 187.092529f}, {147.770508f, 187.097412f}, {147.772461f, 187.098389f}, {147.777832f, 187.097412f},
        {147.783203f, 187.096436f}, {147.785645f, 187.098633f}, {147.779785f, 187.104980f}, {147.762695f, 187.118164f},
        {147.729492f, 187.140381f}, {147.565430f, 187.234863f}, {147.402832f, 187.303223f}, {147.243164f, 187.346191f},
        {147.084473f, 187.363770f}, {146.928223f, 187.357178f}, {146.772949f, 187.326660f}, {146.620117f, 187.272949f},
        {146.470215f, 187.196289f}, {146.320801f, 187.097168f}, {146.174316f, 186.976562f}, {146.115234f, 186.919189f},
        {146.062500f, 186.856445f}, {146.017090f, 186.789551f}, {145.978027f, 186.718506f}, {145.948730f, 186.643311f},
        {145.929199f, 186.564941f}, {145.920410f, 186.483398f}, {145.923828f, 186.398926f}, {145.940430f, 186.312500f},
        {145.970703f, 186.223633f}, {146.056641f, 186.039062f}, {146.151855f, 185.867432f}, {146.256348f, 185.710205f},
        {146.371582f, 185.568604f}, {146.496094f, 185.444580f}, {146.631348f, 185.339355f}, {146.776367f, 185.254395f},
        {146.931641f, 185.191406f}, {147.097656f, 185.151855f}, {147.273438f, 185.136963f}, {147.505859f, 185.134033f},
        {147.734375f, 185.125732f}, {147.958008f, 185.106201f}, {148.172852f, 185.068848f}, {148.378906f, 185.007080f},
        {148.572754f, 184.914795f}, {148.753418f, 184.785156f}, {148.917969f, 184.612061f}, {149.065430f, 184.389160f},
        {149.192383f, 184.109619f}, {149.231934f, 183.911377f}, {149.261719f, 183.712891f}, {149.283691f, 183.513428f},
        {149.297852f, 183.313477f}, {149.305176f, 183.113525f}, {149.305664f, 182.913330f}, {149.301270f, 182.712891f},
        {149.291504f, 182.512695f}, {149.278320f, 182.312988f}, {149.261230f, 182.113525f}, {149.207031f, 181.702637f},
        {149.126953f, 181.349121f}, {149.018066f, 181.052002f}, {148.879395f, 180.809814f}, {148.708984f, 180.619873f},
        {148.505371f, 180.480957f}, {148.266602f, 180.391602f}, {147.991211f, 180.349854f}, {147.677246f, 180.354248f},
        {147.323242f, 180.402588f}, {147.244141f, 180.421875f}, {147.164062f, 180.447510f}, {147.083496f, 180.474609f},
        {147.003906f, 180.497314f}, {146.926270f, 180.511475f}, {146.850586f, 180.510986f}, {146.778809f, 180.491699f},
        {146.711914f, 180.447754f}, {146.649902f, 180.374512f}, {146.594727f, 180.266846f}, {146.560059f, 180.163330f},
        {146.542480f, 180.061768f}, {146.538574f, 179.962402f}, {146.548340f, 179.865723f}, {146.570312f, 179.771729f},
        {146.602051f, 179.681152f}, {146.642578f, 179.594238f}, {146.690918f, 179.510742f}, {146.745117f, 179.432373f},
        {146.803711f, 179.358398f}, {147.060547f, 179.091064f}, {147.336914f, 178.854736f}, {147.626465f, 178.638184f},
        {147.923340f, 178.431152f}, {148.218750f, 178.223389f}, {148.507812f, 178.003906f}, {148.783203f, 177.762451f},
        {149.038086f, 177.488525f}, {149.265625f, 177.171631f}, {149.458496f, 176.800781f}, {149.491699f, 176.747559f},
        {149.534180f, 176.716309f}, {149.583984f, 176.704102f}, {149.639648f, 176.708008f}, {149.697754f, 176.726074f},
        {149.758789f, 176.754883f}, {149.819824f, 176.791748f}, {149.878418f, 176.833984f}, {149.934082f, 176.878662f},
        {149.983887f, 176.923096f}, {150.159180f, 177.071045f}, {150.333008f, 177.187256f}, {150.506836f, 177.270752f},
        {150.680176f, 177.320801f}, {150.853027f, 177.337646f}, {151.024902f, 177.319824f}, {151.196777f, 177.267822f},
        {151.367676f, 177.180664f}, {151.537109f, 177.057373f}, {151.705566f, 176.898438f}, {151.809570f, 176.775635f},
        {151.893066f, 176.646973f}, {151.957520f, 176.512695f}, {152.002930f, 176.374023f}, {152.031250f, 176.230957f},
        {152.041504f, 176.083740f}, {152.035645f, 175.932617f}, {152.013672f, 175.778320f}, {151.976562f, 175.621094f},
        {151.924805f, 175.461670f}, {151.824219f, 175.225830f}, {151.708984f, 175.028809f}, {151.580078f, 174.868164f},
        {151.437988f, 174.742188f}, {151.284180f, 174.649414f}, {151.118164f, 174.587646f}, {150.941895f, 174.555176f},
        {150.754395f, 174.549805f}, {150.558105f, 174.569824f}, {150.352539f, 174.613281f}, {150.306152f, 174.624023f},
        {150.258301f, 174.629639f}, {150.207520f, 174.628662f}, {150.153320f, 174.618652f}, {150.095215f, 174.597168f},
        {150.031250f, 174.562256f}, {149.961426f, 174.510986f}, {149.884277f, 174.442383f}, {149.798340f, 174.353271f},
        {149.703613f, 174.241211f}, {150.060059f, 174.027832f}, {150.395020f, 173.787598f}, {150.710449f, 173.523926f},
        {151.008789f, 173.239258f}, {151.291992f, 172.936279f}, {151.562988f, 172.617920f}, {151.822754f, 172.286865f},
        {152.074707f, 171.945801f}, {152.320801f, 171.597656f}, {152.563477f, 171.244873f}, {152.697266f, 171.098633f},
        {152.860352f, 170.983398f}, {153.041504f, 170.888184f}, {153.229492f, 170.801025f}, {153.411621f, 170.710693f},
        {153.577148f, 170.606445f}, {153.714355f, 170.476074f}, {153.811035f, 170.308350f}, {153.855469f, 170.092529f},
        {153.836426f, 169.816406f}, {153.765625f, 169.538818f}, {153.661621f, 169.289062f}, {153.527832f, 169.064697f},
        {153.370117f, 168.862305f}, {153.190430f, 168.679199f}, {152.995117f, 168.512695f}, {152.787598f, 168.359131f},
        {152.573242f, 168.215820f}, {152.355957f, 168.079834f}, {152.139648f, 167.947754f}, {152.137695f, 167.946289f},
        {152.133301f, 167.942383f}, {152.126465f, 167.937012f}, {152.117676f, 167.930908f}, {152.106445f, 167.924561f},
        {152.093750f, 167.918701f}, {152.079102f, 167.914307f}, {152.062988f, 167.911865f}, {152.044922f, 167.911865f},
        {152.025879f, 167.915527f}, {151.527344f, 168.006592f}, {151.046387f, 168.008301f}, {150.580078f, 167.936523f},
        {150.124512f, 167.806152f}, {149.677246f, 167.632080f}, {149.235840f, 167.429443f}, {148.797363f, 167.213379f},
        {148.357910f, 166.998779f}, {147.916016f, 166.800781f}, {147.468262f, 166.634277f}, {147.387695f, 166.612793f},
        {147.303711f, 166.593506f}, {147.219238f, 166.574219f}, {147.137207f, 166.550537f}, {147.061035f, 166.519043f},
        {146.993652f, 166.475830f}, {146.938965f, 166.417725f}, {146.899902f, 166.341309f}, {146.879883f, 166.242432f},
        {146.881836f, 166.117676f}, {146.903809f, 166.005859f}, {146.942383f, 165.916260f}, {146.996094f, 165.846924f},
        {147.060547f, 165.794678f}, {147.134766f, 165.757324f}, {147.216309f, 165.731689f}, {147.301270f, 165.715820f},
        {147.388672f, 165.706787f}, {147.474609f, 165.702148f}, {147.557617f, 165.699219f}, {147.803711f, 165.688965f},
        {148.047852f, 165.679688f}, {148.290039f, 165.678467f}, {148.528320f, 165.691406f}, {148.763672f, 165.724365f},
        {148.995605f, 165.784424f}, {149.223145f, 165.877441f}, {149.445312f, 166.009766f}, {149.662598f, 166.187988f},
        {149.874512f, 166.417725f}, {150.068848f, 166.596436f}, {150.316406f, 166.728760f}, {150.604980f, 166.817383f},
        {150.920410f, 166.864502f}, {151.251953f, 166.872559f}, {151.585938f, 166.843506f}, {151.908691f, 166.779541f},
        {152.209473f, 166.682617f}, {152.474609f, 166.555908f}, {152.690430f, 166.400391f}, {152.913574f, 166.154053f},
        {153.083008f, 165.871338f}, {153.197754f, 165.562256f}, {153.259277f, 165.237305f}, {153.268555f, 164.906006f},
        {153.224609f, 164.578125f}, {153.129395f, 164.264404f}, {152.982910f, 163.974121f}, {152.786133f, 163.717773f},
        {152.538574f, 163.505371f}, {152.463379f, 163.457031f}, {152.388184f, 163.413086f}, {152.311035f, 163.374268f},
        {152.232422f, 163.339844f}, {152.153320f, 163.310547f}, {152.073242f, 163.286133f}, {151.991699f, 163.266357f},
        {151.910156f, 163.251465f}, {151.827148f, 163.241211f}, {151.744141f, 163.236084f}, {151.387695f, 163.234619f},
        {151.029297f, 163.244385f}, {150.671875f, 163.252930f}, {150.316895f, 163.247803f}, {149.967285f, 163.216064f},
        {149.625000f, 163.145752f}, {149.292480f, 163.024170f}, {148.971680f, 162.838867f}, {148.665527f, 162.577393f},
        {148.375488f, 162.227051f}, {148.321289f, 162.169678f}, {148.255371f, 162.131592f}, {148.179199f, 162.109619f},
        {148.093262f, 162.100586f}, {147.999023f, 162.099854f}, {147.897949f, 162.104736f}, {147.790527f, 162.111084f},
        {147.678711f, 162.115479f}, {147.562500f, 162.114258f}, {147.443359f, 162.104004f}, {147.711914f, 162.056152f},
        {147.937012f, 161.973633f}, {148.122070f, 161.859619f}, {148.270020f, 161.717285f}, {148.384766f, 161.550049f},
        {148.469238f, 161.361572f}, {148.526367f, 161.154785f}, {148.560547f, 160.933105f}, {148.574707f, 160.699463f},
        {148.571289f, 160.458008f}, {148.565918f, 160.079346f}, {148.584961f, 159.734619f}, {148.631836f, 159.425781f},
        {148.709961f, 159.154541f}, {148.824707f, 158.922607f}, {148.978516f, 158.731445f}, {149.176270f, 158.583008f},
        {149.421387f, 158.479492f}, {149.717285f, 158.421875f}, {150.068848f, 158.412109f}, {150.315918f, 158.397705f},
        {150.550293f, 158.336426f}, {150.770996f, 158.236084f}, {150.979980f, 158.102539f}, {151.179199f, 157.942139f},
        {151.368164f, 157.761475f}, {151.548340f, 157.566406f}, {151.721191f, 157.364258f}, {151.887207f, 157.160400f},
        {152.047363f, 156.962158f}, {152.164551f, 156.783203f}, {152.222168f, 156.612061f}, {152.229004f, 156.449463f},
        {152.191895f, 156.294678f}, {152.119141f, 156.148438f}, {152.018555f, 156.010010f}, {151.897949f, 155.879883f},
        {151.764648f, 155.758057f}, {151.626465f, 155.645020f}, {151.492188f, 155.540039f}, {151.115723f, 155.246094f},
        {150.821777f, 154.998535f}, {150.609863f, 154.783691f}, {150.478516f, 154.587158f}, {150.426758f, 154.395752f},
        {150.454590f, 154.195068f}, {150.561523f, 153.970703f}, {150.746094f, 153.709473f}, {151.008301f, 153.397217f},
        {151.345703f, 153.019775f}, {151.630859f, 152.649170f}, {151.878418f, 152.213623f}, {152.086426f, 151.727295f},
        {152.251953f, 151.203125f}, {152.373535f, 150.654053f}, {152.448242f, 150.093994f}, {152.474609f, 149.535645f},
        {152.449219f, 148.992188f}, {152.371094f, 148.476807f}, {152.237305f, 148.003418f}, {152.158203f, 147.811279f},
        {152.067871f, 147.641113f}, {151.966309f, 147.494629f}, {151.854980f, 147.372559f}, {151.733887f, 147.276611f},
        {151.603027f, 147.207275f}, {151.463867f, 147.166260f}, {151.315918f, 147.154541f}, {151.160156f, 147.173828f},
        {150.997559f, 147.224609f}, {150.587402f, 147.344238f}, {150.171387f, 147.389648f}, {149.751465f, 147.382080f},
        {149.330078f, 147.344238f}, {148.907227f, 147.298828f}, {148.485352f, 147.267090f}, {148.064941f, 147.271729f},
        {147.647949f, 147.335205f}, {147.235840f, 147.479492f}, {146.830566f, 147.727051f}, {146.724121f, 147.786133f},
        {146.616699f, 147.805664f}, {146.510254f, 147.789551f}, {146.406738f, 147.742432f}, {146.307129f, 147.667969f},
        {146.213379f, 147.570557f}, {146.127441f, 147.454346f}, {146.050781f, 147.323730f}, {145.985352f, 147.182373f},
        {145.932129f, 147.035156f}, {145.882324f, 146.836182f}, {145.856934f, 146.645264f}, {145.854492f, 146.461426f},
        {145.873535f, 146.285400f}, {145.913086f, 146.116211f}, {145.970703f, 145.953857f}, {146.045410f, 145.797852f},
        {146.136230f, 145.648193f}, {146.240723f, 145.504395f}, {146.357910f, 145.366455f}, {146.455566f, 145.270264f},
        {146.556152f, 145.190674f}, {146.661621f, 145.126221f}, {146.770020f, 145.075684f}, {146.881348f, 145.037842f},
        {146.995605f, 145.012695f}, {147.112305f, 144.998047f}, {147.230957f, 144.993164f}, {147.351562f, 144.997070f},
        {147.473145f, 145.009033f}, {147.686523f, 145.030518f}, {147.896973f, 145.038330f}, {148.100586f, 145.027588f},
        {148.295898f, 144.994141f}, {148.479492f, 144.933350f}, {148.648926f, 144.840576f}, {148.800781f, 144.710938f},
        {148.933594f, 144.540771f}, {149.043457f, 144.324951f}, {149.128418f, 144.058838f}, {149.168945f, 143.793701f},
        {149.154785f, 143.572266f}, {149.093750f, 143.387695f}, {148.996094f, 143.233643f}, {148.869141f, 143.101807f},
        {148.721680f, 142.986572f}, {148.562988f, 142.880127f}, {148.400391f, 142.775879f}, {148.244141f, 142.666748f},
        {148.102051f, 142.545654f}, {148.177246f, 142.405762f}, {148.260742f, 142.308838f}, {148.350098f, 142.247314f},
        {148.445801f, 142.215332f}, {148.543945f, 142.205566f}, {148.645508f, 142.210693f}, {148.748047f, 142.224854f},
        {148.849609f, 142.239990f}, {148.949219f, 142.249756f}, {149.046387f, 142.247314f}, {149.296387f, 142.185791f},
        {149.533691f, 142.066162f}, {149.753418f, 141.895996f}, {149.950195f, 141.684082f}, {150.119629f, 141.437988f},
        {150.256348f, 141.165771f}, {150.354004f, 140.875977f}, {150.409668f, 140.576172f}, {150.416992f, 140.274414f},
        {150.370605f, 139.978760f}, {150.293457f, 139.738037f}, {150.200195f, 139.549805f}, {150.093262f, 139.410400f},
        {149.972168f, 139.315674f}, {149.839844f, 139.260742f}, {149.696777f, 139.242676f}, {149.543945f, 139.256348f},
        {149.382812f, 139.298340f}, {149.214844f, 139.363525f}, {149.041016f, 139.448730f}, {148.954590f, 139.495361f},
        {148.864746f, 139.542480f}, {148.771973f, 139.585449f}, {148.679688f, 139.619141f}, {148.587891f, 139.639160f},
        {148.499512f, 139.641113f}, {148.415039f, 139.619141f}, {148.336914f, 139.569580f}, {148.266113f, 139.486816f},
        {148.204590f, 139.366943f}, {148.172852f, 139.257812f}, {148.169922f, 139.161133f}, {148.190918f, 139.074951f},
        {148.230957f, 138.997803f}, {148.285645f, 138.927246f}, {148.350098f, 138.861572f}, {148.420410f, 138.799072f},
        {148.493164f, 138.737793f}, {148.561523f, 138.676025f}, {148.622559f, 138.611816f}, {148.763184f, 138.444824f},
        {148.895508f, 138.276611f}, {149.014160f, 138.105713f}, {149.112305f, 137.930908f}, {149.182617f, 137.750488f},
        {149.218750f, 137.563477f}, {149.213379f, 137.367920f}, {149.159180f, 137.163086f}, {149.050781f, 136.947510f},
        {148.880371f, 136.719238f}, {148.672363f, 136.965576f}, {148.448242f, 137.175293f}, {148.208984f, 137.354980f},
        {147.959473f, 137.512207f}, {147.703125f, 137.653564f}, {147.441895f, 137.786865f}, {147.180664f, 137.918457f},
        {146.921387f, 138.055908f}, {146.667480f, 138.206055f}, {146.423340f, 138.376709f}, {146.327637f, 138.436035f},
        {146.228516f, 138.471924f}, {146.126953f, 138.485596f}, {146.024414f, 138.479492f}, {145.921387f, 138.455322f},
        {145.819336f, 138.415039f}, {145.718262f, 138.360352f}, {145.620117f, 138.293457f}, {145.525879f, 138.215820f},
        {145.436035f, 138.130127f}, {145.398926f, 138.087891f}, {145.367188f, 138.042480f}, {145.340332f, 137.994141f},
        {145.319336f, 137.943604f}, {145.304199f, 137.891113f}, {145.295410f, 137.837158f}, {145.294434f, 137.782471f},
        {145.299805f, 137.727539f}, {145.312988f, 137.672119f}, {145.334473f, 137.617432f}, {145.401855f, 137.495117f},
        {145.479004f, 137.395996f}, {145.563965f, 137.318359f}, {145.655762f, 137.259766f}, {145.752441f, 137.218262f},
        {145.852539f, 137.192139f}, {145.956543f, 137.179199f}, {146.062500f, 137.177002f}, {146.168945f, 137.184082f},
        {146.273926f, 137.197998f}, {146.535156f, 137.239746f}, {146.794922f, 137.278076f}, {147.052734f, 137.307373f},
        {147.308594f, 137.321777f}, {147.562500f, 137.315674f}, {147.812500f, 137.282959f}, {148.058594f, 137.217529f},
        {148.300781f, 137.114014f}, {148.537598f, 136.966553f}, {148.769043f, 136.768799f}, {148.836914f, 136.554443f},
        {148.882324f, 136.338623f}, {148.909180f, 136.121338f}, {148.921387f, 135.903320f}, {148.921387f, 135.684326f},
        {148.913086f, 135.465088f}, {148.901367f, 135.245361f}, {148.887207f, 135.025635f}, {148.875488f, 134.805908f},
        {148.869141f, 134.586426f}, {148.862793f, 134.574951f}, {148.856934f, 134.562988f}, {148.850586f, 134.551270f},
        {148.843750f, 134.539307f}, {148.837891f, 134.527588f}, {148.832031f, 134.515869f}, {148.825195f, 134.504639f},
        {148.818359f, 134.493408f}, {148.811035f, 134.482910f}, {148.803223f, 134.472900f}, {148.729492f, 134.400391f},
        {148.642578f, 134.344971f}, {148.548340f, 134.300049f}, {148.451172f, 134.258301f}, {148.356934f, 134.213623f},
        {148.270020f, 134.158691f}, {148.195801f, 134.087158f}, {148.139648f, 133.992188f}, {148.105469f, 133.866943f},
        {148.100098f, 133.705078f}, {148.104492f, 133.662598f}, {148.111816f, 133.620605f}, {148.122559f, 133.580078f},
        {148.136719f, 133.541504f}, {148.154297f, 133.505127f}, {148.174316f, 133.471680f}, {148.198242f, 133.441162f},
        {148.224121f, 133.414062f}, {148.252930f, 133.391602f}, {148.283691f, 133.373779f}, {148.412109f, 133.334717f},
        {148.516602f, 133.344482f},

        {148.602539f, 133.392822f}, {148.674805f, 133.470215f}, {148.738281f, 133.565186f}, {148.797852f, 133.668945f},
        {148.858398f, 133.770996f}, {148.925293f, 133.860596f}, {149.003906f, 133.927734f}, {149.097656f, 133.963135f},
        {149.253906f, 133.668701f}, {149.403320f, 133.369141f}, {149.546875f, 133.064941f}, {149.684570f, 132.756836f},
        {149.815918f, 132.445801f}, {149.941406f, 132.131592f}, {150.061035f, 131.815186f}, {150.175293f, 131.497070f},
        {150.284180f, 131.177734f}, {150.387695f, 130.857666f}, {150.451172f, 130.487793f}, {150.422363f, 130.094971f},
        {150.312988f, 129.691406f}, {150.131836f, 129.288574f}, {149.889160f, 128.897949f}, {149.593750f, 128.532227f},
        {149.257812f, 128.202393f}, {148.889648f, 127.920410f}, {148.499023f, 127.698486f}, {148.096680f, 127.548340f},
        {148.038086f, 127.534180f}, {147.979492f, 127.523438f}, {147.920898f, 127.514893f}, {147.860840f, 127.508057f},
        {147.802246f, 127.502686f}, {147.742676f, 127.497803f}, {147.682617f, 127.492920f}, {147.624023f, 127.487061f},
        {147.564453f, 127.479736f}, {147.505859f, 127.470459f}, {147.423828f, 127.458496f}, {147.339355f, 127.447998f},
        {147.253418f, 127.435059f}, {147.169922f, 127.417236f}, {147.092285f, 127.390137f}, {147.023438f, 127.350586f},
        {146.965332f, 127.294922f}, {146.921875f, 127.219727f}, {146.895996f, 127.121582f}, {146.890137f, 126.997314f},
        {146.906250f, 126.873535f}, {146.940430f, 126.775391f}, {146.989258f, 126.701416f}, {147.052246f, 126.647461f},
        {147.124023f, 126.611572f}, {147.203613f, 126.590332f}, {147.287598f, 126.581299f}, {147.374023f, 126.581299f},
        {147.458984f, 126.587646f}, {147.540527f, 126.597412f}, {147.737793f, 126.612305f}, {147.923340f, 126.603027f},
        {148.097168f, 126.569824f}, {148.259277f, 126.512451f}, {148.411621f, 126.431152f}, {148.552246f, 126.325928f},
        {148.682617f, 126.196777f}, {148.803223f, 126.043701f}, {148.913086f, 125.866699f}, {149.013672f, 125.666016f},
        {149.029297f, 125.630615f}, {149.044922f, 125.594727f}, {149.058594f, 125.558105f}, {149.072754f, 125.521240f},
        {149.085449f, 125.483887f}, {149.097656f, 125.446533f}, {149.108398f, 125.408447f}, {149.119629f, 125.370361f},
        {149.129395f, 125.331787f}, {149.139160f, 125.293213f}, {149.087891f, 125.024658f}, {149.092285f, 124.840088f},
        {149.142090f, 124.723633f}, {149.227051f, 124.660645f}, {149.337891f, 124.635742f}, {149.463379f, 124.633301f},
        {149.593750f, 124.638672f}, {149.719238f, 124.636230f}, {149.829102f, 124.611084f}, {149.914551f, 124.547607f},
        {149.942871f, 124.525879f}, {149.970215f, 124.503418f}, {149.996582f, 124.479492f}, {150.021973f, 124.454590f},
        {150.046875f, 124.428223f}, {150.070801f, 124.400879f}, {150.093750f, 124.372559f}, {150.116211f, 124.343262f},
        {150.137695f, 124.312744f}, {150.158203f, 124.281494f}, {150.245117f, 124.101807f}, {150.316406f, 123.917969f},
        {150.372559f, 123.730957f}, {150.415039f, 123.540527f}, {150.445312f, 123.347412f}, {150.464355f, 123.151855f},
        {150.474609f, 122.954834f}, {150.476074f, 122.756348f}, {150.470215f, 122.556641f}, {150.458984f, 122.356689f},
        {150.424316f, 122.031006f}, {150.368652f, 121.752930f}, {150.291504f, 121.522217f}, {150.191895f, 121.337891f},
        {150.067871f, 121.200195f}, {149.919434f, 121.107910f}, {149.744629f, 121.060791f}, {149.543457f, 121.058350f},
        {149.313477f, 121.100098f}, {149.055176f, 121.185059f},

        {148.937012f, 121.230713f}, {148.822754f, 121.271484f}, {148.711426f, 121.304932f}, {148.602051f, 121.328613f},
        {148.494141f, 121.340088f}, {148.387695f, 121.336426f}, {148.281250f, 121.314941f}, {148.174805f, 121.273438f},
        {148.067383f, 121.208984f}, {147.958496f, 121.118896f}, {147.823730f, 120.998047f}, {147.683594f, 120.877197f},
        {147.542969f, 120.753906f}, {147.407715f, 120.626221f}, {147.283203f, 120.491211f}, {147.176270f, 120.346680f},
        {147.090820f, 120.190430f}, {147.033691f, 120.019775f}, {147.010254f, 119.832764f}, {147.026367f, 119.626221f},
        {147.072754f, 119.476074f}, {147.147461f, 119.372314f}, {147.245605f, 119.306885f}, {147.362305f, 119.271240f},
        {147.492676f, 119.257568f}, {147.631348f, 119.256836f}, {147.773438f, 119.260986f}, {147.915039f, 119.261719f},
        {148.051270f, 119.250000f}, {148.176270f, 119.218018f}, {148.221191f, 119.201660f}, {148.266113f, 119.185547f},
        {148.311523f, 119.169678f}, {148.356934f, 119.154053f}, {148.401855f, 119.137451f}, {148.446289f, 119.119873f},
        {148.490723f, 119.101074f}, {148.535156f, 119.080322f}, {148.578125f, 119.057373f}, {148.621582f, 119.031738f},
        {148.764160f, 118.902832f}, {148.887207f, 118.761719f}, {148.991211f, 118.609619f}, {149.077637f, 118.447266f},
        {149.148926f, 118.275635f}, {149.206055f, 118.095703f}, {149.250488f, 117.908691f}, {149.283691f, 117.714600f},
        {149.307617f, 117.515381f}, {149.323242f, 117.311279f}, {149.343750f, 116.403809f}, {149.431152f, 115.507812f},
        {149.565918f, 114.619629f}, {149.729492f, 113.735352f}, {149.904785f, 112.852295f}, {150.071777f, 111.966797f},
        {150.213867f, 111.074463f}, {150.311523f, 110.173096f}, {150.346191f, 109.258301f}, {150.300781f, 108.326660f},
        {150.241211f, 107.812012f}, {150.164062f, 107.327637f}, {150.063965f, 106.874512f}, {149.935547f, 106.453613f},
        {149.774414f, 106.066406f}, {149.575684f, 105.714111f}, {149.333496f, 105.397461f}, {149.043457f, 105.118164f},
        {148.699707f, 104.876953f}, {148.297852f, 104.675537f}, {148.196777f, 104.629883f}, {148.097656f, 104.578369f},
        {148.000977f, 104.521729f}, {147.906738f, 104.460938f}, {147.814453f, 104.395996f}, {147.723145f, 104.327148f},
        {147.634277f, 104.255127f}, {147.546387f, 104.180420f}, {147.460938f, 104.103027f}, {147.376465f, 104.023926f},
        {147.112305f, 103.797852f}, {146.845215f, 103.617676f}, {146.575195f, 103.482666f}, {146.301758f, 103.391113f},
        {146.024414f, 103.342285f}, {145.743652f, 103.333984f}, {145.458984f, 103.365234f}, {145.170898f, 103.435303f},
        {144.878906f, 103.541992f}, {144.582031f, 103.684326f}, {144.307129f, 103.814209f}, {144.051758f, 103.896240f},
        {143.814941f, 103.930664f}, {143.593262f, 103.916748f}, {143.383789f, 103.854004f}, {143.185059f, 103.742188f},
        {142.992676f, 103.580566f}, {142.805176f, 103.369141f}, {142.619629f, 103.107666f}, {142.433105f, 102.795410f},
        {142.312500f, 102.534912f}, {142.253906f, 102.303711f}, {142.246582f, 102.097900f}, {142.284180f, 101.914062f},
        {142.357910f, 101.748047f}, {142.459473f, 101.596191f}, {142.580566f, 101.454102f}, {142.713379f, 101.318604f},
        {142.849609f, 101.185547f}, {142.981934f, 101.051270f}, {143.158691f, 100.844971f}, {143.305176f, 100.638184f},
        {143.419922f, 100.429932f}, {143.499512f, 100.219238f}, {143.542480f, 100.004639f}, {143.547852f, 99.785889f},
        {143.512695f, 99.560791f},  {143.435547f, 99.329346f},  {143.313965f, 99.089844f},  {143.145996f, 98.841797f},
        {143.022461f, 98.659424f},  {142.933105f, 98.484131f},  {142.878418f, 98.317871f},  {142.858887f, 98.160889f},
        {142.874023f, 98.015137f},  {142.925781f, 97.881348f},  {143.012695f, 97.760986f},  {143.136230f, 97.654785f},
        {143.296387f, 97.563965f},  {143.493164f, 97.489990f},  {143.552734f, 97.474854f},  {143.613281f, 97.465332f},
        {143.672852f, 97.461670f},  {143.732422f, 97.464355f},  {143.790527f, 97.474365f},  {143.847656f, 97.491455f},
        {143.902832f, 97.516846f},  {143.955078f, 97.550293f},  {144.004395f, 97.592773f},  {144.049316f, 97.644531f},
        {144.090820f, 97.708252f},  {144.119141f, 97.773682f},  {144.135742f, 97.840576f},  {144.141602f, 97.908203f},
        {144.138184f, 97.975586f},  {144.126465f, 98.042969f},  {144.106934f, 98.109131f},  {144.081543f, 98.173828f},
        {144.051270f, 98.236572f},  {144.015625f, 98.296875f},  {143.913086f, 98.471436f},  {143.821777f, 98.646484f},
        {143.745117f, 98.822754f},  {143.687500f, 99.000488f},  {143.651367f, 99.179688f},  {143.639160f, 99.361328f},
        {143.655762f, 99.544678f},  {143.702148f, 99.730713f},  {143.782715f, 99.919678f},

        {143.900879f, 100.111816f}, {144.091309f, 100.389160f}, {144.281738f, 100.673828f}, {144.474609f, 100.956543f},
        {144.673828f, 101.229492f}, {144.883789f, 101.483398f}, {145.106934f, 101.709961f}, {145.347656f, 101.900879f},
        {145.609863f, 102.047119f}, {145.896973f, 102.140869f}, {146.211914f, 102.172852f}, {146.575195f, 102.155273f},
        {146.929688f, 102.104004f}, {147.275391f, 102.018311f}, {147.608398f, 101.895996f}, {147.929199f, 101.736084f},
        {148.235352f, 101.536621f}, {148.524414f, 101.295654f}, {148.795898f, 101.012695f}, {149.047363f, 100.685303f},
        {149.277832f, 100.312500f}, {149.326172f, 100.226807f}, {149.377930f, 100.137695f}, {149.430176f, 100.046387f},
        {149.479980f, 99.953369f},  {149.525879f, 99.859619f},  {149.563477f, 99.766357f},  {149.591309f, 99.673340f},
        {149.605957f, 99.581787f},  {149.605957f, 99.492676f},  {149.587891f, 99.406250f},  {149.449219f, 98.827881f},
        {149.421875f, 98.297363f},  {149.486816f, 97.807129f},  {149.625000f, 97.348633f},  {149.817871f, 96.914307f},
        {150.046387f, 96.495850f},  {150.291016f, 96.084961f},  {150.533691f, 95.674316f},  {150.754395f, 95.255615f},

        {150.935059f, 94.820801f},  {151.051270f, 94.474609f},  {151.136230f, 94.178955f},  {151.187500f, 93.928467f},
        {151.200195f, 93.716797f},  {151.170410f, 93.538330f},  {151.093750f, 93.387207f},  {150.966309f, 93.257568f},
        {150.783691f, 93.143555f},  {150.541992f, 93.039307f},  {150.237305f, 92.938477f},  {150.118164f, 92.902344f},
        {150.003418f, 92.863770f},  {149.892090f, 92.820557f},  {149.786133f, 92.770752f},  {149.685059f, 92.711914f},
        {149.590332f, 92.642578f},  {149.501465f, 92.560303f},  {149.418945f, 92.462646f},  {149.343262f, 92.347656f},
        {149.274414f, 92.213623f},  {149.195312f, 92.033691f},  {149.112305f, 91.851074f},  {149.023438f, 91.675293f},
        {148.926270f, 91.515137f},  {148.817871f, 91.380127f},  {148.696777f, 91.279785f},  {148.560547f, 91.223389f},
        {148.407227f, 91.219238f},  {148.233887f, 91.277832f},  {148.038574f, 91.407959f},  {147.849121f, 91.581055f},
        {147.689941f, 91.767334f},  {147.564941f, 91.965576f},  {147.475586f, 92.174561f},  {147.423828f, 92.393311f},
        {147.412598f, 92.620361f},  {147.444336f, 92.854980f},  {147.520996f, 93.095459f},  {147.645508f, 93.340820f},
        {147.820312f, 93.590332f},  {147.847168f, 93.618652f},  {147.874512f, 93.645996f},  {147.901855f, 93.672607f},
        {147.929688f, 93.698486f},  {147.958496f, 93.724121f},  {147.986816f, 93.748291f},  {148.016113f, 93.772461f},
        {148.045898f, 93.795654f},  {148.075684f, 93.818115f},  {148.105957f, 93.839844f},  {148.283203f, 93.947510f},
        {148.422852f, 94.065918f},  {148.527832f, 94.194336f},  {148.598145f, 94.331787f},  {148.635742f, 94.478271f},
        {148.642090f, 94.633301f},  {148.619629f, 94.796387f},  {148.568359f, 94.967041f},  {148.490723f, 95.144287f},
        {148.387695f, 95.328369f},  {148.173828f, 95.637695f},  {147.939941f, 95.900391f},  {147.690918f, 96.114502f},
        {147.428223f, 96.277344f},  {147.153809f, 96.386719f},  {146.871582f, 96.439941f},  {146.583984f, 96.434570f},
        {146.292969f, 96.368408f},  {146.001465f, 96.238525f},  {145.713379f, 96.042969f},  {145.245117f, 95.716553f},
        {144.772461f, 95.477295f},  {144.296387f, 95.315186f},  {143.816895f, 95.220703f},  {143.334473f, 95.182861f},
        {142.850586f, 95.192383f},  {142.364258f, 95.238525f},  {141.877441f, 95.311523f},  {141.388672f, 95.401611f},
        {140.900391f, 95.498291f},  {140.675293f, 95.567139f},  {140.486816f, 95.674072f},  {140.331055f, 95.815186f},
        {140.205078f, 95.985840f},  {140.105957f, 96.181641f},  {140.029297f, 96.398193f},  {139.973633f, 96.631104f},
        {139.933105f, 96.876221f},  {139.907227f, 97.129395f},  {139.890625f, 97.385254f},  {139.880371f, 97.874756f},
        {139.891113f, 98.362549f},  {139.918457f, 98.848877f},  {139.957031f, 99.334717f},  {140.001953f, 99.820068f},
        {140.046875f, 100.306152f}, {140.087891f, 100.792725f}, {140.118652f, 101.280518f}, {140.133789f, 101.770264f},
        {140.128906f, 102.261963f}, {140.103516f, 102.836182f},

        {140.061035f, 103.399414f}, {139.997070f, 103.949463f}, {139.905762f, 104.485107f}, {139.782227f, 105.003662f},
        {139.620605f, 105.503662f}, {139.415527f, 105.982422f}, {139.162109f, 106.438721f}, {138.853516f, 106.870605f},
        {138.486328f, 107.275391f}, {138.422852f, 107.340088f}, {138.362305f, 107.407715f}, {138.301758f, 107.477051f},
        {138.242188f, 107.546875f}, {138.182617f, 107.616455f}, {138.122070f, 107.684570f}, {138.058594f, 107.750000f},
        {137.993164f, 107.811768f}, {137.924316f, 107.868652f}, {137.851074f, 107.919678f}, {137.631836f, 108.033203f},
        {137.396973f, 108.111084f}, {137.154297f, 108.154541f}, {136.912598f, 108.164551f}, {136.679688f, 108.141846f},
        {136.463379f, 108.087402f}, {136.270996f, 108.001465f}, {136.112305f, 107.885986f}, {135.993652f, 107.741455f},
        {135.923828f, 107.568604f}, {135.881836f, 107.278320f}, {135.897461f, 107.046875f}, {135.961426f, 106.864990f},
        {136.064941f, 106.723145f}, {136.198242f, 106.611084f}, {136.351562f, 106.520508f}, {136.515625f, 106.440918f},
        {136.681641f, 106.363281f}, {136.839844f, 106.277832f}, {136.980469f, 106.175293f}, {137.059570f, 106.118408f},
        {137.123047f, 106.045410f}, {137.175293f, 105.960693f}, {137.219727f, 105.867676f}, {137.260254f, 105.770264f},
        {137.300781f, 105.672852f}, {137.345215f, 105.578857f}, {137.397461f, 105.492920f}, {137.461914f, 105.417969f},
        {137.541504f, 105.359131f}, {137.599609f, 105.425049f}, {137.640625f, 105.503662f}, {137.668945f, 105.591064f},
        {137.690918f, 105.683838f}, {137.709473f, 105.777832f}, {137.731934f, 105.869385f}, {137.762695f, 105.954346f},
        {137.805664f, 106.028564f}, {137.867188f, 106.088623f}, {137.952148f, 106.130615f}, {138.163086f, 106.140137f},
        {138.345703f, 106.118896f}, {138.499512f, 106.067627f}, {138.625977f, 105.987305f}, {138.725098f, 105.878174f},
        {138.796875f, 105.740723f}, {138.842773f, 105.575928f}, {138.862305f, 105.384033f}, {138.855469f, 105.165283f},
        {138.823730f, 104.920898f}, {138.810059f, 104.836426f}, {138.796875f, 104.750732f}, {138.784180f, 104.665039f},
        {138.771484f, 104.579346f}, {138.757324f, 104.493652f}, {138.743164f, 104.408936f}, {138.726074f, 104.325684f},
        {138.707031f, 104.244141f}, {138.685059f, 104.164795f}, {138.659668f, 104.088135f}, {138.488770f, 103.526123f},
        {138.377441f, 102.966553f}, {138.319824f, 102.409180f}, {138.307617f, 101.853516f}, {138.333496f, 101.299316f},
        {138.390137f, 100.746582f}, {138.471191f, 100.194824f}, {138.568359f, 99.643799f},  {138.674805f, 99.093018f},
        {138.782715f, 98.542480f},  {138.807617f, 98.413574f},  {138.828613f, 98.287109f},  {138.846191f, 98.162354f},
        {138.857422f, 98.038818f},  {138.860352f, 97.916992f},  {138.854004f, 97.795654f},  {138.837402f, 97.675293f},
        {138.806152f, 97.554688f},  {138.761230f, 97.434570f},  {138.699707f, 97.313965f},  {138.456055f, 96.989014f},
        {138.123047f, 96.681396f},  {137.719727f, 96.396973f},  {137.264160f, 96.141113f},  {136.774902f, 95.920166f},
        {136.270508f, 95.739502f},  {135.768555f, 95.604980f},  {135.288574f, 95.522705f},  {134.849121f, 95.498291f},
        {134.467773f, 95.537598f},  {134.104004f, 95.628174f},  {133.739746f, 95.738525f},  {133.374512f, 95.855713f},
        {133.009277f, 95.967285f},  {132.641602f, 96.061035f},  {132.272461f, 96.123779f},  {131.901367f, 96.144043f},
        {131.527832f, 96.108154f},  {131.151367f, 96.004150f},  {130.771973f, 95.819092f},  {130.689453f, 95.773438f},
        {130.603516f, 95.730469f},  {130.517090f, 95.686768f},  {130.432617f, 95.638428f},  {130.351562f, 95.582520f},
        {130.276855f, 95.514648f},  {130.209473f, 95.431885f},  {130.152832f, 95.330078f},  {130.108398f, 95.206055f},
        {130.079102f, 95.055908f},  {130.301758f, 94.903809f},  {130.529297f, 94.785400f},  {130.759766f, 94.697510f},
        {130.994141f, 94.637451f},  {131.230957f, 94.601074f},  {131.471191f, 94.586670f},  {131.713379f, 94.590088f},
        {131.958008f, 94.608643f},  {132.203613f, 94.639404f},  {132.451172f, 94.678955f},  {132.614746f, 94.698975f},
        {132.774414f, 94.701416f},  {132.928223f, 94.685791f},  {133.075195f, 94.650635f},  {133.215820f, 94.595703f},
        {133.347656f, 94.519531f},  {133.471191f, 94.422119f},  {133.585449f, 94.301270f},  {133.689453f, 94.157471f},
        {133.782227f, 93.989014f},  {133.858887f, 93.818848f},  {133.923828f, 93.647705f},  {133.973145f, 93.476562f},
        {134.004883f, 93.306152f},  {134.014648f, 93.137451f},  {134.000000f, 92.971680f},  {133.957520f, 92.809082f},
        {133.883789f, 92.650879f},  {133.776855f, 92.498047f},  {133.631836f, 92.351318f},  {133.518066f, 92.401367f},
        {133.428711f, 92.473633f},  {133.358887f, 92.564453f},  {133.302734f, 92.670654f},  {133.255859f, 92.787598f},
        {133.212402f, 92.912598f},  {133.167969f, 93.041260f},  {133.116699f, 93.170654f},  {133.053223f, 93.296387f},
        {132.973633f, 93.415039f},  {132.908203f, 93.330322f},  {132.854980f, 93.232666f},  {132.810547f, 93.126221f},
        {132.771973f, 93.014893f},  {132.733398f, 92.902832f},  {132.692383f, 92.794189f},  {132.644043f, 92.692139f},
        {132.585938f, 92.601807f},  {132.512695f, 92.526367f},  {132.421387f, 92.470459f},  {132.165527f, 92.367188f},
        {131.908691f, 92.269775f},  {131.651367f, 92.182861f},  {131.393555f, 92.110596f},  {131.134277f, 92.058105f},
        {130.873535f, 92.028564f},  {130.611328f, 92.027344f},  {130.347168f, 92.058105f},  {130.081055f, 92.125977f},
        {129.812012f, 92.234375f},  {129.791016f, 92.541748f},  {129.737793f, 92.826416f},  {129.653809f, 93.089111f},
        {129.539062f, 93.329102f},  {129.392578f, 93.546875f},  {129.214355f, 93.741943f},  {129.004883f, 93.915039f},
        {128.764648f, 94.065674f},  {128.492676f, 94.193848f},  {128.189453f, 94.299805f},  {128.130859f, 94.315918f},
        {128.073242f, 94.330566f},  {128.014648f, 94.344482f},  {127.955566f, 94.357666f},  {127.897461f, 94.371338f},
        {127.838867f, 94.385498f},  {127.781250f, 94.401123f},  {127.723633f, 94.418701f},  {127.666504f, 94.438477f},
        {127.608887f, 94.461182f},  {127.528320f, 94.498291f},  {127.449707f, 94.539795f},  {127.375000f, 94.585938f},
        {127.305664f, 94.638184f},  {127.242188f, 94.697754f},  {127.187012f, 94.765625f},  {127.140625f, 94.842529f},
        {127.105469f, 94.929688f},  {127.081543f, 95.028076f},  {127.070801f, 95.138916f},  {127.075195f, 95.251953f},
        {127.093750f, 95.354248f},  {127.125000f, 95.445801f},  {127.167969f, 95.527588f},  {127.221191f, 95.600586f},
        {127.281738f, 95.665039f},  {127.349609f, 95.721436f},  {127.422363f, 95.771484f},  {127.499512f, 95.814697f},
        {127.578613f, 95.852295f},  {127.746094f, 95.925781f},  {127.913086f, 95.998779f},  {128.080566f, 96.072510f},
        {128.246582f, 96.147217f},  {128.412598f, 96.223877f},  {128.578125f, 96.302734f},  {128.742676f, 96.384766f},
        {128.906250f, 96.470215f},  {129.069336f, 96.560303f},  {129.231445f, 96.655273f},  {129.384766f, 96.756836f},
        {129.513672f, 96.862061f},  {129.617676f, 96.971680f},  {129.694824f, 97.088135f},  {129.746094f, 97.212402f},
        {129.769043f, 97.345215f},  {129.764648f, 97.489014f},  {129.731934f, 97.644775f},  {129.669434f, 97.813965f},
        {129.576660f, 97.997559f},  {129.395508f, 98.356934f},  {129.249023f, 98.722168f},  {129.135742f, 99.093018f},
        {129.053223f, 99.469482f},  {128.999023f, 99.852051f},  {128.970215f, 100.240967f}, {128.966309f, 100.635742f},
        {128.983887f, 101.036865f}, {129.020020f, 101.444824f}, {129.073730f, 101.858887f}, {129.128906f, 102.380859f},
        {129.132812f, 102.847168f}, {129.083984f, 103.260010f}, {128.982422f, 103.621582f}, {128.828125f, 103.934082f},
        {128.620605f, 104.198486f}, {128.358398f, 104.418213f}, {128.041504f, 104.594238f}, {127.669922f, 104.729248f},
        {127.243164f, 104.824707f}, {127.106934f, 104.847900f}, {126.973633f, 104.874023f}, {126.844727f, 104.906006f},
        {126.722168f, 104.947998f}, {126.608398f, 105.002686f}, {126.503906f, 105.073486f}, {126.410645f, 105.164551f},
        {126.330566f, 105.278076f}, {126.265137f, 105.418701f}, {126.215820f, 105.589111f}, {126.185059f, 105.775635f},
        {126.176758f, 105.953857f}, {126.188965f, 106.124023f}, {126.219727f, 106.285400f}, {126.269043f, 106.438965f},
        {126.334473f, 106.583984f}, {126.415039f, 106.721191f}, {126.509277f, 106.850098f}, {126.616699f, 106.970947f},
        {126.733887f, 107.083740f}, {127.311523f, 107.542969f}, {127.903320f, 107.915771f}, {128.508301f, 108.208496f},
        {129.125000f, 108.426025f}, {129.751953f, 108.574463f}, {130.388184f, 108.659424f}, {131.031738f, 108.686523f},
        {131.681641f, 108.660889f}, {132.337402f, 108.588867f}, {132.996094f, 108.475586f}, {133.248535f, 108.376465f},
        {133.458008f, 108.196533f}, {133.623535f, 107.947754f}, {133.743164f, 107.641846f}, {133.816406f, 107.291260f},
        {133.841797f, 106.907959f}, {133.817383f, 106.504150f}, {133.743164f, 106.091309f}, {133.616699f, 105.682373f},
        {133.437988f, 105.288574f}, {133.318848f, 105.068848f}, {133.201660f, 104.849609f}, {133.089355f, 104.628906f},
        {132.984863f, 104.405762f}, {132.889648f, 104.178467f}, {132.808105f, 103.945801f}, {132.742188f, 103.705811f},
        {132.693359f, 103.457764f}, {132.666016f, 103.199463f}, {132.662598f, 102.930176f}, {132.667969f, 102.769287f},
        {132.676758f, 102.604736f}, {132.691406f, 102.441162f}, {132.715820f, 102.282959f}, {132.753418f, 102.134521f},
        {132.807129f, 102.000488f}, {132.879883f, 101.884766f}, {132.975586f, 101.791992f}, {133.097656f, 101.727051f},
        {133.248535f, 101.693115f}, {133.384277f, 101.698730f}, {133.495117f, 101.739746f}, {133.583008f, 101.811523f},
        {133.653809f, 101.908936f}, {133.708984f, 102.025879f}, {133.754883f, 102.157715f}, {133.792969f, 102.298828f},
        {133.829102f, 102.443604f}, {133.865234f, 102.586670f}, {133.906250f, 102.722900f}, {134.104980f, 103.394775f},
        {134.258789f, 104.081787f}, {134.382324f, 104.779053f}, {134.488770f, 105.482666f}, {134.592285f, 106.187256f},
        {134.706055f, 106.888916f}, {134.843750f, 107.582764f}, {135.018555f, 108.264648f}, {135.245605f, 108.930176f},
        {135.538086f, 109.573975f}, {135.617188f, 109.731201f}, {135.693359f, 109.890137f}, {135.768066f, 110.050537f},
        {135.842773f, 110.210449f}, {135.918945f, 110.369141f}, {135.998047f, 110.525879f}, {136.082520f, 110.678955f},
        {136.172363f, 110.828369f}, {136.270508f, 110.972168f}, {136.377930f, 111.110107f}, {136.528809f, 111.291748f},
        {136.675293f, 111.476074f}, {136.817871f, 111.664062f}, {136.954590f, 111.857178f}, {137.084961f, 112.056396f},
        {137.208496f, 112.263184f}, {137.323242f, 112.478516f}, {137.429199f, 112.704102f}, {137.524414f, 112.941162f},
        {137.609863f, 113.190674f}, {137.718262f, 113.493408f}, {137.839844f, 113.741943f}, {137.976074f, 113.937500f},
        {138.127441f, 114.082764f}, {138.295410f, 114.179199f}, {138.480957f, 114.228760f}, {138.685059f, 114.232910f},
        {138.909668f, 114.194092f}, {139.155273f, 114.113525f}, {139.422852f, 113.993652f}, {139.786133f, 113.802734f},
        {140.132324f, 113.596436f}, {140.456543f, 113.368652f}, {140.754395f, 113.114746f}, {141.020996f, 112.828369f},
        {141.250488f, 112.504395f}, {141.439941f, 112.137207f}, {141.583008f, 111.721191f}, {141.675293f, 111.251465f},
        {141.711914f, 110.721680f}, {141.722656f, 110.560547f}, {141.749023f, 110.423584f}, {141.791016f, 110.312012f},
        {141.846191f, 110.227783f}, {141.915039f, 110.172363f}, {141.995117f, 110.147461f}, {142.086914f, 110.154541f},
        {142.188477f, 110.195312f}, {142.299316f, 110.270996f}, {142.417969f, 110.383789f}, {142.542480f, 110.516357f},
        {142.667969f, 110.648682f}, {142.791992f, 110.782715f}, {142.912598f, 110.920410f}, {143.026855f, 111.064453f},
        {143.133301f, 111.215576f}, {143.229492f, 111.376465f}, {143.313965f, 111.548828f}, {143.383789f, 111.734863f},
        {143.437500f, 111.936523f}, {143.495117f, 112.176270f}, {143.563477f, 112.408203f}, {143.641602f, 112.633057f},
        {143.729980f, 112.850830f}, {143.828613f, 113.061279f}, {143.935547f, 113.264893f}, {144.052246f, 113.462402f},
        {144.178223f, 113.653320f}, {144.312500f, 113.838135f}, {144.455566f, 114.017334f}, {144.507812f, 114.077881f},
        {144.562012f, 114.138916f}, {144.616211f, 114.201904f}, {144.667969f, 114.266846f}, {144.714844f, 114.333984f},
        {144.753418f, 114.404297f}, {144.783203f, 114.478027f}, {144.800781f, 114.555908f}, {144.803223f, 114.638428f},
        {144.789551f, 114.726074f}, {144.750977f, 114.830566f}, {144.700684f, 114.911133f}, {144.639648f, 114.970215f},
        {144.569824f, 115.011963f}, {144.493164f, 115.039307f}, {144.411621f, 115.055420f}, {144.326660f, 115.064209f},
        {144.240723f, 115.068359f}, {144.155762f, 115.072021f}, {144.072754f, 115.078125f}, {143.978027f, 115.085938f},
        {143.883301f, 115.091797f}, {143.787598f, 115.096436f}, {143.692871f, 115.101318f}, {143.597168f, 115.107422f},
        {143.502441f, 115.115967f}, {143.408203f, 115.128662f}, {143.314453f, 115.146240f}, {143.220703f, 115.170654f},
        {143.128906f, 115.202637f}, {142.965820f, 115.280273f}, {142.826172f, 115.376709f}, {142.707031f, 115.490479f},
        {142.607910f, 115.620361f}, {142.526855f, 115.764648f}, {142.461914f, 115.922119f}, {142.411621f, 116.091064f},
        {142.374512f, 116.270264f}, {142.349121f, 116.458740f}, {142.333984f, 116.654785f}, {142.330566f, 116.769043f},
        {142.330566f, 116.884033f}, {142.333008f, 116.999023f}, {142.335938f, 117.114258f}, {142.337402f, 117.229492f},
        {142.335938f, 117.344238f}, {142.329102f, 117.458252f}, {142.314941f, 117.571289f}, {142.292480f, 117.683350f},
        {142.259277f, 117.793945f}, {142.224121f, 117.889648f}, {142.184570f, 117.983398f}, {142.140625f, 118.072510f},
        {142.091797f, 118.155273f}, {142.037598f, 118.228760f}, {141.977539f, 118.291260f}, {141.910156f, 118.340088f},
        {141.835449f, 118.373047f}, {141.752441f, 118.387939f}, {141.661133f, 118.382324f}, {141.569336f, 118.355713f},
        {141.493164f, 118.311523f}, {141.431152f, 118.252197f}, {141.382324f, 118.179932f}, {141.343262f, 118.096924f},
        {141.313965f, 118.004883f}, {141.291992f, 117.906982f}, {141.276367f, 117.805176f}, {141.264160f, 117.701416f},
        {141.254883f, 117.598389f}, {141.247559f, 117.391357f}, {141.254883f, 117.180176f}, {141.269531f, 116.967529f},
        {141.281738f, 116.755615f}, {141.285156f, 116.545898f}, {141.271484f, 116.340820f}, {141.231934f, 116.142578f},
        {141.159668f, 115.952881f}, {141.045898f, 115.774170f}, {140.882812f, 115.608643f}, {140.683105f, 115.467041f},
        {140.481445f, 115.367920f}, {140.276367f, 115.305420f}, {140.068848f, 115.273193f}, {139.860352f, 115.264893f},
        {139.649902f, 115.275146f}, {139.438965f, 115.297607f}, {139.227051f, 115.325928f}, {139.014648f, 115.354980f},
        {138.802734f, 115.377441f}, {138.535156f, 115.418457f}, {138.301270f, 115.493164f}, {138.101074f, 115.600830f},
        {137.932129f, 115.740479f}, {137.792969f, 115.911133f}, {137.682129f, 116.111572f}, {137.598145f, 116.340576f},
        {137.540039f, 116.597412f}, {137.505859f, 116.881592f}, {137.494141f, 117.191162f}, {137.495605f, 117.536865f},
        {137.499023f, 117.883057f}, {137.504395f, 118.229248f}, {137.510254f, 118.575439f}, {137.514160f, 118.921631f},
        {137.516602f, 119.267334f}, {137.515137f, 119.612793f}, {137.508301f, 119.957764f}, {137.495605f, 120.302002f},
        {137.474609f, 120.645752f}, {137.437500f, 121.134033f}, {137.396973f, 121.622314f}, {137.351074f, 122.110107f},
        {137.300781f, 122.596924f}, {137.244629f, 123.083008f}, {137.182617f, 123.567871f}, {137.113281f, 124.051758f},
        {137.036133f, 124.534180f}, {136.951172f, 125.014648f}, {136.856934f, 125.493408f}, {136.823730f, 125.663330f},
        {136.796387f, 125.833984f}, {136.773926f, 126.005127f}, {136.757812f, 126.176758f}, {136.746094f, 126.348633f},
        {136.740234f, 126.520752f}, {136.739258f, 126.692871f}, {136.744629f, 126.864990f}, {136.755859f, 127.036865f},
        {136.772949f, 127.208496f}, {136.797363f, 127.558350f}, {136.790039f, 127.894043f}, {136.753906f, 128.217529f},
        {136.692383f, 128.530273f}, {136.607910f, 128.833496f}, {136.503906f, 129.129395f}, {136.382812f, 129.419189f},
        {136.248535f, 129.704590f}, {136.104004f, 129.987061f}, {135.950684f, 130.268311f}, {135.853027f, 130.426270f},
        {135.755859f, 130.549072f}, {135.659180f, 130.637207f}, {135.564453f, 130.691650f}, {135.470215f, 130.712891f},
        {135.377930f, 130.701416f}, {135.288086f, 130.657715f}, {135.201172f, 130.582275f}, {135.117188f, 130.475830f},
        {135.037109f, 130.338867f}, {134.889160f, 130.036377f}, {134.747559f, 129.728271f}, {134.605469f, 129.422607f},
        {134.456055f, 129.127197f}, {134.292480f, 128.850098f}, {134.107910f, 128.599854f}, {133.895996f, 128.384521f},
        {133.648438f, 128.211670f}, {133.359375f, 128.089844f}, {133.022461f, 128.026855f}, {132.980957f, 128.016113f},
        {132.944824f, 127.991943f}, {132.912109f, 127.956299f}, {132.885742f, 127.911621f}, {132.863281f, 127.859375f},
        {132.846191f, 127.801270f}, {132.834473f, 127.739502f}, {132.829102f, 127.676025f}, {132.829102f, 127.612061f},
        {132.834961f, 127.550293f}, {132.854492f, 127.465332f}, {132.884277f, 127.391846f}, {132.923340f, 127.330566f},
        {132.968750f, 127.280762f}, {133.019531f, 127.242920f}, {133.073730f, 127.216553f}, {133.129395f, 127.202148f},
        {133.185059f, 127.199219f}, {133.238770f, 127.208008f}, {133.289551f, 127.228271f}, {133.595215f, 127.357178f},
        {133.887207f, 127.411133f}, {134.167969f, 127.401367f}, {134.438477f, 127.340332f}, {134.701660f, 127.238770f},
        {134.958984f, 127.108643f}, {135.213379f, 126.961426f}, {135.465820f, 126.809082f}, {135.719238f, 126.662598f},
        {135.975586f, 126.534424f}, {136.224121f, 126.391602f}, {136.433594f, 126.209473f}, {136.600586f, 125.994629f},
        {136.724121f, 125.753662f}, {136.803223f, 125.493652f}, {136.835449f, 125.221436f}, {136.819824f, 124.944092f},
        {136.753418f, 124.668213f}, {136.635254f, 124.401367f}, {136.463867f, 124.149658f}, {136.231934f, 123.860107f},
        {136.005371f, 123.564941f}, {135.783203f, 123.265381f}, {135.563477f, 122.962646f}, {135.345703f, 122.658936f},
        {135.127930f, 122.354736f}, {134.909668f, 122.052002f}, {134.688477f, 121.751953f}, {134.463867f, 121.456055f},
        {134.233398f, 121.165771f}, {133.896973f, 120.819336f}, {133.502441f, 120.529541f}, {133.062500f, 120.298340f},
        {132.589844f, 120.127197f}, {132.098145f, 120.018066f}, {131.599121f, 119.973145f}, {131.106445f, 119.994141f},
        {130.633301f, 120.083008f}, {130.192383f, 120.241455f}, {129.796387f, 120.471680f}, {129.648926f, 120.596924f},
        {129.541992f, 120.729004f}, {129.470215f, 120.867188f}, {129.430176f, 121.010498f}, {129.415527f, 121.159668f},
        {129.422852f, 121.313721f}, {129.447754f, 121.472656f}, {129.484375f, 121.635498f}, {129.529297f, 121.802734f},
        {129.577148f, 121.973389f}, {129.655273f, 122.217285f}, {129.746094f, 122.461182f}, {129.839355f, 122.706055f},
        {129.924805f, 122.952148f}, {129.991699f, 123.199951f}, {130.029297f, 123.449463f}, {130.026855f, 123.701172f},
        {129.974609f, 123.956055f}, {129.861328f, 124.213623f}, {129.676758f, 124.475098f}, {129.653320f, 124.510498f},
        {129.632324f, 124.546387f}, {129.611816f, 124.583496f}, {129.593262f, 124.621094f}, {129.575684f, 124.659424f},
        {129.559082f, 124.698975f}, {129.543945f, 124.738770f}, {129.529785f, 124.779785f}, {129.517090f, 124.821289f},
        {129.505371f, 124.863525f}, {129.612793f, 125.305176f}, {129.709961f, 125.746338f}, {129.796875f, 126.188965f},
        {129.873047f, 126.632568f}, {129.935547f, 127.079346f}, {129.985352f, 127.529541f}, {130.020020f, 127.984131f},
        {130.039062f, 128.444336f}, {130.041504f, 128.910400f}, {130.025879f, 129.383545f}, {130.035156f, 129.707520f},
        {130.098633f, 129.984619f}, {130.211914f, 130.215088f}, {130.371582f, 130.399902f}, {130.574707f, 130.539551f},
        {130.817383f, 130.634521f}, {131.096680f, 130.685303f}, {131.408203f, 130.692383f}, {131.749023f, 130.656494f},
        {132.115723f, 130.577881f}, {132.273926f, 130.526123f}, {132.438477f, 130.460449f}, {132.605957f, 130.395264f},
        {132.770020f, 130.344971f}, {132.926270f, 130.324219f}, {133.069824f, 130.347412f}, {133.195312f, 130.428955f},
        {133.297363f, 130.583008f}, {133.372070f, 130.824219f}, {133.413574f, 131.167236f}, {133.419434f, 131.373291f},
        {133.422852f, 131.579102f}, {133.423828f, 131.784668f}, {133.423828f, 131.990479f}, {133.423828f, 132.196045f},
        {133.423828f, 132.402100f}, {133.425781f, 132.607666f}, {133.429199f, 132.812988f}, {133.436035f, 133.018555f},
        {133.446777f, 133.223389f}, {133.638184f, 133.906250f}, {133.772461f, 134.594482f}, {133.858398f, 135.287598f},
        {133.906250f, 135.984375f}, {133.924316f, 136.684082f}, {133.923340f, 137.385254f}, {133.911621f, 138.087891f},
        {133.898926f, 138.790771f}, {133.894531f, 139.492188f}, {133.908203f, 140.192383f}, {133.911621f, 140.336182f},
        {133.913086f, 140.479736f}, {133.912109f, 140.623535f}, {133.911621f, 140.767822f}, {133.910645f, 140.911621f},
        {133.910645f, 141.055420f}, {133.912109f, 141.198975f}, {133.916992f, 141.342529f}, {133.924316f, 141.486084f},
        {133.936523f, 141.629150f}, {133.949219f, 141.758545f}, {133.963379f, 141.889160f}, {133.981445f, 142.018066f},
        {134.006348f, 142.142578f}, {134.040039f, 142.260742f}, {134.086426f, 142.368896f}, {134.146484f, 142.465332f},
        {134.223633f, 142.546875f}, {134.320801f, 142.610840f}, {134.440918f, 142.654541f}, {134.555664f, 142.674072f},
        {134.664062f, 142.673584f}, {134.765137f, 142.654785f}, {134.859375f, 142.617676f}, {134.946289f, 142.563477f},
        {135.025391f, 142.492920f}, {135.097656f, 142.407227f}, {135.162598f, 142.307129f}, {135.220215f, 142.193115f},
        {135.270020f, 142.066406f}, {135.144531f, 142.477539f}, {135.041992f, 142.897217f}, {134.953125f, 143.322754f},
        {134.871094f, 143.751465f}, {134.787109f, 144.181396f}, {134.694336f, 144.610352f}, {134.584961f, 145.035400f},
        {134.451172f, 145.454834f}, {134.285156f, 145.865967f}, {134.079102f, 146.266602f}, {133.964844f, 146.504639f},
        {133.887207f, 146.760254f}, {133.845215f, 147.027832f}, {133.838867f, 147.303711f}, {133.867188f, 147.582520f},
        {133.930664f, 147.860352f}, {134.027832f, 148.133057f}, {134.158691f, 148.395020f}, {134.322266f, 148.643066f},
        {134.518555f, 148.871582f}, {134.669434f, 149.035156f}, {134.814453f, 149.207031f}, {134.953125f, 149.385010f},
        {135.087402f, 149.567139f}, {135.219238f, 149.751953f}, {135.350098f, 149.937256f}, {135.480957f, 150.121582f},
        {135.613770f, 150.302490f}, {135.749023f, 150.478516f}, {135.889160f, 150.647949f}, {136.092285f, 150.903076f},
        {136.241699f, 151.139160f}, {136.340332f, 151.359375f}, {136.389160f, 151.567383f}, {136.389648f, 151.766846f},
        {136.344238f, 151.961426f}, {136.253906f, 152.155029f}, {136.121582f, 152.350830f}, {135.948242f, 152.552734f},
        {135.735352f, 152.764160f}, {135.252441f, 153.231689f}, {134.879883f, 153.633057f}, {134.620117f, 153.981689f},
        {134.473145f, 154.291016f}, {134.439453f, 154.575195f}, {134.520508f, 154.846680f}, {134.716309f, 155.120117f},
        {135.027832f, 155.408447f}, {135.456543f, 155.725098f}, {136.002441f, 156.083740f}, {136.114258f, 156.157227f},
        {136.221191f, 156.232178f}, {136.321777f, 156.311523f}, {136.413574f, 156.396484f}, {136.495117f, 156.489014f},
        {136.564453f, 156.590820f}, {136.619629f, 156.703857f}, {136.659668f, 156.829834f}, {136.682617f, 156.970703f},
        {136.686523f, 157.127930f}, {136.666992f, 157.314209f}, {136.625000f, 157.471191f}, {136.562500f, 157.602051f},
        {136.482910f, 157.709473f}, {136.387695f, 157.796875f}, {136.280762f, 157.867432f}, {136.162598f, 157.925049f},
        {136.038086f, 157.971924f}, {135.907227f, 158.011719f}, {135.774902f, 158.047852f}, {135.611816f, 158.088379f},
        {135.449219f, 158.123779f}, {135.287598f, 158.153564f}, {135.126465f, 158.176758f}, {134.963867f, 158.192627f},
        {134.800781f, 158.200195f}, {134.637207f, 158.198730f}, {134.471191f, 158.187744f}, {134.304199f, 158.166504f},
        {134.133789f, 158.133545f}, {133.710938f, 158.054443f}, {133.335449f, 158.017334f}, {133.005859f, 158.022949f},
        {132.720215f, 158.070557f}, {132.476074f, 158.161377f}, {132.272461f, 158.294678f}, {132.106934f, 158.471436f},
        {131.977539f, 158.691650f}, {131.882812f, 158.956055f}, {131.820801f, 159.263672f}, {131.791504f, 159.716797f},
        {131.827148f, 160.173096f}, {131.922363f, 160.623047f}, {132.070312f, 161.056152f}, {132.267090f, 161.462402f},
        {132.506836f, 161.831787f}, {132.782715f, 162.153809f}, {133.090332f, 162.418701f}, {133.423828f, 162.615967f},
        {133.777832f, 162.735840f}, {133.954102f, 162.767822f}, {134.131836f, 162.789307f}, {134.309570f, 162.802734f},
        {134.488281f, 162.809570f}, {134.666504f, 162.812012f}, {134.845215f, 162.811523f}, {135.023926f, 162.810791f},
        {135.203125f, 162.811523f}, {135.381836f, 162.815430f}, {135.560059f, 162.824951f}, {135.777344f, 162.852295f},
        {135.974609f, 162.903076f}, {136.151367f, 162.978271f}, {136.306152f, 163.078857f}, {136.438477f, 163.205322f},
        {136.546387f, 163.358887f}, {136.629883f, 163.540283f}, {136.688477f, 163.750000f}, {136.719238f, 163.989746f},
        {136.723633f, 164.259521f}, {136.696289f, 164.523193f}, {136.637207f, 164.731201f}, {136.550781f, 164.889893f},
        {136.441406f, 165.006104f}, {136.312012f, 165.086914f}, {136.166504f, 165.138672f}, {136.008789f, 165.168457f},
        {135.844238f, 165.183105f}, {135.674316f, 165.188965f}, {135.505371f, 165.192871f}, {135.374023f, 165.194092f},
        {135.243164f, 165.190430f}, {135.112305f, 165.182861f}, {134.981445f, 165.171631f}, {134.851562f, 165.157227f},
        {134.721191f, 165.141357f}, {134.591797f, 165.124023f}, {134.461426f, 165.106201f}, {134.331543f, 165.088623f},
        {134.201172f, 165.071533f}, {134.088867f, 165.060791f}, {133.977539f, 165.057617f}, {133.867676f, 165.063965f},
        {133.762207f, 165.081787f}, {133.661621f, 165.113525f}, {133.567871f, 165.160645f}, {133.482910f, 165.225342f},
        {133.406738f, 165.309814f}, {133.342285f, 165.416016f}, {133.291504f, 165.545898f}, {133.254395f, 165.705078f},
        {133.245117f, 165.852295f}, {133.260254f, 165.989014f}, {133.296875f, 166.116455f}, {133.351562f, 166.234863f},
        {133.420410f, 166.345703f}, {133.500977f, 166.450195f}, {133.589844f, 166.548340f}, {133.683594f, 166.642090f},
        {133.778320f, 166.731934f}, {133.901855f, 166.833008f}, {134.029297f, 166.913330f}, {134.160645f, 166.975830f},
        {134.295410f, 167.022949f}, {134.433105f, 167.057129f}, {134.572754f, 167.080811f}, {134.714355f, 167.096436f},
        {134.857422f, 167.105957f}, {135.000488f, 167.112549f}, {135.144043f, 167.118164f}, {135.285645f, 167.122559f},
        {135.427246f, 167.124268f}, {135.569336f, 167.125488f}, {135.710938f, 167.128662f}, {135.852051f, 167.135254f},
        {135.993164f, 167.147949f}, {136.133789f, 167.168457f}, {136.273926f, 167.199219f}, {136.414062f, 167.241699f},
        {136.553223f, 167.298584f}, {136.852051f, 167.448730f}, {137.098145f, 167.599365f}, {137.293457f, 167.756348f},
        {137.438965f, 167.925049f}, {137.536133f, 168.112305f}, {137.587402f, 168.323730f}, {137.593750f, 168.565430f},
        {137.556641f, 168.843506f}, {137.479004f, 169.164062f}, {137.360352f, 169.532959f}, {137.298340f, 169.733398f},
        {137.260254f, 169.913818f}, {137.245605f, 170.075439f}, {137.255371f, 170.220947f}, {137.289062f, 170.351074f},
        {137.347656f, 170.467773f}, {137.431641f, 170.572754f}, {137.540527f, 170.667725f}, {137.674805f, 170.754395f},
        {137.835449f, 170.833740f}, {138.421875f, 171.111084f}, {138.892578f, 171.382812f}, {139.251953f, 171.662354f},
        {139.503418f, 171.962891f}, {139.650391f, 172.297363f}, {139.697266f, 172.679932f}, {139.647461f, 173.123047f},
        {139.504395f, 173.640869f}, {139.273438f, 174.246094f}, {138.956543f, 174.952148f}, {138.773926f, 175.447998f},
        {138.658203f, 176.006836f}, {138.604980f, 176.608398f}, {138.612793f, 177.232910f}, {138.679199f, 177.860840f},
        {138.800781f, 178.472168f}, {138.975098f, 179.047363f}, {139.201172f, 179.566406f}, {139.475098f, 180.009521f},
        {139.794434f, 180.357178f}, {139.975098f, 180.537598f}, {140.109863f, 180.725098f}, {140.202637f, 180.919434f},
        {140.259766f, 181.119629f}, {140.287109f, 181.325195f}, {140.291016f, 181.535889f}, {140.274902f, 181.750732f},
        {140.246582f, 181.969727f}, {140.210449f, 182.191650f}, {140.172852f, 182.416016f}, {140.115723f, 182.698486f},
        {140.036621f, 183.003662f}, {139.942871f, 183.323242f}, {139.841309f, 183.648926f}, {139.737793f, 183.973389f},
        {139.640137f, 184.287842f}, {139.553711f, 184.584717f}, {139.486328f, 184.855469f}, {139.444336f, 185.092285f},
        {139.434570f, 185.287354f}, {139.496094f, 184.934082f}, {139.502441f, 184.537354f}, {139.463867f, 184.105713f},
        {139.387695f, 183.648682f}, {139.285645f, 183.174805f}, {139.165039f, 182.693115f}, {139.036133f, 182.212891f},
        {138.907715f, 181.742676f}, {138.790527f, 181.291748f}, {138.691895f, 180.868652f}, {138.637695f, 180.659668f},
        {138.568359f, 180.470703f}, {138.483887f, 180.301514f}, {138.384277f, 180.151611f}, {138.270996f, 180.021240f},
        {138.144043f, 179.909180f}, {138.002930f, 179.816406f}, {137.849609f, 179.741699f}, {137.683594f, 179.685059f},
        {137.505371f, 179.646484f}, {137.149902f, 179.710938f}, {136.845703f, 179.792480f}, {136.589355f, 179.895752f},
        {136.376953f, 180.026611f}, {136.204590f, 180.190186f}, {136.069336f, 180.391113f}, {135.966797f, 180.635498f},
        {135.894531f, 180.927734f}, {135.847168f, 181.273438f}, {135.822754f, 181.677734f}, {135.810547f, 182.067139f},
        {135.797852f, 182.455078f}, {135.782227f, 182.840088f}, {135.757812f, 183.220459f}, {135.722656f, 183.595459f},
        {135.671387f, 183.962891f}, {135.600586f, 184.321777f}, {135.507324f, 184.670410f}, {135.386230f, 185.007812f},
        {135.234375f, 185.332031f}, {135.188965f, 184.974854f}, {135.152344f, 184.610107f}, {135.124023f, 184.238770f},
        {135.102051f, 183.861328f}, {135.083984f, 183.479004f}, {135.069336f, 183.092529f}, {135.054688f, 182.703125f},
        {135.040039f, 182.311523f}, {135.022949f, 181.918457f}, {135.000977f, 181.525391f}, {134.913086f, 180.883789f},
        {134.734863f, 180.283936f}, {134.476562f, 179.733643f}, {134.149414f, 179.242676f}, {133.762207f, 178.818359f},
        {133.325195f, 178.470215f}, {132.847656f, 178.206543f}, {132.341309f, 178.035889f}, {131.813965f, 177.966797f},
        {131.276367f, 178.007812f}, {131.217773f, 178.019043f}, {131.159180f, 178.031006f}, {131.100586f, 178.043213f},
        {131.041992f, 178.055908f}, {130.983398f, 178.068604f}, {130.925293f, 178.081055f}, {130.866699f, 178.093262f},
        {130.807617f, 178.105225f}, {130.749512f, 178.116455f}, {130.690430f, 178.126953f}, {130.198242f, 178.224609f},
        {129.801270f, 178.338623f}, {129.496582f, 178.475586f}, {129.281738f, 178.643066f}, {129.153809f, 178.848145f},
        {129.111328f, 179.098145f}, {129.150879f, 179.400146f}, {129.270020f, 179.761475f}, {129.466797f, 180.188965f},
        {129.737305f, 180.690430f}, {129.817871f, 180.845215f}, {129.883789f, 181.002197f}, {129.937500f, 181.161377f},
        {129.980469f, 181.322754f}, {130.013672f, 181.486084f}, {130.037598f, 181.651123f}, {130.054199f, 181.818359f},
        {130.064941f, 181.987305f}, {130.071289f, 182.157959f}, {130.073730f, 182.330322f}, {130.076172f, 182.819092f},
        {130.077148f, 183.307861f}, {130.078125f, 183.796387f}, {130.078125f, 184.285156f}, {130.078125f, 184.773682f},
        {130.077148f, 185.262207f}, {130.077148f, 185.750977f}, {130.076660f, 186.239746f}, {130.077148f, 186.728516f},
        {130.078613f, 187.217285f}, {130.079590f, 187.418457f}, {130.083984f, 187.619629f}, {130.090820f, 187.820312f},
        {130.101074f, 188.020508f}, {130.115234f, 188.219971f}, {130.133301f, 188.419189f}, {130.155762f, 188.617920f},
        {130.183594f, 188.816162f}, {130.217773f, 189.013916f}, {130.257324f, 189.210938f}, {130.318848f, 189.453369f},
        {130.392578f, 189.660156f}, {130.479004f, 189.831787f}, {130.579590f, 189.968262f}, {130.696777f, 190.069824f},
        {130.829590f, 190.136475f}, {130.982422f, 190.167969f}, {131.154297f, 190.165283f}, {131.348145f, 190.127686f},
        {131.564453f, 190.055176f}, {132.004883f, 189.886719f}, {132.354492f, 189.770508f}, {132.625977f, 189.713135f},
        {132.833984f, 189.721436f}, {132.990723f, 189.802734f}, {133.110840f, 189.964600f}, {133.206543f, 190.213135f},
        {133.292480f, 190.555420f}, {133.381836f, 190.999268f}, {133.487793f, 191.551025f}, {133.571777f, 192.046631f},
        {133.629395f, 192.535400f}, {133.663086f, 193.018311f}, {133.674316f, 193.496338f}, {133.665527f, 193.971191f},
        {133.638184f, 194.443359f}, {133.594238f, 194.914795f}, {133.535645f, 195.386230f}, {133.465332f, 195.859131f},
        {133.383301f, 196.334473f}, {133.347656f, 196.528809f}, {133.314453f, 196.724365f}, {133.284668f, 196.921143f},
        {133.262695f, 197.118652f}, {133.250977f, 197.316406f}, {133.252930f, 197.514160f}, {133.270508f, 197.710938f},
        {133.307617f, 197.906738f}, {133.366699f, 198.100830f}, {133.450684f, 198.293213f}, {133.472656f, 198.331055f},
        {133.495605f, 198.367432f}, {133.519531f, 198.403076f}, {133.544434f, 198.437744f}, {133.569824f, 198.471191f},
        {133.596680f, 198.503662f}, {133.624023f, 198.534912f}, {133.652344f, 198.565674f}, {133.681641f, 198.594971f},
        {133.711426f, 198.623535f}, {134.050781f, 198.734619f}, {134.339844f, 198.884521f}, {134.580078f, 199.071289f},
        {134.774902f, 199.293457f}, {134.924805f, 199.549561f}, {135.034668f, 199.837646f}, {135.104980f, 200.155762f},
        {135.138672f, 200.501953f}, {135.137207f, 200.875488f}, {135.104492f, 201.274170f}, {135.099121f, 201.318604f},
        {135.095703f, 201.342773f}, {135.094238f, 201.351562f}, {135.093262f, 201.350342f}, {135.094238f, 201.344238f},
        {135.095703f, 201.338135f}, {135.097168f, 201.337158f}, {135.099609f, 201.346680f}, {135.100586f, 201.371582f},
        {135.102051f, 201.417236f}, {135.136230f, 202.276855f}, {135.216797f, 202.998047f}, {135.352051f, 203.586426f},
        {135.547363f, 204.047607f}, {135.808594f, 204.386475f}, {136.143555f, 204.609619f}, {136.556152f, 204.721436f},
        {137.054688f, 204.727783f}, {137.644531f, 204.634521f}, {138.331543f, 204.446777f}, {138.497070f, 204.400391f},
        {138.654785f, 204.368164f}, {138.805176f, 204.352295f}, {138.949219f, 204.354736f}, {139.087402f, 204.376953f},
        {139.220215f, 204.420898f}, {139.348633f, 204.488281f}, {139.473633f, 204.580566f}, {139.595703f, 204.699951f},
        {139.714844f, 204.847656f}, {139.887207f, 205.064453f}, {140.066406f, 205.252686f}, {140.254395f, 205.412598f},
        {140.451660f, 205.545410f}, {140.657227f, 205.651123f}, {140.873047f, 205.730225f}, {141.098633f, 205.783447f},
        {141.333984f, 205.811035f}, {141.581055f, 205.813721f}, {141.838867f, 205.792480f}, {142.252441f, 205.760498f},
        {142.628906f, 205.776367f}, {142.970215f, 205.842041f}, {143.279785f, 205.958984f}, {143.559570f, 206.128906f},
        {143.812988f, 206.354248f}, {144.042480f, 206.636230f}, {144.250000f, 206.977051f}, {144.438965f, 207.378418f},
        {144.611816f, 207.842285f}, {144.707520f, 208.095459f}, {144.814941f, 208.317627f}, {144.934082f, 208.510254f},
        {145.066895f, 208.674316f}, {145.211426f, 208.811768f}, {145.369629f, 208.923340f}, {145.541992f, 209.010986f},
        {145.727539f, 209.075439f}, {145.927246f, 209.118408f}, {146.142090f, 209.141113f}, {146.366211f, 209.141602f},
        {146.574219f, 209.115234f}, {146.766602f, 209.062500f}, {146.943848f, 208.982178f}, {147.104980f, 208.873779f},
        {147.251465f, 208.737305f}, {147.382324f, 208.571533f}, {147.498047f, 208.376953f}, {147.598145f, 208.152100f},
        {147.684082f, 207.896973f}, {147.714355f, 207.790527f}, {147.747559f, 207.679199f}, {147.785156f, 207.568359f},
        {147.828613f, 207.461914f}, {147.879395f, 207.365234f}, {147.939453f, 207.282471f}, {148.009277f, 207.218506f},
        {148.092285f, 207.178223f}, {148.187500f, 207.166016f}, {148.298828f, 207.186523f}, {148.389648f, 207.230957f},
        {148.449219f, 207.292969f}, {148.483398f, 207.369385f}, {148.497070f, 207.457275f}, {148.496094f, 207.553711f},
        {148.485840f, 207.656006f}, {148.471191f, 207.760498f}, {148.457520f, 207.864746f}, {148.451172f, 207.966064f},
        {148.455078f, 208.061035f}, {148.525391f, 208.630615f}, {148.580566f, 209.201172f}, {148.622559f, 209.772217f},
        {148.652832f, 210.344238f}, {148.673828f, 210.916748f}, {148.685059f, 211.489502f}, {148.689453f, 212.063232f},
        {148.688477f, 212.636963f}, {148.682617f, 213.211182f}, {148.674316f, 213.785645f}, {148.684082f, 213.906250f},
        {148.696289f, 214.025879f}, {148.709961f, 214.145508f}, {148.724121f, 214.265137f}, {148.738281f, 214.384766f},
        {148.749023f, 214.504395f}, {148.757812f, 214.624512f}, {148.761230f, 214.745117f}, {148.758789f, 214.866211f},
        {148.749512f, 214.988281f}, {148.722168f, 215.185059f}, {148.701172f, 215.381836f}, {148.684570f, 215.579102f},
        {148.672852f, 215.776611f}, {148.666504f, 215.974121f}, {148.664062f, 216.171875f}, {148.666504f, 216.369629f},
        {148.671875f, 216.566895f}, {148.681152f, 216.764160f}, {148.693359f, 216.961670f}, {148.701660f, 217.097168f},
        {148.709473f, 217.235107f}, {148.720703f, 217.371826f}, {148.739746f, 217.504150f}, {148.770996f, 217.628906f},
        {148.817383f, 217.741943f}, {148.883301f, 217.840576f}, {148.973145f, 217.920898f}, {149.090332f, 217.979736f},
        {149.239258f, 218.013916f}};

    Vec2 vertices23[] = {
        {289.365723f, 227.168457f}, {289.388672f, 227.053467f}, {289.411621f, 226.938965f}, {289.435059f, 226.824219f},
        {289.458496f, 226.709717f}, {289.481934f, 226.594971f}, {289.504883f, 226.480225f}, {289.527832f, 226.365723f},
        {289.551270f, 226.250977f}, {289.574219f, 226.136230f}, {289.597168f, 226.021729f}, {289.473633f, 225.667480f},
        {289.379395f, 225.307373f}, {289.310059f, 224.942627f}, {289.261719f, 224.573975f}, {289.228027f, 224.202393f},
        {289.205566f, 223.829346f}, {289.188477f, 223.454834f}, {289.173828f, 223.080566f}, {289.155273f, 222.706787f},
        {289.128906f, 222.335205f}, {289.081055f, 221.500244f}, {289.076172f, 220.667236f}, {289.104492f, 219.836182f},
        {289.157715f, 219.005859f}, {289.225098f, 218.176514f}, {289.297852f, 217.346924f}, {289.367188f, 216.517334f},
        {289.423828f, 215.686768f}, {289.457520f, 214.854736f}, {289.458496f, 214.020752f}, {289.460449f, 213.953369f},
        {289.466797f, 213.885742f}, {289.475098f, 213.818604f}, {289.484375f, 213.751465f}, {289.492188f, 213.683594f},
        {289.496582f, 213.615723f}, {289.495605f, 213.547363f}, {289.488281f, 213.478027f}, {289.472168f, 213.407959f},
        {289.444824f, 213.337158f}, {289.228027f, 212.788818f}, {289.110840f, 212.276367f}, {289.081543f, 211.796387f},
        {289.131348f, 211.344971f}, {289.250000f, 210.918457f}, {289.427246f, 210.513672f}, {289.652832f, 210.126953f},
        {289.917969f, 209.754395f}, {290.211426f, 209.392334f}, {290.524414f, 209.037598f}, {290.528320f, 206.126465f},
        {290.532715f, 203.215332f}, {290.537109f, 200.304443f}, {290.541992f, 197.393311f}, {290.546387f, 194.482422f},
        {290.551270f, 191.571533f}, {290.555176f, 188.660645f}, {290.559570f, 185.749756f}, {290.564453f, 182.838867f},
        {290.568848f, 179.927979f}, {290.596680f, 179.880859f}, {290.623535f, 179.832520f}, {290.649414f, 179.782959f},
        {290.674316f, 179.732910f}, {290.696289f, 179.681641f}, {290.715820f, 179.629395f}, {290.732422f, 179.576172f},
        {290.744629f, 179.521729f}, {290.752441f, 179.466797f}, {290.755371f, 179.410156f}, {290.761719f, 178.010010f},
        {290.772461f, 176.609863f}, {290.784668f, 175.209229f}, {290.796387f, 173.809082f}, {290.803711f, 172.408691f},
        {290.804688f, 171.008301f}, {290.796875f, 169.608154f}, {290.777344f, 168.207520f}, {290.743164f, 166.807373f},
        {290.692871f, 165.407227f}, {290.666016f, 165.352295f}, {290.637207f, 165.305908f}, {290.605957f, 165.267578f},
        {290.571777f, 165.238037f}, {290.534668f, 165.216797f}, {290.495605f, 165.203857f}, {290.453613f, 165.199463f},
        {290.409180f, 165.203125f}, {290.362305f, 165.215576f}, {290.312500f, 165.236328f}, {290.313477f, 169.108154f},
        {290.313477f, 172.979736f}, {290.313477f, 176.851562f}, {290.313477f, 180.723389f}, {290.312500f, 184.594971f},
        {290.312012f, 188.466797f}, {290.310059f, 192.338623f}, {290.307129f, 196.210449f}, {290.303711f, 200.082031f},
        {290.298828f, 203.953857f}, {290.307129f, 204.125244f}, {290.327637f, 204.313721f}, {290.351562f, 204.511230f},
        {290.369141f, 204.709961f}, {290.373535f, 204.901367f}, {290.354004f, 205.078125f}, {290.302734f, 205.232422f},
        {290.210938f, 205.355713f}, {290.070312f, 205.440430f}, {289.872070f, 205.478271f}, {289.653320f, 205.462158f},
        {289.480469f, 205.393311f}, {289.348633f, 205.279297f}, {289.251953f, 205.127686f}, {289.186035f, 204.946533f},
        {289.145508f, 204.742676f}, {289.124512f, 204.524658f}, {289.118652f, 204.299561f}, {289.123047f, 204.075439f},
        {289.130859f, 203.859619f}, {289.158203f, 202.827881f}, {289.158691f, 201.798340f}, {289.136719f, 200.770020f},
        {289.095703f, 199.742676f}, {289.039062f, 198.716553f}, {288.970703f, 197.691406f}, {288.895508f, 196.667236f},
        {288.816406f, 195.642822f}, {288.737305f, 194.619141f}, {288.662598f, 193.595703f}, {288.659668f, 193.279541f},
        {288.689941f, 192.980225f}, {288.745117f, 192.693115f}, {288.818359f, 192.415283f}, {288.899902f, 192.141846f},
        {288.982422f, 191.869385f}, {289.057129f, 191.593750f}, {289.116699f, 191.311035f}, {289.152344f, 191.017578f},
        {289.155762f, 190.708740f}, {289.123047f, 189.980957f}, {289.093750f, 189.253662f}, {289.066895f, 188.525879f},
        {289.040039f, 187.798340f}, {289.012695f, 187.070557f}, {288.982910f, 186.342773f}, {288.948242f, 185.614990f},
        {288.908203f, 184.886963f}, {288.860352f, 184.158691f}, {288.803223f, 183.430420f}, {288.788574f, 183.137695f},
        {288.791504f, 182.837158f}, {288.807129f, 182.530029f}, {288.831543f, 182.217285f}, {288.860840f, 181.898682f},
        {288.890625f, 181.576416f}, {288.915527f, 181.250488f}, {288.932617f, 180.922119f}, {288.937012f, 180.592285f},
        {288.924805f, 180.261719f}, {288.893066f, 179.697021f}, {288.872559f, 179.130859f}, {288.861328f, 178.563965f},
        {288.856934f, 177.996338f}, {288.858398f, 177.428223f}, {288.863281f, 176.859863f}, {288.870117f, 176.291016f},
        {288.875977f, 175.722412f}, {288.879395f, 175.153564f}, {288.878906f, 174.585693f}, {288.879395f, 174.498535f},
        {288.880371f, 174.408936f}, {288.880371f, 174.317627f}, {288.878906f, 174.226074f}, {288.874512f, 174.135742f},
        {288.867676f, 174.047852f}, {288.854492f, 173.964355f}, {288.836426f, 173.885742f}, {288.811523f, 173.813965f},
        {288.777832f, 173.750488f}, {288.639160f, 173.498047f}, {288.536621f, 173.244385f}, {288.467773f, 172.990234f},
        {288.428223f, 172.734375f}, {288.415039f, 172.477051f}, {288.424805f, 172.218018f}, {288.453613f, 171.957031f},
        {288.499023f, 171.694092f}, {288.556641f, 171.428223f}, {288.623535f, 171.159912f}, {288.754395f, 170.597412f},
        {288.857910f, 170.030762f}, {288.937500f, 169.461182f}, {288.996582f, 168.888428f}, {289.039062f, 168.313477f},
        {289.067383f, 167.736816f}, {289.085938f, 167.158936f}, {289.098145f, 166.580322f}, {289.107910f, 166.001221f},
        {289.116699f, 165.422852f}, {289.118652f, 165.336182f}, {289.121094f, 165.247559f}, {289.122070f, 165.157959f},
        {289.122070f, 165.067871f}, {289.119629f, 164.978760f}, {289.113770f, 164.891357f}, {289.103516f, 164.806885f},
        {289.088379f, 164.725830f}, {289.066895f, 164.649414f}, {289.038574f, 164.578613f}, {288.778809f, 163.939941f},
        {288.598145f, 163.303955f}, {288.489746f, 162.670410f}, {288.447266f, 162.038818f}, {288.460938f, 161.408936f},
        {288.526367f, 160.780762f}, {288.633789f, 160.153809f}, {288.777344f, 159.528320f}, {288.949707f, 158.903564f},
        {289.141602f, 158.279541f}, {289.301758f, 157.714600f}, {289.421387f, 157.147705f}, {289.503906f, 156.578857f},
        {289.553711f, 156.008789f}, {289.573242f, 155.437256f}, {289.567383f, 154.864746f}, {289.539551f, 154.290771f},
        {289.493164f, 153.715576f}, {289.432129f, 153.139648f}, {289.360352f, 152.562988f}, {289.182129f, 152.354492f},
        {289.025391f, 152.134521f}, {288.891602f, 151.904053f}, {288.778809f, 151.663086f}, {288.685059f, 151.411865f},
        {288.610352f, 151.150635f}, {288.552246f, 150.880127f}, {288.511230f, 150.599854f}, {288.484863f, 150.311035f},
        {288.473145f, 150.012939f}, {288.470703f, 149.502197f}, {288.475586f, 148.990967f}, {288.482422f, 148.479248f},
        {288.483887f, 147.968018f}, {288.473145f, 147.458496f}, {288.444336f, 146.950195f}, {288.390137f, 146.444092f},
        {288.304688f, 145.941162f}, {288.181152f, 145.441406f}, {288.012695f, 144.945801f}, {287.951660f, 144.739014f},
        {287.928711f, 144.541260f}, {287.940918f, 144.352783f}, {287.983887f, 144.172363f}, {288.052246f, 144.000488f},
        {288.143066f, 143.836670f}, {288.251465f, 143.680420f}, {288.373535f, 143.531982f}, {288.504395f, 143.390381f},
        {288.640625f, 143.256348f}, {288.727051f, 143.185791f}, {288.820801f, 143.128418f}, {288.917969f, 143.079346f},
        {289.017090f, 143.034424f}, {289.116211f, 142.988770f}, {289.212891f, 142.937988f}, {289.304199f, 142.877197f},
        {289.388672f, 142.802246f}, {289.462891f, 142.708740f}, {289.525391f, 142.591309f}, {289.541504f, 141.103760f},
        {289.559082f, 139.616455f}, {289.576660f, 138.128906f}, {289.592285f, 136.641846f}, {289.604004f, 135.154297f},
        {289.609375f, 133.667236f}, {289.606934f, 132.179688f}, {289.594727f, 130.692627f}, {289.570801f, 129.205322f},
        {289.532715f, 127.718018f}, {289.532227f, 127.616943f}, {289.536621f, 127.514893f}, {289.542969f, 127.409180f},
        {289.550293f, 127.299316f}, {289.556641f, 127.182617f}, {289.559570f, 127.057373f}, {289.557129f, 126.922363f},
        {289.548828f, 126.775391f}, {289.531250f, 126.614990f}, {289.503906f, 126.438965f}, {289.562500f, 127.837402f},
        {289.601074f, 129.221191f}, {289.621582f, 130.591797f}, {289.628906f, 131.950684f}, {289.625977f, 133.299561f},
        {289.616211f, 134.640137f}, {289.604492f, 135.973633f}, {289.593750f, 137.302246f}, {289.588379f, 138.627686f},
        {289.590820f, 139.950928f}, {289.591309f, 140.898926f}, {289.583496f, 141.846436f}, {289.569336f, 142.794434f},
        {289.551758f, 143.741943f}, {289.533691f, 144.689941f}, {289.517090f, 145.637695f}, {289.505371f, 146.585205f},
        {289.500488f, 147.533203f}, {289.506348f, 148.480957f}, {289.524414f, 149.428711f}, {289.521973f, 149.613037f},
        {289.510742f, 149.804932f}, {289.499512f, 150.000244f}, {289.495117f, 150.194580f}, {289.504883f, 150.384033f},
        {289.537109f, 150.564697f}, {289.599121f, 150.732178f}, {289.698242f, 150.882568f}, {289.842285f, 151.011475f},
        {290.039062f, 151.115234f}, {290.040039f, 147.805664f}, {290.040527f, 144.496338f}, {290.041504f, 141.186768f},
        {290.041992f, 137.877441f}, {290.042969f, 134.567871f}, {290.043945f, 131.258789f}, {290.044922f, 127.949463f},
        {290.046387f, 124.640381f}, {290.047363f, 121.331055f}, {290.048828f, 118.021973f}, {290.020020f, 117.996094f},
        {289.991699f, 117.975830f}, {289.962402f, 117.961182f}, {289.933594f, 117.952148f}, {289.904297f, 117.948730f},
        {289.875977f, 117.951416f}, {289.846680f, 117.959961f}, {289.818359f, 117.974609f}, {289.789551f, 117.995361f},
        {289.760254f, 118.021973f}, {289.701172f, 118.229248f}, {289.638672f, 118.402832f}, {289.570801f, 118.539551f},
        {289.498047f, 118.635986f}, {289.419922f, 118.688721f}, {289.335938f, 118.693848f}, {289.245117f, 118.648193f},
        {289.147461f, 118.548340f}, {289.041992f, 118.390869f}, {288.928711f, 118.171875f}, {288.816406f, 117.887695f},
        {288.744141f, 117.601318f}, {288.709473f, 117.316406f}, {288.713379f, 117.036377f}, {288.755371f, 116.764160f},
        {288.833984f, 116.503662f}, {288.949707f, 116.257324f}, {289.101074f, 116.028809f}, {289.287598f, 115.821533f},
        {289.509766f, 115.638672f}, {289.571289f, 115.598389f}, {289.634277f, 115.562256f}, {289.696289f, 115.526611f},
        {289.756836f, 115.489258f}, {289.812012f, 115.447266f}, {289.861328f, 115.398438f}, {289.901855f, 115.340088f},
        {289.932617f, 115.268799f}, {289.950684f, 115.182861f}, {289.955078f, 115.079102f}, {289.954590f, 114.780762f},
        {289.953613f, 114.482178f}, {289.953613f, 114.183838f}, {289.953613f, 113.885010f}, {289.953613f, 113.586670f},
        {289.953613f, 113.288330f}, {289.953613f, 112.990479f}, {289.953613f, 112.692383f}, {289.953125f, 112.394043f},
        {289.953125f, 112.095947f}, {289.952637f, 112.004395f}, {289.953125f, 111.912598f}, {289.953125f, 111.821045f},
        {289.953613f, 111.729492f}, {289.953613f, 111.637939f}, {289.953125f, 111.546387f}, {289.951172f, 111.455078f},
        {289.947754f, 111.363525f}, {289.942871f, 111.272461f}, {289.936035f, 111.181396f}, {289.916016f, 111.141602f},
        {289.893555f, 111.106689f}, {289.869141f, 111.076660f}, {289.842285f, 111.051270f}, {289.813965f, 111.031006f},
        {289.783691f, 111.015625f}, {289.750488f, 111.005127f}, {289.715820f, 110.999512f}, {289.679688f, 110.999023f},
        {289.641113f, 111.003174f}, {289.513184f, 111.150635f}, {289.403320f, 111.336182f}, {289.301758f, 111.541748f},
        {289.201172f, 111.749756f}, {289.093750f, 111.942139f}, {288.971680f, 112.101074f}, {288.826172f, 112.208740f},
        {288.648926f, 112.247314f}, {288.433594f, 112.198730f}, {288.170898f, 112.045166f}, {287.956543f, 111.866699f},
        {287.779785f, 111.674072f}, {287.640625f, 111.467529f}, {287.536621f, 111.246582f}, {287.467285f, 111.010742f},
        {287.430176f, 110.759766f}, {287.424316f, 110.492676f}, {287.448242f, 110.209229f}, {287.500000f, 109.909424f},
        {287.579102f, 109.592529f}, {287.666992f, 109.314697f}, {287.766602f, 109.028564f}, {287.865723f, 108.736328f},
        {287.950684f, 108.440186f}, {288.010254f, 108.142334f}, {288.031250f, 107.844971f}, {287.999512f, 107.550293f},
        {287.902832f, 107.260498f}, {287.729004f, 106.978027f}, {287.464355f, 106.704590f}, {287.378906f, 106.869385f},
        {287.283691f, 107.014160f}, {287.176758f, 107.139160f}, {287.059082f, 107.244141f}, {286.931641f, 107.329102f},
        {286.791992f, 107.394531f}, {286.642578f, 107.439941f}, {286.481934f, 107.465332f}, {286.310547f, 107.470947f},
        {286.127930f, 107.456543f}, {286.053223f, 107.775635f}, {285.985840f, 108.095459f}, {285.925781f, 108.416748f},
        {285.875977f, 108.738770f}, {285.836426f, 109.062256f}, {285.808594f, 109.387451f}, {285.793945f, 109.714111f},
        {285.793457f, 110.042236f}, {285.808105f, 110.372314f}, {285.838867f, 110.704102f}, {285.860352f, 110.951172f},
        {285.862793f, 111.182861f}, {285.844727f, 111.399414f}, {285.805176f, 111.601807f}, {285.743164f, 111.790527f},
        {285.656738f, 111.966309f}, {285.545410f, 112.130127f}, {285.407715f, 112.282471f}, {285.243164f, 112.423584f},
        {285.049316f, 112.554932f}, {284.761719f, 112.803711f}, {284.515625f, 113.160645f}, {284.312988f, 113.603271f},
        {284.156250f, 114.107178f}, {284.048340f, 114.649902f}, {283.993164f, 115.208008f}, {283.991211f, 115.758057f},
        {284.047363f, 116.277100f}, {284.162598f, 116.741455f}, {284.340820f, 117.127930f}, {284.434082f, 117.262695f},
        {284.529297f, 117.369385f}, {284.627441f, 117.448730f}, {284.726562f, 117.500977f}, {284.827637f, 117.526611f},
        {284.930176f, 117.525635f}, {285.033691f, 117.498535f}, {285.138184f, 117.446045f}, {285.243652f, 117.367920f},
        {285.348633f, 117.264893f}, {285.541504f, 117.080078f}, {285.711426f, 116.968018f}, {285.858398f, 116.920410f},
        {285.984375f, 116.930664f}, {286.089844f, 116.990967f}, {286.174316f, 117.094727f}, {286.239746f, 117.233643f},
        {286.286621f, 117.401367f}, {286.315918f, 117.589844f}, {286.327637f, 117.792236f}, {286.354980f, 118.648438f},
        {286.402832f, 119.503662f}, {286.464844f, 120.358398f}, {286.533203f, 121.212158f}, {286.600098f, 122.066406f},
        {286.657715f, 122.921143f}, {286.699219f, 123.776611f}, {286.716309f, 124.633545f}, {286.701660f, 125.492676f},
        {286.647461f, 126.354004f}, {286.623047f, 126.542969f}, {286.585938f, 126.715088f}, {286.535645f, 126.871338f},
        {286.472656f, 127.013916f}, {286.397949f, 127.144287f}, {286.311523f, 127.263916f}, {286.213867f, 127.374268f},
        {286.105469f, 127.476807f}, {285.987305f, 127.573486f}, {285.858398f, 127.665283f}, {285.711914f, 127.781250f},
        {285.594727f, 127.908936f}, {285.506348f, 128.046143f}, {285.447266f, 128.190918f}, {285.416992f, 128.340576f},
        {285.415527f, 128.493164f}, {285.442871f, 128.646729f}, {285.499023f, 128.798584f}, {285.583984f, 128.947021f},
        {285.697266f, 129.089600f}, {286.005859f, 129.468262f}, {286.259766f, 129.865479f}, {286.464355f, 130.280518f},
        {286.623535f, 130.711670f}, {286.742188f, 131.157471f}, {286.825684f, 131.616455f}, {286.877441f, 132.087158f},
        {286.902832f, 132.568604f}, {286.905762f, 133.059326f}, {286.892578f, 133.557129f}, {286.847656f, 134.061279f},
        {286.842773f, 134.555908f}, {286.873047f, 135.040771f}, {286.937500f, 135.517334f}, {287.031738f, 135.986084f},
        {287.153809f, 136.447754f}, {287.301270f, 136.902588f}, {287.469727f, 137.352539f}, {287.658203f, 137.797119f},
        {287.862793f, 138.237793f}, {287.762207f, 138.193359f}, {287.684570f, 138.139648f}, {287.625977f, 138.077637f},
        {287.583984f, 138.009033f}, {287.553711f, 137.935547f}, {287.533203f, 137.858643f}, {287.519043f, 137.779541f},
        {287.506836f, 137.699707f}, {287.494629f, 137.621094f}, {287.478027f, 137.544922f}, {287.440430f, 137.412109f},
        {287.396973f, 137.288818f}, {287.346680f, 137.176514f}, {287.289062f, 137.075439f}, {287.222656f, 136.987305f},
        {287.147461f, 136.912842f}, {287.061523f, 136.853760f}, {286.964844f, 136.810547f}, {286.855957f, 136.784668f},
        {286.733887f, 136.777344f}, {286.593750f, 136.791992f}, {286.473633f, 136.829346f}, {286.370117f, 136.887451f},
        {286.281738f, 136.964355f}, {286.207520f, 137.057861f}, {286.145020f, 137.166016f}, {286.092773f, 137.287354f},
        {286.048828f, 137.419189f}, {286.012207f, 137.559814f}, {285.979980f, 137.707520f}, {285.911621f, 138.108154f},
        {285.863281f, 138.508789f}, {285.833984f, 138.908691f}, {285.822754f, 139.308594f}, {285.826660f, 139.708008f},
        {285.845215f, 140.106934f}, {285.875488f, 140.505371f}, {285.917480f, 140.903076f}, {285.967773f, 141.300537f},
        {286.026367f, 141.697510f}, {286.052734f, 141.869385f}, {286.076660f, 142.039795f}, {286.096680f, 142.209473f},
        {286.112793f, 142.378662f}, {286.122070f, 142.547363f}, {286.123047f, 142.715576f}, {286.115234f, 142.884033f},
        {286.097656f, 143.052734f}, {286.066895f, 143.221436f}, {286.023926f, 143.391113f}, {286.003906f, 143.535889f},
        {285.988770f, 143.680420f}, {285.978516f, 143.824707f}, {285.972168f, 143.969238f}, {285.971191f, 144.113770f},
        {285.974609f, 144.258057f}, {285.982422f, 144.402344f}, {285.994629f, 144.546387f}, {286.011719f, 144.690674f},
        {286.033691f, 144.834961f}, {286.128418f, 145.790039f}, {286.216797f, 146.745850f}, {286.293945f, 147.701660f},
        {286.357422f, 148.658203f}, {286.402344f, 149.615234f}, {286.426758f, 150.572510f}, {286.425781f, 151.530029f},
        {286.396973f, 152.488037f}, {286.336426f, 153.446289f}, {286.241211f, 154.404785f}, {286.182617f, 155.054443f},
        {286.159668f, 155.701660f}, {286.164551f, 156.346680f}, {286.189941f, 156.990479f}, {286.229980f, 157.633057f},
        {286.277344f, 158.274658f}, {286.325684f, 158.916504f}, {286.367676f, 159.558838f}, {286.395996f, 160.201416f},
        {286.405273f, 160.845459f}, {286.401855f, 161.247803f}, {286.393066f, 161.643555f}, {286.373535f, 162.032715f},
        {286.338379f, 162.415039f}, {286.282227f, 162.790527f}, {286.200195f, 163.159424f}, {286.087891f, 163.521484f},
        {285.939453f, 163.876221f}, {285.750000f, 164.224121f}, {285.515625f, 164.565186f}, {285.322266f, 164.855469f},
        {285.188965f, 165.143555f}, {285.114746f, 165.426025f}, {285.097168f, 165.699707f}, {285.135742f, 165.961426f},
        {285.229004f, 166.208008f}, {285.375000f, 166.436279f}, {285.571777f, 166.643311f}, {285.819336f, 166.825439f},
        {286.115234f, 166.979492f}, {286.348145f, 167.108887f}, {286.525879f, 167.264160f}, {286.655762f, 167.441895f},
        {286.747559f, 167.638184f}, {286.810547f, 167.848633f}, {286.851562f, 168.070068f}, {286.880371f, 168.297607f},
        {286.905273f, 168.528076f}, {286.934570f, 168.757080f}, {286.977539f, 168.980713f}, {287.145508f, 169.779541f},
        {287.266602f, 170.580322f}, {287.346191f, 171.383301f}, {287.390625f, 172.187500f}, {287.405273f, 172.993408f},
        {287.396973f, 173.800537f}, {287.370605f, 174.608398f}, {287.331543f, 175.416992f}, {287.287109f, 176.226074f},
        {287.241699f, 177.035156f}, {287.207520f, 177.587158f}, {287.167480f, 178.139160f}, {287.125488f, 178.691162f},
        {287.085938f, 179.242920f}, {287.053223f, 179.795166f}, {287.030762f, 180.347412f}, {287.023438f, 180.900146f},
        {287.035645f, 181.453125f}, {287.070312f, 182.007080f}, {287.133301f, 182.561035f}, {287.138672f, 182.606445f},
        {287.145020f, 182.651855f}, {287.151367f, 182.696777f}, {287.159668f, 182.741455f}, {287.167969f, 182.786133f},
        {287.177246f, 182.830811f}, {287.187012f, 182.875000f}, {287.197266f, 182.919189f}, {287.208008f, 182.962891f},
        {287.219727f, 183.006592f}, {287.280762f, 183.194092f}, {287.327148f, 183.381592f}, {287.360840f, 183.569580f},
        {287.380859f, 183.758057f}, {287.388184f, 183.947021f}, {287.383301f, 184.136475f}, {287.365723f, 184.325928f},
        {287.335938f, 184.516113f}, {287.294434f, 184.706299f}, {287.241699f, 184.896973f}, {287.229980f, 184.942383f},
        {287.219238f, 184.988037f}, {287.209473f, 185.033203f}, {287.200195f, 185.079346f}, {287.192383f, 185.125244f},
        {287.184570f, 185.171143f}, {287.177734f, 185.217529f}, {287.171875f, 185.264160f}, {287.166016f, 185.310791f},
        {287.161133f, 185.357910f}, {287.121094f, 186.315674f}, {287.108398f, 187.273438f}, {287.114746f, 188.231201f},
        {287.133301f, 189.189209f}, {287.158203f, 190.146729f}, {287.182617f, 191.104736f}, {287.198242f, 192.062500f},
        {287.199707f, 193.020020f}, {287.179688f, 193.977539f}, {287.130859f, 194.935059f}, {287.123047f, 195.091797f},
        {287.118652f, 195.249268f}, {287.116211f, 195.406738f}, {287.114746f, 195.564453f}, {287.111328f, 195.721680f},
        {287.104980f, 195.878906f}, {287.093262f, 196.035156f}, {287.075684f, 196.190918f}, {287.049316f, 196.345703f},
        {287.012695f, 196.499023f}, {286.963867f, 196.903076f}, {286.932129f, 197.307373f}, {286.915527f, 197.712158f},
        {286.910645f, 198.117432f}, {286.913574f, 198.522461f}, {286.922363f, 198.928223f}, {286.932129f, 199.333740f},
        {286.940430f, 199.739258f}, {286.944336f, 200.144775f}, {286.939453f, 200.550049f}, {286.944336f, 200.596924f},
        {286.950195f, 200.643555f}, {286.957031f, 200.689941f}, {286.964355f, 200.736328f}, {286.972656f, 200.782471f},
        {286.981934f, 200.828369f}, {286.991699f, 200.874023f}, {287.002441f, 200.919678f}, {287.013672f, 200.964844f},
        {287.025879f, 201.010010f}, {287.177246f, 201.436035f}, {287.287109f, 201.861084f}, {287.358398f, 202.285400f},
        {287.392578f, 202.708984f}, {287.393066f, 203.132080f}, {287.360840f, 203.554443f}, {287.299805f, 203.976318f},
        {287.211426f, 204.397461f}, {287.097656f, 204.818848f}, {286.961914f, 205.239258f}, {286.916016f, 205.673584f},
        {286.884766f, 206.107910f}, {286.864746f, 206.542725f}, {286.854004f, 206.977783f}, {286.851074f, 207.412842f},
        {286.853516f, 207.848145f}, {286.859863f, 208.283691f}, {286.867676f, 208.718750f}, {286.875488f, 209.154297f},
        {286.880371f, 209.589844f}, {287.080566f, 210.764648f}, {287.218750f, 211.943115f}, {287.304688f, 213.124268f},
        {287.350586f, 214.307861f}, {287.365234f, 215.493408f}, {287.358398f, 216.679932f}, {287.341309f, 217.866943f},
        {287.324219f, 219.053955f}, {287.316895f, 220.240723f}, {287.330566f, 221.425781f}, {287.339355f, 221.812744f},
        {287.350098f, 222.198975f}, {287.361328f, 222.585205f}, {287.375488f, 222.970947f}, {287.390625f, 223.356689f},
        {287.407715f, 223.742188f}, {287.427734f, 224.127930f}, {287.449707f, 224.513916f}, {287.475098f, 224.899414f},
        {287.502930f, 225.285400f}, {287.520020f, 225.644531f}, {287.516602f, 226.001221f}, {287.494629f, 226.355713f},
        {287.454590f, 226.707275f}, {287.397949f, 227.055908f}, {287.325684f, 227.401855f}, {287.239258f, 227.744629f},
        {287.140137f, 228.084473f}, {287.028809f, 228.420898f}, {286.907227f, 228.754150f}, {286.766113f, 229.153564f},
        {286.674316f, 229.494141f}, {286.633301f, 229.780273f}, {286.645020f, 230.016113f}, {286.712402f, 230.205566f},
        {286.836914f, 230.352539f}, {287.020996f, 230.461182f}, {287.266113f, 230.535645f}, {287.574219f, 230.580078f},
        {287.949219f, 230.598145f}, {288.163574f, 230.299805f}, {288.369141f, 229.996338f}, {288.563477f, 229.685059f},
        {288.743164f, 229.365234f}, {288.905762f, 229.034912f}, {289.048828f, 228.692383f}, {289.169922f, 228.336670f},
        {289.265137f, 227.965332f}, {289.332520f, 227.577148f}, {289.369629f, 227.170410f}};

    Vec2 vertices24[] = {
        {45.750000f, 144.375000f},  {75.500000f, 136.875000f},  {75.500000f, 159.125000f},  {100.250000f, 161.375000f},
        {65.500000f, 181.375000f},  {102.250000f, 179.125000f}, {95.000000f, 215.125000f},  {129.331467f, 189.926208f},
        {131.371460f, 206.366196f}, {139.651474f, 192.446198f}, {161.851471f, 200.606201f}, {151.000000f, 220.375000f},
        {110.500000f, 244.375000f}, {153.750000f, 238.125000f}, {142.500000f, 253.875000f}, {220.750000f, 259.375000f},
        {250.500000f, 244.375000f}, {168.750000f, 241.875000f}, {182.250000f, 154.125000f}, {190.250000f, 227.375000f},
        {196.500000f, 197.375000f}, {208.750000f, 210.625000f}, {220.750000f, 194.375000f}, {208.750000f, 176.375000f},
        {253.250000f, 173.875000f}, {243.750000f, 154.125000f}, {213.750000f, 161.375000f}, {202.250000f, 139.875000f},
        {236.000000f, 131.875000f}, {218.500000f, 120.875000f}, {206.500000f, 125.625000f}, {184.500000f, 110.375000f},
        {157.000000f, 108.625000f}, {147.500000f, 96.625000f},  {153.750000f, 85.125000f},  {147.500000f, 75.375000f},
        {126.500000f, 74.125000f},  {110.500000f, 86.625000f},  {127.750000f, 85.125000f},  {135.250000f, 91.125000f},
        {135.250000f, 97.875000f},  {124.000000f, 93.875000f},  {115.500000f, 100.875000f}, {115.500000f, 111.875000f},
        {135.250000f, 108.625000f}, {151.000000f, 124.125000f}, {90.500000f, 131.875000f},  {113.250000f, 120.875000f},
        {88.000000f, 116.875000f},  {106.000000f, 103.875000f}, {88.000000f, 97.875000f},
    };

    Vec2 vertices25[] = {
        {138.267090f, 127.291748f}, {139.800293f, 127.490967f}, {141.316650f, 127.755859f}, {142.816895f, 128.080566f},
        {144.303223f, 128.458984f}, {145.777100f, 128.885254f}, {147.240234f, 129.353516f}, {148.693848f, 129.857422f},
        {150.140137f, 130.390869f}, {151.580322f, 130.948486f}, {153.016113f, 131.523682f}, {153.330566f, 131.678467f},
        {153.591553f, 131.861816f}, {153.805908f, 132.071777f}, {153.979736f, 132.305664f}, {154.120117f, 132.561523f},
        {154.233643f, 132.836670f}, {154.326904f, 133.128906f}, {154.406006f, 133.435547f}, {154.478027f, 133.755127f},
        {154.549316f, 134.084473f}, {154.708740f, 134.787354f}, {154.878418f, 135.488037f}, {155.056641f, 136.186768f},
        {155.242188f, 136.883789f}, {155.434326f, 137.579346f}, {155.631592f, 138.273682f}, {155.832520f, 138.967041f},
        {156.036133f, 139.659668f}, {156.241211f, 140.352051f}, {156.446289f, 141.043701f}, {156.637207f, 141.585693f},
        {156.875488f, 142.085205f}, {157.157227f, 142.539795f}, {157.479980f, 142.946777f}, {157.840332f, 143.302490f},
        {158.236084f, 143.604736f}, {158.663330f, 143.849854f}, {159.119873f, 144.035645f}, {159.602051f, 144.158691f},
        {160.107178f, 144.216064f}, {160.766357f, 144.279541f}, {161.313965f, 144.406006f}, {161.761963f, 144.595215f},
        {162.123535f, 144.847900f}, {162.410645f, 145.164307f}, {162.635986f, 145.545166f}, {162.811768f, 145.990479f},
        {162.951172f, 146.500977f}, {163.065430f, 147.076904f}, {163.167969f, 147.718994f}, {163.407227f, 148.722900f},
        {163.790527f, 149.583984f}, {164.298340f, 150.316162f}, {164.912842f, 150.934326f}, {165.613525f, 151.452148f},
        {166.382812f, 151.884277f}, {167.200928f, 152.244629f}, {168.049072f, 152.547119f}, {168.908203f, 152.806396f},
        {169.759277f, 153.036621f}, {170.612305f, 153.238770f}, {171.473877f, 153.404053f}, {172.342773f, 153.539307f},
        {173.217285f, 153.650635f}, {174.095947f, 153.743896f}, {174.977295f, 153.824951f}, {175.860352f, 153.900879f},
        {176.743408f, 153.976562f}, {177.624756f, 154.059326f}, {178.503174f, 154.154541f}, {178.844482f, 154.316162f},
        {179.179688f, 154.478271f}, {179.507080f, 154.646729f}, {179.825195f, 154.826904f}, {180.133057f, 155.025391f},
        {180.428955f, 155.246826f}, {180.711426f, 155.498047f}, {180.979736f, 155.783936f}, {181.231689f, 156.110596f},
        {181.466797f, 156.484131f}, {181.795654f, 157.011719f}, {182.178955f, 157.533447f}, {182.607910f, 158.032227f},
        {183.072754f, 158.492188f}, {183.564209f, 158.895996f}, {184.073242f, 159.227051f}, {184.590088f, 159.468994f},
        {185.106201f, 159.604980f}, {185.611572f, 159.618408f}, {186.096924f, 159.492676f}, {187.556396f, 159.023193f},
        {188.905029f, 158.877930f}, {190.160400f, 159.004395f}, {191.341064f, 159.350342f}, {192.464355f, 159.863525f},
        {193.548096f, 160.491943f}, {194.610352f, 161.182617f}, {195.668945f, 161.884277f}, {196.741455f, 162.543945f},
        {197.846191f, 163.109863f}, {198.067627f, 163.353516f}, {198.268311f, 163.643799f}, {198.459717f, 163.954102f},
        {198.654541f, 164.258301f}, {198.864014f, 164.529297f}, {199.100830f, 164.740967f}, {199.376465f, 164.866943f},
        {199.703369f, 164.880371f}, {200.092773f, 164.755371f}, {200.557129f, 164.464844f}, {200.884766f, 163.278809f},
        {200.970703f, 162.235352f}, {200.843506f, 161.317139f}, {200.534668f, 160.506104f}, {200.073486f, 159.784668f},
        {199.489990f, 159.135010f}, {198.814941f, 158.539307f}, {198.077881f, 157.979980f}, {197.308594f, 157.439453f},
        {196.538086f, 156.899658f}, {195.129883f, 155.962402f}, {193.670166f, 155.151611f}, {192.168945f, 154.441162f},
        {190.637207f, 153.804932f}, {189.085449f, 153.215820f}, {187.524414f, 152.647705f}, {185.965576f, 152.073975f},
        {184.418945f, 151.468018f}, {182.895264f, 150.803711f}, {181.405762f, 150.054443f}, {180.676758f, 149.641357f},
        {179.985352f, 149.211182f}, {179.333984f, 148.755127f}, {178.726074f, 148.264160f}, {178.163818f, 147.729736f},
        {177.650635f, 147.143066f}, {177.189453f, 146.495605f}, {176.782959f, 145.778076f}, {176.433594f, 144.982178f},
        {176.145020f, 144.099121f}, {175.583252f, 142.681885f}, {174.716553f, 141.287598f}, {173.595215f, 139.948242f},
        {172.270996f, 138.696289f}, {170.795166f, 137.563965f}, {169.218506f, 136.583496f}, {167.593262f, 135.786621f},
        {165.969971f, 135.206055f}, {164.400146f, 134.873535f}, {162.935059f, 134.822021f}, {162.500732f, 134.852295f},
        {162.071045f, 134.875977f}, {161.647461f, 134.885010f}, {161.231689f, 134.870117f}, {160.825439f, 134.823975f},
        {160.429688f, 134.737549f}, {160.047119f, 134.602539f}, {159.678467f, 134.410400f}, {159.325928f, 134.152588f},
        {158.990723f, 133.820801f}, {157.458740f, 132.215576f}, {155.839844f, 130.785156f}, {154.141846f, 129.513672f},
        {152.372803f, 128.383789f}, {150.541260f, 127.378418f}, {148.655029f, 126.481201f}, {146.722168f, 125.675049f},
        {144.750732f, 124.942871f}, {142.749268f, 124.268066f}, {140.725342f, 123.633789f}, {139.885498f, 123.361816f},
        {139.052734f, 123.065430f}, {138.225342f, 122.751221f}, {137.400879f, 122.424561f}, {136.577637f, 122.093018f},
        {135.753662f, 121.762207f}, {134.926758f, 121.438721f}, {134.095215f, 121.129639f}, {133.256592f, 120.840576f},
        {132.409180f, 120.578369f}, {132.152832f, 120.480225f}, {131.946533f, 120.351318f}, {131.786377f, 120.195068f},
        {131.669189f, 120.014160f}, {131.591064f, 119.812744f}, {131.548340f, 119.593506f}, {131.537842f, 119.360107f},
        {131.555664f, 119.115234f}, {131.598389f, 118.862793f}, {131.662109f, 118.605957f}, {131.768311f, 118.372070f},
        {131.887451f, 118.149414f}, {132.018555f, 117.937256f}, {132.160889f, 117.735596f}, {132.313721f, 117.543213f},
        {132.476807f, 117.359863f}, {132.649170f, 117.185059f}, {132.830811f, 117.018555f}, {133.020264f, 116.859131f},
        {133.217529f, 116.706543f}, {133.295898f, 116.646729f}, {133.372803f, 116.585205f}, {133.448486f, 116.521729f},
        {133.522461f, 116.456787f}, {133.595215f, 116.389893f}, {133.666748f, 116.322021f}, {133.736816f, 116.252441f},
        {133.805664f, 116.181396f}, {133.873291f, 116.109375f}, {133.939453f, 116.036377f}, {134.111084f, 115.793213f},
        {134.281006f, 115.548584f}, {134.449219f, 115.303223f}, {134.616211f, 115.056396f}, {134.782227f, 114.809082f},
        {134.947510f, 114.561035f}, {135.112305f, 114.312500f}, {135.277100f, 114.063721f}, {135.441406f, 113.814941f},
        {135.606201f, 113.566406f}, {135.707275f, 113.391846f}, {135.806641f, 113.216064f}, {135.903564f, 113.039551f},
        {135.999268f, 112.862549f}, {136.094482f, 112.684814f}, {136.188721f, 112.506836f}, {136.282959f, 112.329102f},
        {136.377686f, 112.151611f}, {136.473145f, 111.974609f}, {136.569824f, 111.798584f}, {136.821045f, 111.341797f},
        {137.096924f, 110.911621f}, {137.395508f, 110.506348f}, {137.716309f, 110.124268f}, {138.057373f, 109.764404f},
        {138.417480f, 109.424561f}, {138.795166f, 109.103760f}, {139.188721f, 108.799561f}, {139.597412f, 108.511230f},
        {140.019775f, 108.237061f}, {140.274658f, 108.047852f}, {140.531250f, 107.861572f}, {140.789551f, 107.677490f},
        {141.049072f, 107.496094f}, {141.310303f, 107.316895f}, {141.572754f, 107.140137f}, {141.836670f, 106.965088f},
        {142.102051f, 106.792480f}, {142.368408f, 106.621094f}, {142.636230f, 106.451904f}, {144.346680f, 105.290283f},
        {146.032959f, 104.094727f}, {147.698730f, 102.868896f}, {149.345947f, 101.617432f}, {150.977783f, 100.343994f},
        {152.597412f, 99.052979f},  {154.207520f, 97.748047f},  {155.810303f, 96.434082f},  {157.409424f, 95.114990f},
        {159.007324f, 93.794678f},  {159.449707f, 93.444824f},  {159.907471f, 93.096191f},  {160.359131f, 92.737305f},
        {160.783936f, 92.357178f},  {161.161377f, 91.945068f},  {161.470215f, 91.489502f},  {161.690186f, 90.979980f},
        {161.800049f, 90.405273f},  {161.779541f, 89.753906f},  {161.607178f, 89.015625f},  {161.372314f, 88.913086f},
        {161.145508f, 88.855225f},  {160.925293f, 88.837158f},  {160.711670f, 88.854004f},  {160.503418f, 88.901123f},
        {160.299316f, 88.973145f},  {160.098877f, 89.065918f},  {159.901123f, 89.173584f},  {159.705322f, 89.292480f},
        {159.510010f, 89.416504f},  {158.992920f, 89.898926f},  {158.512451f, 90.305908f},  {158.068359f, 90.616455f},
        {157.661377f, 90.808594f},  {157.291260f, 90.860840f},  {156.958252f, 90.751221f},  {156.663574f, 90.458740f},
        {156.406494f, 89.961426f},  {156.187744f, 89.237793f},  {156.007568f, 88.266357f},  {155.843506f, 87.373535f},
        {155.624756f, 86.492676f},  {155.361816f, 85.620361f},  {155.069092f, 84.752686f},  {154.757812f, 83.886475f},
        {154.440918f, 83.017822f},  {154.131348f, 82.143799f},  {153.841064f, 81.260254f},  {153.582520f, 80.364258f},
        {153.368896f, 79.451416f},  {153.251221f, 78.755371f},  {153.194824f, 78.109131f},  {153.200439f, 77.508301f},
        {153.270020f, 76.948730f},  {153.405273f, 76.425537f},  {153.606689f, 75.934814f},  {153.876709f, 75.471924f},
        {154.216309f, 75.032715f},  {154.626953f, 74.612549f},  {155.110352f, 74.207275f},  {155.765381f, 73.704834f},
        {156.423096f, 73.208008f},  {157.086182f, 72.723633f},  {157.758545f, 72.256592f},  {158.443115f, 71.812744f},
        {159.143311f, 71.396973f},  {159.862305f, 71.016113f},  {160.603516f, 70.674805f},  {161.370117f, 70.378662f},
        {162.165527f, 70.133545f},  {163.342041f, 69.745361f},  {164.459961f, 69.244873f},  {165.531006f, 68.654541f},
        {166.566162f, 67.996582f},  {167.578125f, 67.293457f},  {168.578369f, 66.566650f},  {169.578369f, 65.839355f},
        {170.590088f, 65.133057f},  {171.625000f, 64.470703f},  {172.695312f, 63.873535f},  {173.259277f, 63.696777f},
        {173.776367f, 63.469727f},  {174.247803f, 63.193848f},  {174.675537f, 62.871094f},  {175.060791f, 62.503174f},
        {175.405273f, 62.092041f},  {175.711182f, 61.639160f},  {175.979736f, 61.146484f},  {176.212891f, 60.615967f},
        {176.411621f, 60.048584f},  {177.813721f, 58.156250f},  {179.311035f, 56.480713f},  {180.903564f, 55.026611f},
        {182.593018f, 53.797607f},  {184.378906f, 52.797363f},  {186.262207f, 52.029785f},  {188.244141f, 51.498535f},
        {190.324707f, 51.208008f},  {192.504883f, 51.161133f},  {194.785156f, 51.362549f},  {197.445801f, 51.641113f},
        {199.784180f, 51.670898f},  {201.825195f, 51.433105f},  {203.594971f, 50.907471f},  {205.119629f, 50.074951f},
        {206.424561f, 48.916016f},  {207.535889f, 47.410645f},  {208.479248f, 45.539795f},  {209.280273f, 43.283203f},
        {209.964600f, 40.622070f},  {209.985840f, 40.494141f},  {210.001709f, 40.365723f},  {210.012451f, 40.237793f},
        {210.018799f, 40.109619f},  {210.020020f, 39.981689f},  {210.016846f, 39.853760f},  {210.009033f, 39.725830f},
        {209.996582f, 39.598145f},  {209.979980f, 39.470703f},  {209.959229f, 39.343262f},  {209.923584f, 39.218506f},
        {209.880127f, 39.099609f},  {209.828613f, 38.987305f},  {209.769287f, 38.881348f},  {209.701904f, 38.781738f},
        {209.626465f, 38.688721f},  {209.543701f, 38.602051f},  {209.452881f, 38.521729f},  {209.354248f, 38.447998f},
        {209.248291f, 38.380615f},  {208.789551f, 38.405029f},  {208.365723f, 38.490723f},  {207.972168f, 38.631104f},
        {207.605225f, 38.818604f},  {207.260254f, 39.046875f},  {206.933105f, 39.308350f},  {206.619385f, 39.596191f},
        {206.315186f, 39.903809f},  {206.016113f, 40.223633f},  {205.717773f, 40.549316f},  {204.853027f, 41.424561f},
        {203.952148f, 42.209961f},  {203.014160f, 42.903320f},  {202.038574f, 43.502930f},  {201.025146f, 44.007080f},
        {199.973389f, 44.414062f},  {198.883057f, 44.722168f},  {197.753174f, 44.929688f},  {196.583740f, 45.034668f},
        {195.374268f, 45.035645f},  {195.180420f, 45.031738f},  {194.986328f, 45.035156f},  {194.791992f, 45.043213f},
        {194.597656f, 45.053711f},  {194.403564f, 45.064697f},  {194.210205f, 45.074219f},  {194.017822f, 45.079346f},
        {193.826660f, 45.078613f},  {193.637207f, 45.069580f},  {193.449463f, 45.050293f},  {191.080566f, 44.913086f},
        {188.811523f, 45.105957f},  {186.625977f, 45.575684f},  {184.508301f, 46.268799f},  {182.441650f, 47.131104f},
        {180.410156f, 48.109375f},  {178.397949f, 49.149902f},  {176.388672f, 50.199219f},  {174.366211f, 51.203613f},
        {172.314697f, 52.109131f},  {171.895996f, 52.317139f},  {171.514648f, 52.579102f},  {171.164062f, 52.885254f},
        {170.837891f, 53.227295f},  {170.530518f, 53.595947f},  {170.235596f, 53.981689f},  {169.946777f, 54.376465f},
        {169.658203f, 54.770752f},  {169.363281f, 55.155273f},  {169.056641f, 55.521240f},  {168.408691f, 56.185791f},
        {167.751221f, 56.733398f},  {167.081543f, 57.161865f},  {166.397461f, 57.468018f},  {165.696289f, 57.649414f},
        {164.975342f, 57.702881f},  {164.232666f, 57.625977f},  {163.464844f, 57.415527f},  {162.670410f, 57.069092f},
        {161.845947f, 56.583740f},  {160.644775f, 55.838623f},  {159.603271f, 55.307373f},  {158.703613f, 54.996582f},
        {157.928955f, 54.913086f},  {157.261475f, 55.063721f},  {156.684814f, 55.455078f},  {156.181152f, 56.093506f},
        {155.733154f, 56.986084f},  {155.323730f, 58.139404f},  {154.935547f, 59.559814f},  {154.775391f, 60.156738f},
        {154.591797f, 60.740479f},  {154.385986f, 61.312012f},  {154.159668f, 61.871826f},  {153.913818f, 62.420654f},
        {153.649658f, 62.958984f},  {153.368408f, 63.487305f},  {153.071777f, 64.006348f},  {152.760254f, 64.516357f},
        {152.435791f, 65.017822f},  {152.059082f, 65.590088f},  {151.693848f, 66.165039f},  {151.344238f, 66.745850f},
        {151.014404f, 67.334961f},  {150.708740f, 67.935303f},  {150.431641f, 68.549805f},  {150.187500f, 69.180908f},
        {149.980225f, 69.831299f},  {149.814453f, 70.504150f},  {149.694336f, 71.201904f},  {149.559082f, 71.915039f},
        {149.364258f, 72.501709f},  {149.111328f, 72.966797f},  {148.802002f, 73.314209f},  {148.437012f, 73.549316f},
        {148.017822f, 73.676270f},  {147.546143f, 73.699707f},  {147.022949f, 73.624268f},  {146.449707f, 73.454346f},
        {145.827881f, 73.194824f},  {144.517822f, 72.706299f},  {143.117188f, 72.411621f},  {141.657227f, 72.302734f},
        {140.169678f, 72.372070f},  {138.686035f, 72.611328f},  {137.237793f, 73.012451f},  {135.856689f, 73.567871f},
        {134.574219f, 74.269043f},  {133.422119f, 75.108154f},  {132.431641f, 76.077393f},  {132.212891f, 76.354492f},
        {132.034180f, 76.636230f},  {131.894287f, 76.922607f},  {131.791748f, 77.214111f},  {131.725586f, 77.510742f},
        {131.693848f, 77.812988f},  {131.695801f, 78.120850f},  {131.729980f, 78.434326f},  {131.795166f, 78.753906f},
        {131.889893f, 79.080078f},  {132.023926f, 79.504395f},  {132.148926f, 79.931641f},  {132.267578f, 80.361084f},
        {132.383057f, 80.791016f},  {132.498535f, 81.221436f},  {132.617676f, 81.649902f},  {132.743652f, 82.076172f},
        {132.879150f, 82.499023f},  {133.027588f, 82.916992f},  {133.192871f, 83.329590f},  {133.776367f, 84.845703f},
        {134.143311f, 86.157471f},  {134.285156f, 87.275635f},  {134.193115f, 88.211426f},  {133.858398f, 88.976562f},
        {133.272217f, 89.581787f},  {132.426270f, 90.038574f},  {131.312012f, 90.358398f},  {129.920410f, 90.552002f},
        {128.242920f, 90.631104f},  {128.369873f, 90.065430f},  {128.577637f, 89.574219f},  {128.850586f, 89.144531f},
        {129.174072f, 88.762939f},  {129.532471f, 88.416260f},  {129.911377f, 88.090820f},  {130.295166f, 87.773682f},
        {130.669189f, 87.451416f},  {131.017578f, 87.111084f},  {131.326172f, 86.738770f},  {131.820801f, 85.967773f},
        {132.160645f, 85.241455f},  {132.346680f, 84.564697f},  {132.379639f, 83.942627f},  {132.260498f, 83.379883f},
        {131.990479f, 82.881348f},  {131.570068f, 82.451172f},  {131.000488f, 82.095215f},  {130.282959f, 81.817383f},
        {129.418213f, 81.623047f},  {128.992432f, 81.560547f},  {128.563232f, 81.511719f},  {128.132568f, 81.480225f},
        {127.702393f, 81.469727f},  {127.274414f, 81.482666f},  {126.850586f, 81.523438f},  {126.432861f, 81.594727f},
        {126.022949f, 81.700195f},  {125.623047f, 81.843262f},  {125.235107f, 82.027100f},  {123.002686f, 83.058838f},
        {120.760010f, 83.788330f},  {118.508057f, 84.250977f},  {116.248047f, 84.482178f},  {113.981445f, 84.517578f},
        {111.708984f, 84.393066f},  {109.432861f, 84.143799f},  {107.153809f, 83.805664f},  {104.873047f, 83.414062f},
        {102.592285f, 83.004639f},  {101.862793f, 82.726074f},  {101.049316f, 82.165527f},  {100.188965f, 81.375244f},
        {99.318848f, 80.408203f},   {98.476318f, 79.315918f},   {97.698730f, 78.151367f},   {97.023438f, 76.966309f},
        {96.487305f, 75.812988f},   {96.127686f, 74.744385f},   {95.981689f, 73.812256f},   {95.955322f, 72.879150f},
        {95.934570f, 71.945068f},   {95.916016f, 71.011475f},   {95.896973f, 70.077637f},   {95.874268f, 69.144287f},
        {95.844971f, 68.210693f},   {95.805664f, 67.277588f},   {95.753418f, 66.345459f},   {95.685303f, 65.413574f},
        {95.598389f, 64.482422f},   {95.578857f, 64.360107f},   {95.555908f, 64.239502f},   {95.528809f, 64.119629f},
        {95.498535f, 64.001465f},   {95.464600f, 63.884277f},   {95.427246f, 63.768311f},   {95.386719f, 63.653564f},
        {95.342529f, 63.539551f},   {95.295654f, 63.426758f},   {95.245605f, 63.314941f},   {94.668945f, 62.579834f},
        {94.125488f, 62.089600f},   {93.611328f, 61.819580f},   {93.123535f, 61.744873f},   {92.658203f, 61.840576f},
        {92.212402f, 62.082520f},   {91.782471f, 62.445312f},   {91.365234f, 62.904785f},   {90.956787f, 63.436035f},
        {90.554199f, 64.014404f},   {90.417969f, 64.247070f},   {90.295654f, 64.503662f},   {90.178223f, 64.770752f},
        {90.057373f, 65.034668f},   {89.924805f, 65.281738f},   {89.771729f, 65.498291f},   {89.589600f, 65.671143f},
        {89.370361f, 65.785889f},   {89.104980f, 65.829346f},   {88.784912f, 65.787598f},   {88.459229f, 65.668213f},
        {88.196533f, 65.497070f},   {87.989014f, 65.281494f},   {87.829346f, 65.028076f},   {87.710449f, 64.744873f},
        {87.624756f, 64.438477f},   {87.565430f, 64.115967f},   {87.524902f, 63.784668f},   {87.495850f, 63.451904f},
        {87.471191f, 63.124756f},   {87.436279f, 61.605713f},   {87.549561f, 60.119629f},   {87.783203f, 58.660156f},
        {88.109375f, 57.220947f},   {88.500488f, 55.795898f},   {88.928955f, 54.378662f},   {89.366455f, 52.963135f},
        {89.785400f, 51.543213f},   {90.158203f, 50.112305f},   {90.457031f, 48.664551f},   {90.548340f, 48.026611f},
        {90.592773f, 47.425049f},   {90.586426f, 46.859131f},   {90.524658f, 46.327881f},   {90.403564f, 45.830322f},
        {90.218506f, 45.365479f},   {89.966064f, 44.932129f},   {89.641602f, 44.529297f},   {89.240967f, 44.156494f},
        {88.760010f, 43.812256f},   {88.350586f, 43.561523f},   {87.936768f, 43.334229f},   {87.521240f, 43.147949f},
        {87.108887f, 43.018799f},   {86.702637f, 42.963867f},   {86.305908f, 43.000244f},   {85.922852f, 43.144531f},
        {85.556885f, 43.413086f},   {85.211670f, 43.823242f},   {84.890869f, 44.391846f},   {84.712891f, 46.942627f},
        {84.600830f, 49.493896f},   {84.541748f, 52.045654f},   {84.523438f, 54.597900f},   {84.533203f, 57.149902f},
        {84.558350f, 59.702393f},   {84.586670f, 62.254150f},   {84.605225f, 64.806152f},   {84.601562f, 67.357422f},
        {84.562988f, 69.908203f},   {84.552002f, 70.758301f},   {84.554932f, 71.608643f},   {84.564941f, 72.459229f},
        {84.576660f, 73.309814f},   {84.583496f, 74.159912f},   {84.579102f, 75.009521f},   {84.557617f, 75.858154f},
        {84.512695f, 76.706055f},   {84.437744f, 77.552734f},   {84.326904f, 78.398193f},   {84.170166f, 80.235840f},
        {84.127441f, 82.073242f},   {84.168701f, 83.911133f},   {84.265137f, 85.749268f},   {84.387207f, 87.587402f},
        {84.506104f, 89.426270f},   {84.592041f, 91.265137f},   {84.615967f, 93.104736f},   {84.548096f, 94.944824f},
        {84.360107f, 96.785645f},   {84.685303f, 100.734619f},  {85.014648f, 104.682373f},  {85.331787f, 108.630371f},
        {85.621094f, 112.579102f},  {85.866943f, 116.530029f},  {86.053467f, 120.484131f},  {86.164795f, 124.442627f},
        {86.185059f, 128.406494f},  {86.098877f, 132.377197f},  {85.890381f, 136.355469f},  {85.853516f, 137.619141f},
        {85.899658f, 138.886475f},  {85.999268f, 140.157715f},  {86.125000f, 141.432129f},  {86.247314f, 142.709229f},
        {86.338623f, 143.989258f},  {86.370117f, 145.270996f},  {86.313477f, 146.554932f},  {86.140137f, 147.840332f},
        {85.821289f, 149.126953f},  {85.749268f, 149.443115f},  {85.730713f, 149.755859f},  {85.762207f, 150.061523f},
        {85.842041f, 150.356934f},  {85.967529f, 150.638428f},  {86.136475f, 150.902832f},  {86.346680f, 151.146484f},
        {86.595215f, 151.365967f},  {86.880127f, 151.558350f},  {87.198975f, 151.719727f},  {87.353760f, 151.963867f},
        {87.508789f, 152.207764f},  {87.663574f, 152.452148f},  {87.817871f, 152.696045f},  {87.972412f, 152.940186f},
        {88.127197f, 153.184082f},  {88.281738f, 153.428223f},  {88.436279f, 153.672119f},  {88.591064f, 153.916504f},
        {88.746094f, 154.160645f},  {88.760742f, 152.299561f},  {88.949707f, 150.645508f},  {89.321533f, 149.200195f},
        {89.884033f, 147.965088f},  {90.645020f, 146.940918f},  {91.612793f, 146.130127f},  {92.795166f, 145.533447f},
        {94.200684f, 145.152588f},  {95.836914f, 144.989258f},  {97.712158f, 145.044189f},  {98.368652f, 145.026611f},
        {98.910889f, 144.867676f},  {99.338867f, 144.584229f},  {99.651855f, 144.193848f},  {99.849854f, 143.713379f},
        {99.932129f, 143.160156f},  {99.898438f, 142.551025f},  {99.748779f, 141.903320f},  {99.481934f, 141.234131f},
        {99.098145f, 140.560791f},  {98.358398f, 139.509766f},  {97.656494f, 138.665771f},  {96.978760f, 138.027100f},
        {96.313477f, 137.591553f},  {95.647217f, 137.357422f},  {94.968018f, 137.322510f},  {94.262695f, 137.485352f},
        {93.519043f, 137.843506f},  {92.724121f, 138.395264f},  {91.865234f, 139.138672f},  {91.711670f, 139.280029f},
        {91.556885f, 139.415527f},  {91.400146f, 139.540039f},  {91.240479f, 139.648682f},  {91.077148f, 139.737061f},
        {90.909424f, 139.799805f},  {90.736084f, 139.832764f},  {90.557129f, 139.831055f},  {90.370605f, 139.789307f},
        {90.176514f, 139.703369f},  {89.959229f, 139.556152f},  {89.790771f, 139.385986f},  {89.664551f, 139.196533f},
        {89.574951f, 138.989990f},  {89.516113f, 138.769531f},  {89.482178f, 138.537598f},  {89.467285f, 138.297119f},
        {89.465088f, 138.051025f},  {89.469971f, 137.801758f},  {89.476318f, 137.552490f},  {89.545166f, 136.104736f},
        {89.682129f, 134.670166f},  {89.866455f, 133.253418f},  {90.076904f, 131.859131f},  {90.292969f, 130.493164f},
        {90.492920f, 129.159912f},  {90.656006f, 127.864746f},  {90.761719f, 126.612549f},  {90.788330f, 125.408203f},
        {90.715332f, 124.257080f},  {90.659912f, 124.995117f},  {90.700684f, 125.778809f},  {90.818848f, 126.604736f},
        {90.996582f, 127.469238f},  {91.215088f, 128.368652f},  {91.457031f, 129.299072f},  {91.703857f, 130.256836f},
        {91.936523f, 131.238770f},  {92.138428f, 132.240723f},  {92.290039f, 133.259277f},  {92.338867f, 133.722656f},
        {92.392334f, 134.215088f},  {92.464600f, 134.713867f},  {92.571533f, 135.194824f},  {92.727539f, 135.634277f},
        {92.947998f, 136.009033f},  {93.247803f, 136.295410f},  {93.642090f, 136.469727f},  {94.145508f, 136.508057f},
        {94.773193f, 136.387451f},  {95.333984f, 136.166748f},  {95.816162f, 135.869629f},  {96.217773f, 135.504883f},
        {96.536621f, 135.081055f},  {96.770264f, 134.606445f},  {96.916748f, 134.089600f},  {96.973633f, 133.539062f},
        {96.938477f, 132.962891f},  {96.809326f, 132.370361f},  {96.584229f, 131.769531f},  {96.237549f, 130.886475f},
        {96.006836f, 130.024658f},  {95.885010f, 129.183838f},  {95.865967f, 128.362305f},  {95.943359f, 127.558350f},
        {96.110596f, 126.770752f},  {96.360840f, 125.998535f},  {96.688477f, 125.240234f},  {97.086182f, 124.494141f},
        {97.547852f, 123.759521f},  {97.891113f, 123.297852f},  {98.245850f, 122.916504f},  {98.606934f, 122.625977f},
        {98.968994f, 122.437500f},  {99.327393f, 122.362549f},  {99.677002f, 122.411865f},  {100.012451f, 122.596680f},
        {100.328613f, 122.928223f}, {100.620850f, 123.417480f}, {100.883789f, 124.075439f}, {101.234375f, 124.980225f},
        {101.652100f, 125.883057f}, {102.083008f, 126.786621f}, {102.473633f, 127.692627f}, {102.770020f, 128.603271f},
        {102.918213f, 129.520752f}, {102.864746f, 130.447021f}, {102.555664f, 131.384277f}, {101.937500f, 132.334717f},
        {100.956299f, 133.299805f}, {100.722656f, 133.562256f}, {100.576416f, 133.878662f}, {100.504395f, 134.240234f},
        {100.495117f, 134.636475f}, {100.535400f, 135.058105f}, {100.613525f, 135.495361f}, {100.716797f, 135.938477f},
        {100.833252f, 136.377930f}, {100.950439f, 136.803955f}, {101.056396f, 137.207031f}, {101.532715f, 138.440674f},
        {102.312256f, 139.631592f}, {103.336426f, 140.747070f}, {104.547119f, 141.753906f}, {105.886475f, 142.618896f},
        {107.295898f, 143.309326f}, {108.717773f, 143.791748f}, {110.093506f, 144.033447f}, {111.365234f, 144.001465f},
        {112.474854f, 143.662842f}, {112.878174f, 143.439941f}, {113.275146f, 143.194580f}, {113.668945f, 142.949219f},
        {114.062256f, 142.728027f}, {114.458252f, 142.553711f}, {114.860352f, 142.449707f}, {115.270996f, 142.438965f},
        {115.693359f, 142.545166f}, {116.130615f, 142.791260f}, {116.585693f, 143.200439f}, {116.888916f, 143.556152f},
        {117.148438f, 143.925049f}, {117.363281f, 144.306885f}, {117.532959f, 144.701660f}, {117.656494f, 145.108643f},
        {117.733398f, 145.527832f}, {117.762939f, 145.958252f}, {117.744385f, 146.399902f}, {117.677246f, 146.852295f},
        {117.560547f, 147.315430f}, {117.379883f, 147.843750f}, {117.166260f, 148.337646f}, {116.917480f, 148.793457f},
        {116.632080f, 149.207031f}, {116.307617f, 149.574707f}, {115.941895f, 149.892334f}, {115.533203f, 150.156250f},
        {115.079346f, 150.362549f}, {114.577881f, 150.507568f}, {114.027588f, 150.587158f}, {113.371094f, 150.638428f},
        {112.715820f, 150.690430f}, {112.061768f, 150.749023f}, {111.410645f, 150.819580f}, {110.762451f, 150.907959f},
        {110.118408f, 151.019531f}, {109.479248f, 151.159912f}, {108.845459f, 151.334961f}, {108.217773f, 151.549805f},
        {107.597412f, 151.810547f}, {106.609619f, 152.317139f}, {105.821533f, 152.833496f}, {105.233887f, 153.363770f},
        {104.848389f, 153.912109f}, {104.666016f, 154.482666f}, {104.687500f, 155.079834f}, {104.914307f, 155.707520f},
        {105.347412f, 156.370117f}, {105.987549f, 157.071289f}, {106.836426f, 157.815674f}, {107.289795f, 158.214844f},
        {107.661133f, 158.615479f}, {107.953857f, 159.021729f}, {108.172119f, 159.437744f}, {108.318604f, 159.867188f},
        {108.397461f, 160.314453f}, {108.413086f, 160.782959f}, {108.367676f, 161.277344f}, {108.266113f, 161.800781f},
        {108.111328f, 162.357910f}, {107.870117f, 163.130371f}, {107.629883f, 163.903320f}, {107.389648f, 164.676270f},
        {107.148926f, 165.448975f}, {106.906982f, 166.221191f}, {106.663330f, 166.992676f}, {106.417480f, 167.763428f},
        {106.168213f, 168.533447f}, {105.915527f, 169.302002f}, {105.658691f, 170.069092f}, {105.166748f, 171.527100f},
        {104.694336f, 172.985596f}, {104.265137f, 174.447998f}, {103.903076f, 175.917236f}, {103.632080f, 177.395996f},
        {103.475830f, 178.887939f}, {103.457520f, 180.395264f}, {103.601318f, 181.921387f}, {103.930908f, 183.468994f},
        {104.469971f, 185.041260f}, {104.660645f, 185.628174f}, {104.759277f, 186.218018f}, {104.775635f, 186.809814f},
        {104.720459f, 187.401367f}, {104.602783f, 187.991211f}, {104.433350f, 188.578125f}, {104.221680f, 189.160156f},
        {103.978027f, 189.736084f}, {103.711914f, 190.303955f}, {103.434082f, 190.862305f}, {102.697754f, 192.423096f},
        {102.095215f, 193.969727f}, {101.649658f, 195.499023f}, {101.385498f, 197.008301f}, {101.326416f, 198.495117f},
        {101.496094f, 199.956055f}, {101.918457f, 201.388916f}, {102.617188f, 202.790527f}, {103.616211f, 204.158203f},
        {104.939453f, 205.489014f}, {105.345703f, 205.889404f}, {105.637451f, 206.273682f}, {105.819824f, 206.643555f},
        {105.898926f, 207.000732f}, {105.880859f, 207.347412f}, {105.770508f, 207.685303f}, {105.574463f, 208.016357f},
        {105.298096f, 208.342285f}, {104.947510f, 208.665039f}, {104.528320f, 208.986328f}, {103.419678f, 209.888428f},
        {102.454590f, 210.893555f}, {101.613037f, 211.985840f}, {100.874756f, 213.149902f}, {100.218994f, 214.370117f},
        {99.625488f, 215.630615f},  {99.073975f, 216.916016f},  {98.544189f, 218.210938f},  {98.015381f, 219.499268f},
        {97.467529f, 220.765625f},  {97.181885f, 221.436035f},  {96.919434f, 222.102295f},  {96.662354f, 222.756104f},
        {96.394287f, 223.390137f},  {96.098389f, 223.996338f},  {95.757812f, 224.566406f},  {95.355713f, 225.092529f},
        {94.875488f, 225.567139f},  {94.300049f, 225.981689f},  {93.612305f, 226.329102f},  {93.213867f, 226.515137f},
        {92.843994f, 226.732666f},  {92.508301f, 226.981689f},  {92.212646f, 227.262207f},  {91.962402f, 227.573730f},
        {91.763672f, 227.916504f},  {91.622070f, 228.290527f},  {91.542969f, 228.695312f},  {91.532227f, 229.131348f},
        {91.595947f, 229.597900f},  {91.791748f, 228.136475f},  {91.809814f, 226.682129f},  {91.689209f, 225.231934f},
        {91.468506f, 223.783447f},  {91.186523f, 222.333496f},  {90.881836f, 220.879150f},  {90.593506f, 219.417480f},
        {90.359863f, 217.945557f},  {90.220215f, 216.460449f},  {90.212646f, 214.959229f},  {90.208740f, 214.739258f},
        {90.177002f, 214.516357f},  {90.115723f, 214.298096f},  {90.023438f, 214.092773f},  {89.899170f, 213.908203f},
        {89.740723f, 213.752686f},  {89.547852f, 213.633545f},  {89.318848f, 213.558838f},  {89.051758f, 213.536865f},
        {88.746094f, 213.575195f},  {88.622803f, 215.219482f},  {88.602051f, 216.862061f},  {88.655518f, 218.503662f},
        {88.756592f, 220.145508f},  {88.878418f, 221.788086f},  {88.993164f, 223.432373f},  {89.073730f, 225.079346f},
        {89.092529f, 226.729248f},  {89.023193f, 228.383545f},  {88.837646f, 230.042725f},  {88.739990f, 231.020020f},
        {88.755127f, 231.940674f},  {88.888428f, 232.790283f},  {89.145264f, 233.554443f},  {89.530518f, 234.218994f},
        {90.049805f, 234.769043f},  {90.708252f, 235.191162f},  {91.510986f, 235.469971f},  {92.463379f, 235.591797f},
        {93.570801f, 235.541748f},  {94.277344f, 235.502441f},  {94.875000f, 235.562012f},  {95.369873f, 235.714600f},
        {95.767822f, 235.955566f},  {96.075684f, 236.279297f},  {96.299561f, 236.679932f},  {96.445557f, 237.152588f},
        {96.520020f, 237.691895f},  {96.528809f, 238.292236f},  {96.479004f, 238.948242f},  {96.436768f, 239.525391f},
        {96.439697f, 240.094971f},  {96.480225f, 240.658691f},  {96.551758f, 241.217041f},  {96.646973f, 241.771729f},
        {96.759277f, 242.323730f},  {96.881592f, 242.874023f},  {97.007324f, 243.424316f},  {97.128906f, 243.975830f},
        {97.239990f, 244.529297f},  {97.284668f, 244.777588f},  {97.331055f, 245.028076f},  {97.384277f, 245.275391f},
        {97.449463f, 245.513184f},  {97.531494f, 245.735107f},  {97.635986f, 245.935547f},  {97.768066f, 246.108398f},
        {97.932861f, 246.247070f},  {98.135498f, 246.346191f},  {98.381348f, 246.399170f},  {98.617920f, 246.397461f},
        {98.835205f, 246.345703f},  {99.034912f, 246.251221f},  {99.219238f, 246.120117f},  {99.389893f, 245.959717f},
        {99.549561f, 245.777100f},  {99.698975f, 245.578369f},  {99.840820f, 245.370850f},  {99.976807f, 245.161377f},
        {100.109131f, 244.956299f}, {100.562256f, 244.128662f}, {100.890137f, 243.233398f}, {101.094238f, 242.288574f},
        {101.176270f, 241.311768f}, {101.138184f, 240.320557f}, {100.981934f, 239.332031f}, {100.708984f, 238.364502f},
        {100.321289f, 237.435059f}, {99.820801f, 236.561523f},  {99.209229f, 235.761230f},  {98.490723f, 234.752930f},
        {98.017578f, 233.671631f},  {97.779297f, 232.552246f},  {97.767090f, 231.430176f},  {97.970947f, 230.340576f},
        {98.381348f, 229.318848f},  {98.988770f, 228.400635f},  {99.782959f, 227.620850f},  {100.755127f, 227.015137f},
        {101.895020f, 226.618652f}, {102.270752f, 226.524414f}, {102.645020f, 226.412109f}, {103.008789f, 226.280762f},
        {103.354004f, 226.127686f}, {103.672363f, 225.951416f}, {103.955811f, 225.750488f}, {104.195801f, 225.522461f},
        {104.384033f, 225.266113f}, {104.512451f, 224.979492f}, {104.572754f, 224.660889f}, {104.716064f, 223.599365f},
        {104.974365f, 222.577148f}, {105.316895f, 221.584717f}, {105.712891f, 220.612793f}, {106.131592f, 219.652100f},
        {106.542480f, 218.693115f}, {106.915039f, 217.726562f}, {107.218262f, 216.742920f}, {107.421631f, 215.732910f},
        {107.494629f, 214.687256f}, {107.524414f, 213.910889f}, {107.618408f, 213.201904f}, {107.776855f, 212.555908f},
        {108.001465f, 211.969727f}, {108.292969f, 211.438965f}, {108.652100f, 210.960205f}, {109.080322f, 210.529053f},
        {109.578613f, 210.141846f}, {110.147705f, 209.794922f}, {110.788818f, 209.483643f}, {111.477539f, 209.141846f},
        {112.025635f, 208.776855f}, {112.432617f, 208.388184f}, {112.698975f, 207.976807f}, {112.823730f, 207.542236f},
        {112.807373f, 207.084717f}, {112.649902f, 206.604736f}, {112.350830f, 206.101807f}, {111.910156f, 205.576904f},
        {111.327637f, 205.029541f}, {110.974365f, 204.716797f}, {110.630127f, 204.392578f}, {110.292480f, 204.059082f},
        {109.960449f, 203.719238f}, {109.631592f, 203.374756f}, {109.304443f, 203.028076f}, {108.977051f, 202.681641f},
        {108.647461f, 202.337891f}, {108.314209f, 201.998779f}, {107.975098f, 201.666992f}, {107.268311f, 200.947754f},
        {106.653809f, 200.219971f}, {106.139160f, 199.476074f}, {105.733398f, 198.707275f}, {105.443604f, 197.905762f},
        {105.279053f, 197.062744f}, {105.247314f, 196.170410f}, {105.356201f, 195.219971f}, {105.614990f, 194.203613f},
        {106.031006f, 193.112793f}, {106.416992f, 192.125244f}, {106.725342f, 191.106445f}, {106.963379f, 190.060791f},
        {107.139160f, 188.993652f}, {107.259033f, 187.909668f}, {107.331055f, 186.813965f}, {107.362549f, 185.711426f},
        {107.361084f, 184.606689f}, {107.334229f, 183.504639f}, {107.289062f, 182.410400f}, {107.250244f, 180.428711f},
        {107.333252f, 178.506592f}, {107.549561f, 176.646729f}, {107.911133f, 174.851318f}, {108.429443f, 173.123291f},
        {109.115723f, 171.465332f}, {109.982178f, 169.880127f}, {111.040283f, 168.370117f}, {112.301270f, 166.937500f},
        {113.777588f, 165.585693f}, {114.574951f, 164.891113f}, {115.308838f, 164.160645f}, {115.952148f, 163.391602f},
        {116.477539f, 162.581055f}, {116.857910f, 161.726074f}, {117.065918f, 160.823730f}, {117.074463f, 159.871094f},
        {116.855957f, 158.865234f}, {116.383789f, 157.803711f}, {115.630127f, 156.683350f}, {115.415527f, 156.353760f},
        {115.304932f, 156.056396f}, {115.284912f, 155.788818f}, {115.342773f, 155.549805f}, {115.465332f, 155.337402f},
        {115.639648f, 155.149414f}, {115.852539f, 154.984375f}, {116.091309f, 154.840332f}, {116.342773f, 154.715576f},
        {116.593994f, 154.608398f}, {117.470459f, 154.160889f}, {118.198730f, 153.599609f}, {118.803223f, 152.943604f},
        {119.309570f, 152.212402f}, {119.742432f, 151.425049f}, {120.126953f, 150.600830f}, {120.488281f, 149.759277f},
        {120.851318f, 148.919678f}, {121.240967f, 148.101562f}, {121.682617f, 147.324219f}, {121.781006f, 147.134521f},
        {121.862305f, 146.909424f}, {121.925537f, 146.659180f}, {121.969238f, 146.393555f}, {121.992432f, 146.122070f},
        {121.994385f, 145.854980f}, {121.973389f, 145.602295f}, {121.928467f, 145.374023f}, {121.858887f, 145.179688f},
        {121.762939f, 145.029785f}, {121.005371f, 144.024902f}, {120.451172f, 142.996826f}, {120.075684f, 141.948730f},
        {119.856689f, 140.883057f}, {119.769531f, 139.802979f}, {119.791260f, 138.710938f}, {119.898193f, 137.610840f},
        {120.066895f, 136.504639f}, {120.274414f, 135.395264f}, {120.496338f, 134.286377f}, {120.730469f, 132.979736f},
        {120.922363f, 131.665771f}, {121.086670f, 130.347412f}, {121.238525f, 129.026367f}, {121.392090f, 127.705322f},
        {121.562500f, 126.386963f}, {121.764404f, 125.073975f}, {122.012207f, 123.768311f}, {122.320557f, 122.472900f},
        {122.704346f, 121.189941f}, {122.840332f, 120.730225f}, {122.956543f, 120.263184f}, {123.068848f, 119.800537f},
        {123.193848f, 119.352295f}, {123.348389f, 118.929688f}, {123.548340f, 118.543457f}, {123.811035f, 118.204102f},
        {124.152588f, 117.922363f}, {124.589111f, 117.709473f}, {125.137695f, 117.575684f}, {125.556885f, 117.534668f},
        {125.961914f, 117.537109f}, {126.350342f, 117.583740f}, {126.720215f, 117.675049f}, {127.069824f, 117.811035f},
        {127.396729f, 117.991943f}, {127.698975f, 118.217529f}, {127.974609f, 118.488770f}, {128.221436f, 118.805420f},
        {128.437500f, 119.167969f}, {128.632568f, 119.646729f}, {128.713379f, 120.095459f}, {128.696045f, 120.518311f},
        {128.596680f, 120.918945f}, {128.431641f, 121.301514f}, {128.216797f, 121.669189f}, {127.968262f, 122.026611f},
        {127.702148f, 122.377197f}, {127.434814f, 122.725586f}, {127.182129f, 123.074707f}, {127.088379f, 123.204102f},
        {126.989014f, 123.329834f}, {126.885742f, 123.453125f}, {126.780762f, 123.574951f}, {126.676270f, 123.696777f},
        {126.574219f, 123.819336f}, {126.477295f, 123.944580f}, {126.386719f, 124.072998f}, {126.305176f, 124.206055f},
        {126.234863f, 124.344971f}, {126.120117f, 124.611816f}, {126.017822f, 124.887207f}, {125.934570f, 125.166748f},
        {125.878418f, 125.445557f}, {125.856445f, 125.719238f}, {125.875977f, 125.982666f}, {125.944092f, 126.231201f},
        {126.068848f, 126.460449f}, {126.256592f, 126.665283f}, {126.515625f, 126.841064f}, {126.764160f, 126.939941f},
        {126.988525f, 126.961914f}, {127.191162f, 126.917969f}, {127.374268f, 126.817871f}, {127.540771f, 126.672852f},
        {127.692871f, 126.493164f}, {127.833496f, 126.288818f}, {127.964844f, 126.071045f}, {128.089355f, 125.849609f},
        {128.209717f, 125.635498f}, {128.374756f, 125.324707f}, {128.529541f, 125.002441f}, {128.682861f, 124.679199f},
        {128.845215f, 124.364990f}, {129.025391f, 124.070068f}, {129.232910f, 123.804443f}, {129.477295f, 123.577881f},
        {129.768066f, 123.401123f}, {130.114746f, 123.283447f}, {130.526123f, 123.235596f}, {131.400635f, 123.431641f},
        {132.220459f, 123.742188f}, {132.997559f, 124.142334f}, {133.744385f, 124.606201f}, {134.472656f, 125.108643f},
        {135.194824f, 125.624023f}, {135.922852f, 126.126953f}, {136.669189f, 126.592041f}, {137.445801f, 126.993652f},
        {138.264648f, 127.306396f},
    };

    Vec2 vertices26[] = {
        {227.830200f, 131.051514f}, {227.830200f, 131.051514f}, {227.491943f, 131.093506f}, {227.174561f, 131.086182f},
        {226.875244f, 131.033447f}, {226.591309f, 130.940186f}, {226.319946f, 130.809814f}, {226.058472f, 130.646729f},
        {225.804077f, 130.455811f}, {225.554199f, 130.240479f}, {225.305664f, 130.006104f}, {225.056274f, 129.756104f},
        {225.056274f, 129.756104f}, {224.661011f, 129.356689f}, {224.260376f, 128.960205f}, {223.855347f, 128.567139f},
        {223.447144f, 128.177002f}, {223.037109f, 127.789795f}, {222.626343f, 127.405518f}, {222.216309f, 127.025146f},
        {221.807739f, 126.647705f}, {221.402222f, 126.273682f}, {221.000854f, 125.902588f}, {221.000854f, 125.902588f},
        {220.510498f, 125.515869f}, {220.007324f, 125.232178f}, {219.496704f, 125.027100f}, {218.984253f, 124.876709f},
        {218.474976f, 124.756592f}, {217.974487f, 124.642822f}, {217.488037f, 124.510498f}, {217.021240f, 124.336670f},
        {216.579102f, 124.095947f}, {216.166992f, 123.764404f}, {216.166992f, 123.764404f}, {215.786865f, 123.450684f},
        {215.369019f, 123.188232f}, {214.929443f, 122.954834f}, {214.484375f, 122.727295f}, {214.049683f, 122.484375f},
        {213.641602f, 122.202393f}, {213.276001f, 121.859863f}, {212.969238f, 121.433594f}, {212.737061f, 120.901611f},
        {212.595825f, 120.240967f}, {212.595825f, 120.240967f}, {212.537598f, 119.963379f}, {212.442993f, 119.747070f},
        {212.316284f, 119.587646f}, {212.161987f, 119.479492f}, {211.984375f, 119.418945f}, {211.788452f, 119.400391f},
        {211.578369f, 119.420166f}, {211.358643f, 119.472656f}, {211.133911f, 119.553467f}, {210.908691f, 119.658203f},
        {210.908691f, 119.658203f}, {210.357056f, 119.936279f}, {209.805664f, 120.211670f}, {209.258179f, 120.492432f},
        {208.718506f, 120.786377f}, {208.190186f, 121.102539f}, {207.677368f, 121.448486f}, {207.183472f, 121.832764f},
        {206.712402f, 122.263916f}, {206.267822f, 122.750000f}, {205.853638f, 123.298828f}, {205.853638f, 123.298828f},
        {205.658569f, 123.542969f}, {205.460693f, 123.712402f}, {205.263794f, 123.810059f}, {205.072021f, 123.838623f},
        {204.889648f, 123.800293f}, {204.720581f, 123.697754f}, {204.569092f, 123.533691f}, {204.439087f, 123.310059f},
        {204.334717f, 123.030273f}, {204.260010f, 122.696045f}, {204.260010f, 122.696045f}, {204.025879f, 121.652832f},
        {203.688110f, 120.693115f}, {203.262573f, 119.804199f}, {202.765259f, 118.973633f}, {202.212402f, 118.188477f},
        {201.619751f, 117.435547f}, {201.003418f, 116.703125f}, {200.379395f, 115.977783f}, {199.763794f, 115.247070f},
        {199.172241f, 114.498291f}, {199.172241f, 114.498291f}, {198.989258f, 114.302490f}, {198.809448f, 114.195068f},
        {198.636230f, 114.165527f}, {198.473877f, 114.204590f}, {198.326172f, 114.302246f}, {198.197266f, 114.448975f},
        {198.090942f, 114.634521f}, {198.011108f, 114.849365f}, {197.961670f, 115.083984f}, {197.946411f, 115.328125f},
        {197.946411f, 115.328125f}, {197.944214f, 115.763428f}, {197.921387f, 116.176025f}, {197.871704f, 116.563721f},
        {197.789551f, 116.924316f}, {197.668701f, 117.255127f}, {197.503906f, 117.554199f}, {197.289062f, 117.819580f},
        {197.018311f, 118.048096f}, {196.685791f, 118.238281f}, {196.286011f, 118.387451f}, {196.286011f, 118.387451f},
        {196.167480f, 118.439209f}, {196.072632f, 118.514893f}, {195.998047f, 118.611084f}, {195.940918f, 118.724365f},
        {195.897949f, 118.851562f}, {195.866089f, 118.989014f}, {195.842041f, 119.134033f}, {195.822876f, 119.282227f},
        {195.805542f, 119.430664f}, {195.786743f, 119.576172f}, {195.786743f, 119.576172f}, {195.639526f, 120.191650f},
        {195.395996f, 120.729980f}, {195.070923f, 121.185303f}, {194.678467f, 121.550293f}, {194.233032f, 121.820068f},
        {193.749023f, 121.987305f}, {193.240967f, 122.046387f}, {192.723267f, 121.991211f}, {192.210205f, 121.815674f},
        {191.716187f, 121.513184f}, {191.716187f, 121.513184f}, {191.560303f, 121.390625f}, {191.414429f, 121.266357f},
        {191.280884f, 121.138428f}, {191.162354f, 121.003662f}, {191.061157f, 120.859863f}, {190.979858f, 120.704834f},
        {190.921021f, 120.535645f}, {190.886963f, 120.350098f}, {190.880371f, 120.145752f}, {190.903687f, 119.919922f},
        {190.903687f, 119.919922f}, {190.950073f, 119.692627f}, {191.012085f, 119.479248f}, {191.089844f, 119.280518f},
        {191.183594f, 119.096680f}, {191.293335f, 118.927979f}, {191.419312f, 118.774414f}, {191.561523f, 118.636475f},
        {191.720215f, 118.513672f}, {191.895630f, 118.407227f}, {192.087646f, 118.316650f}, {192.087646f, 118.316650f},
        {192.330322f, 118.238037f}, {192.593994f, 118.179199f}, {192.866211f, 118.126953f}, {193.134277f, 118.067627f},
        {193.385376f, 117.987305f}, {193.607178f, 117.872314f}, {193.786743f, 117.709473f}, {193.911621f, 117.484619f},
        {193.969116f, 117.184570f}, {193.946655f, 116.795654f}, {193.946655f, 116.795654f}, {193.858765f, 116.392578f},
        {193.723999f, 116.014404f}, {193.546631f, 115.665283f}, {193.331055f, 115.347168f}, {193.081665f, 115.063965f},
        {192.802734f, 114.817627f}, {192.499146f, 114.611572f}, {192.174561f, 114.449219f}, {191.833740f, 114.332764f},
        {191.481201f, 114.265381f}, {191.481201f, 114.265381f}, {191.018188f, 114.212402f}, {190.553589f, 114.164551f},
        {190.087158f, 114.127441f}, {189.619507f, 114.106445f}, {189.151001f, 114.107178f}, {188.681763f, 114.134766f},
        {188.212524f, 114.195068f}, {187.743286f, 114.293457f}, {187.274536f, 114.434814f}, {186.806519f, 114.625488f},
        {186.806519f, 114.625488f}, {186.090088f, 114.885498f}, {185.388306f, 115.006592f}, {184.700317f, 115.007080f},
        {184.025269f, 114.905273f}, {183.362183f, 114.719971f}, {182.709839f, 114.469238f}, {182.067993f, 114.171875f},
        {181.435181f, 113.845947f}, {180.810547f, 113.510010f}, {180.193481f, 113.182617f}, {180.193481f, 113.182617f},
        {179.786133f, 112.989990f}, {179.374756f, 112.826660f}, {178.960449f, 112.687012f}, {178.543945f, 112.566162f},
        {178.126465f, 112.458252f}, {177.709106f, 112.358398f}, {177.292725f, 112.260742f}, {176.878296f, 112.160156f},
        {176.466919f, 112.051514f}, {176.059692f, 111.928955f}, {176.059692f, 111.928955f}, {175.732788f, 111.887695f},
        {175.406738f, 111.959717f}, {175.078491f, 112.120117f}, {174.745239f, 112.344727f}, {174.404663f, 112.608154f},
        {174.053833f, 112.885986f}, {173.690063f, 113.153809f}, {173.310791f, 113.386475f}, {172.913208f, 113.559326f},
        {172.494629f, 113.648193f}, {172.494629f, 113.648193f}, {172.290405f, 113.688965f}, {172.100342f, 113.769043f},
        {171.922485f, 113.882568f}, {171.755005f, 114.023438f}, {171.595825f, 114.185791f}, {171.443115f, 114.362793f},
        {171.294922f, 114.549316f}, {171.149292f, 114.738525f}, {171.004272f, 114.925049f}, {170.858032f, 115.102539f},
        {170.858032f, 115.102539f}, {170.651367f, 115.320801f}, {170.446533f, 115.492676f}, {170.242310f, 115.618896f},
        {170.037109f, 115.699219f}, {169.829590f, 115.733643f}, {169.618164f, 115.722656f}, {169.401855f, 115.666016f},
        {169.178833f, 115.563965f}, {168.947632f, 115.416504f}, {168.707153f, 115.223877f}, {168.707153f, 115.223877f},
        {168.265503f, 114.823486f}, {167.836670f, 114.409424f}, {167.419922f, 113.982422f}, {167.014893f, 113.543701f},
        {166.620361f, 113.093262f}, {166.235962f, 112.632324f}, {165.860596f, 112.160889f}, {165.493652f, 111.679688f},
        {165.134277f, 111.189941f}, {164.781982f, 110.691406f}, {164.781982f, 110.691406f}, {164.643311f, 110.475342f},
        {164.523438f, 110.253418f}, {164.420776f, 110.026123f}, {164.334351f, 109.792969f}, {164.262817f, 109.554199f},
        {164.205200f, 109.309326f}, {164.160156f, 109.058105f}, {164.126587f, 108.801270f}, {164.103516f, 108.537842f},
        {164.089478f, 108.268311f}, {164.089478f, 108.268311f}, {164.054688f, 107.724854f}, {163.991577f, 107.274902f},
        {163.896606f, 106.917969f}, {163.766968f, 106.653076f}, {163.599121f, 106.478516f}, {163.389771f, 106.394287f},
        {163.135864f, 106.398682f}, {162.834106f, 106.490479f}, {162.481079f, 106.669189f}, {162.073853f, 106.933838f},
        {162.073853f, 106.933838f}, {161.560669f, 107.252441f}, {161.062378f, 107.477539f}, {160.576904f, 107.614502f},
        {160.102661f, 107.667480f}, {159.637451f, 107.642334f}, {159.179443f, 107.542969f}, {158.726685f, 107.375000f},
        {158.277222f, 107.143311f}, {157.828979f, 106.852295f}, {157.380249f, 106.507324f}, {157.380249f, 106.507324f},
        {157.257324f, 106.403564f}, {157.141113f, 106.297607f}, {157.034302f, 106.187988f}, {156.940308f, 106.073486f},
        {156.862183f, 105.953125f}, {156.802979f, 105.824463f}, {156.765747f, 105.686768f}, {156.753906f, 105.538574f},
        {156.770142f, 105.378174f}, {156.817871f, 105.204590f}, {156.817871f, 105.204590f}, {156.899658f, 105.014648f},
        {156.996826f, 104.856689f}, {157.107788f, 104.730469f}, {157.230591f, 104.635986f}, {157.363647f, 104.573975f},
        {157.505371f, 104.543213f}, {157.654175f, 104.544678f}, {157.807983f, 104.577637f}, {157.965332f, 104.642578f},
        {158.124634f, 104.739014f}, {158.124634f, 104.739014f}, {158.486450f, 104.958740f}, {158.854370f, 105.118164f},
        {159.227295f, 105.225830f}, {159.604248f, 105.291504f}, {159.984375f, 105.324463f}, {160.366821f, 105.333008f},
        {160.750732f, 105.326660f}, {161.135254f, 105.314453f}, {161.519287f, 105.305176f}, {161.901855f, 105.308594f},
        {161.901855f, 105.308594f}, {162.255005f, 105.303223f}, {162.565918f, 105.260254f}, {162.830322f, 105.178711f},
        {163.044678f, 105.056396f}, {163.204956f, 104.891357f}, {163.307495f, 104.681641f}, {163.348145f, 104.425537f},
        {163.323120f, 104.120850f}, {163.228638f, 103.765869f}, {163.060791f, 103.358398f}, {163.060791f, 103.358398f},
        {162.951172f, 103.106934f}, {162.862671f, 102.857666f}, {162.796509f, 102.610596f}, {162.753906f, 102.364990f},
        {162.735718f, 102.120361f}, {162.743286f, 101.876465f}, {162.777832f, 101.632568f}, {162.840210f, 101.388672f},
        {162.931763f, 101.143555f}, {163.053711f, 100.897461f}, {163.053711f, 100.897461f}, {162.780396f, 100.665039f},
        {162.497070f, 100.499512f}, {162.205322f, 100.391113f}, {161.906738f, 100.329102f}, {161.603027f, 100.302734f},
        {161.295898f, 100.302246f}, {160.987061f, 100.316895f}, {160.677979f, 100.335938f}, {160.370483f, 100.349365f},
        {160.066162f, 100.346680f}, {160.066162f, 100.346680f}, {159.668579f, 100.331055f}, {159.270874f, 100.321045f},
        {158.873047f, 100.315674f}, {158.474976f, 100.313477f}, {158.076660f, 100.314453f}, {157.678345f, 100.316895f},
        {157.280029f, 100.320068f}, {156.881836f, 100.323242f}, {156.483521f, 100.324951f}, {156.085327f, 100.324951f},
        {156.085327f, 100.324951f}, {155.685791f, 100.327881f}, {155.286255f, 100.329834f}, {154.886475f, 100.331055f},
        {154.486938f, 100.332031f}, {154.087402f, 100.332031f}, {153.687744f, 100.331787f}, {153.288208f, 100.330811f},
        {152.888672f, 100.329346f}, {152.488892f, 100.327393f}, {152.089355f, 100.324951f}, {152.089355f, 100.324951f},
        {150.933228f, 100.347900f}, {149.776855f, 100.350342f}, {148.620361f, 100.339600f}, {147.463745f, 100.323486f},
        {146.307007f, 100.308594f}, {145.150757f, 100.302490f}, {143.994507f, 100.312500f}, {142.838745f, 100.345703f},
        {141.683350f, 100.408936f}, {140.528687f, 100.510010f}, {140.528687f, 100.510010f}, {140.428101f, 100.562012f},
        {140.337280f, 100.623535f}, {140.255249f, 100.693848f}, {140.181641f, 100.772461f}, {140.115112f, 100.858887f},
        {140.055298f, 100.951904f}, {140.001465f, 101.051758f}, {139.952515f, 101.156982f}, {139.907715f, 101.267090f},
        {139.866333f, 101.381836f}, {139.866333f, 101.381836f}, {139.710205f, 101.765381f}, {139.532715f, 102.072754f},
        {139.336670f, 102.305176f}, {139.125366f, 102.463867f}, {138.901733f, 102.549805f}, {138.668945f, 102.564209f},
        {138.430054f, 102.507568f}, {138.187988f, 102.381104f}, {137.945801f, 102.186523f}, {137.706787f, 101.924072f},
        {137.706787f, 101.924072f}, {137.390381f, 101.575928f}, {137.063110f, 101.302979f}, {136.725830f, 101.096680f},
        {136.379272f, 100.948975f}, {136.024292f, 100.851074f}, {135.661621f, 100.794922f}, {135.292358f, 100.771973f},
        {134.917358f, 100.773926f}, {134.537231f, 100.791748f}, {134.153076f, 100.818115f}, {134.153076f, 100.818115f},
        {133.944824f, 100.844482f}, {133.757568f, 100.892578f}, {133.590454f, 100.963379f}, {133.442505f, 101.057861f},
        {133.312744f, 101.176758f}, {133.200439f, 101.321289f}, {133.104614f, 101.491699f}, {133.024170f, 101.689453f},
        {132.958130f, 101.915283f}, {132.905762f, 102.169922f}, {132.905762f, 102.169922f}, {132.782715f, 102.810059f},
        {132.645752f, 103.343506f}, {132.485474f, 103.779785f}, {132.293091f, 104.128418f}, {132.059082f, 104.398438f},
        {131.774414f, 104.598633f}, {131.429932f, 104.738525f}, {131.016479f, 104.827881f}, {130.524902f, 104.875000f},
        {129.946167f, 104.889648f}, {129.946167f, 104.889648f}, {129.297974f, 104.878906f}, {128.650269f, 104.849121f},
        {128.002686f, 104.806885f}, {127.355347f, 104.759521f}, {126.707764f, 104.713623f}, {126.060059f, 104.676514f},
        {125.412231f, 104.655029f}, {124.763916f, 104.655762f}, {124.115112f, 104.686523f}, {123.465576f, 104.753662f},
        {123.465576f, 104.753662f}, {123.291626f, 104.773926f}, {123.117310f, 104.790039f}, {122.942993f, 104.805908f},
        {122.769287f, 104.824951f}, {122.597412f, 104.851318f}, {122.427612f, 104.888428f}, {122.260986f, 104.940186f},
        {122.097900f, 105.010010f}, {121.939453f, 105.101562f}, {121.786011f, 105.219238f}, {121.786011f, 105.219238f},
        {121.687866f, 105.372559f}, {121.608154f, 105.531982f}, {121.544434f, 105.696533f}, {121.494751f, 105.865723f},
        {121.457153f, 106.038574f}, {121.429321f, 106.214600f}, {121.409058f, 106.392578f}, {121.394409f, 106.571777f},
        {121.382935f, 106.751465f}, {121.372925f, 106.931152f}, {121.372925f, 106.931152f}, {121.341553f, 107.247803f},
        {121.284668f, 107.537109f}, {121.201782f, 107.797119f}, {121.092529f, 108.028320f}, {120.956299f, 108.230225f},
        {120.792847f, 108.402100f}, {120.602051f, 108.543213f}, {120.383301f, 108.653809f}, {120.136108f, 108.732910f},
        {119.860229f, 108.780029f}, {119.860229f, 108.780029f}, {119.505127f, 108.838379f}, {119.184326f, 108.934326f},
        {118.897827f, 109.067627f}, {118.645630f, 109.239258f}, {118.427612f, 109.448975f}, {118.243652f, 109.697266f},
        {118.093628f, 109.984863f}, {117.977539f, 110.311523f}, {117.895386f, 110.678223f}, {117.846924f, 111.084717f},
        {117.846924f, 111.084717f}, {117.810913f, 111.368164f}, {117.747925f, 111.625488f}, {117.659302f, 111.858887f},
        {117.547119f, 112.070557f}, {117.412720f, 112.261475f}, {117.257812f, 112.434082f}, {117.084106f, 112.589844f},
        {116.892944f, 112.730713f}, {116.686401f, 112.858398f}, {116.465698f, 112.974609f}, {116.465698f, 112.974609f},
        {116.190552f, 113.115234f}, {115.921387f, 113.266602f}, {115.659302f, 113.429688f}, {115.405640f, 113.606689f},
        {115.161255f, 113.797363f}, {114.927246f, 114.004395f}, {114.704590f, 114.228027f}, {114.494629f, 114.469482f},
        {114.298218f, 114.730957f}, {114.116333f, 115.013184f}, {114.116333f, 115.013184f}, {114.008667f, 115.209961f},
        {113.917358f, 115.410889f}, {113.843628f, 115.614990f}, {113.788818f, 115.822510f}, {113.754272f, 116.032471f},
        {113.740845f, 116.244385f}, {113.750122f, 116.458008f}, {113.783325f, 116.672607f}, {113.841309f, 116.888184f},
        {113.925537f, 117.103516f}, {113.925537f, 117.103516f}, {114.045288f, 117.323730f}, {114.183350f, 117.501953f},
        {114.336792f, 117.641357f}, {114.503296f, 117.743652f}, {114.679688f, 117.812012f}, {114.863037f, 117.848633f},
        {115.050903f, 117.855469f}, {115.240356f, 117.835693f}, {115.428467f, 117.791748f}, {115.612793f, 117.725342f},
        {115.612793f, 117.725342f}, {116.017822f, 117.571045f}, {116.410156f, 117.456055f}, {116.791992f, 117.383789f},
        {117.164673f, 117.358398f}, {117.530640f, 117.382568f}, {117.891479f, 117.459961f}, {118.249390f, 117.593750f},
        {118.606201f, 117.788086f}, {118.963867f, 118.045654f}, {119.324341f, 118.370117f}, {119.324341f, 118.370117f},
        {119.549072f, 118.547119f}, {119.782715f, 118.648193f}, {120.022705f, 118.681152f}, {120.266479f, 118.654297f},
        {120.511475f, 118.575928f}, {120.755127f, 118.453613f}, {120.995239f, 118.295654f}, {121.229004f, 118.110352f},
        {121.453857f, 117.905518f}, {121.667358f, 117.689209f}, {121.667358f, 117.689209f}, {122.674438f, 116.737305f},
        {123.731812f, 115.954590f}, {124.833374f, 115.342041f}, {125.973389f, 114.900146f}, {127.145630f, 114.630371f},
        {128.344238f, 114.533203f}, {129.563477f, 114.609619f}, {130.796997f, 114.860352f}, {132.038940f, 115.286621f},
        {133.283691f, 115.889160f}, {133.283691f, 115.889160f}, {133.448853f, 115.976807f}, {133.616211f, 116.056396f},
        {133.785156f, 116.126709f}, {133.955444f, 116.185303f}, {134.126831f, 116.230225f}, {134.298706f, 116.260010f},
        {134.470825f, 116.273193f}, {134.643066f, 116.267578f}, {134.814819f, 116.241211f}, {134.985962f, 116.192871f},
        {134.985962f, 116.192871f}, {135.703369f, 115.927734f}, {136.411743f, 115.640625f}, {137.110352f, 115.330078f},
        {137.798340f, 114.994873f}, {138.475220f, 114.633545f}, {139.140503f, 114.245361f}, {139.792969f, 113.827881f},
        {140.432617f, 113.380371f}, {141.058472f, 112.901855f}, {141.669800f, 112.390381f}, {141.669800f, 112.390381f},
        {141.799438f, 112.127686f}, {141.887085f, 111.851562f}, {141.942627f, 111.563721f}, {141.976196f, 111.266846f},
        {141.998047f, 110.962158f}, {142.017944f, 110.652832f}, {142.045898f, 110.340332f}, {142.092041f, 110.026855f},
        {142.166382f, 109.714844f}, {142.279053f, 109.406250f}, {142.279053f, 109.406250f}, {142.739014f, 109.898926f},
        {143.162354f, 110.401123f}, {143.543823f, 110.916748f}, {143.879028f, 111.449707f}, {144.162964f, 112.003418f},
        {144.390747f, 112.582275f}, {144.557739f, 113.189941f}, {144.659058f, 113.830322f}, {144.690186f, 114.507080f},
        {144.645996f, 115.224365f}, {144.645996f, 115.224365f}, {144.625610f, 115.401855f}, {144.606323f, 115.581543f},
        {144.589478f, 115.762207f}, {144.577393f, 115.943848f}, {144.571655f, 116.125488f}, {144.574341f, 116.306641f},
        {144.587280f, 116.486816f}, {144.612427f, 116.665039f}, {144.651611f, 116.841064f}, {144.706787f, 117.014160f},
        {144.706787f, 117.014160f}, {144.797119f, 117.229492f}, {144.901123f, 117.425537f}, {145.018677f, 117.599609f},
        {145.149902f, 117.749268f}, {145.294922f, 117.872803f}, {145.453979f, 117.967773f}, {145.627075f, 118.031738f},
        {145.814331f, 118.062500f}, {146.015991f, 118.058105f}, {146.232056f, 118.015869f}, {146.232056f, 118.015869f},
        {146.424194f, 117.947998f}, {146.593262f, 117.857422f}, {146.738037f, 117.745361f}, {146.858276f, 117.613281f},
        {146.952881f, 117.462891f}, {147.021240f, 117.295654f}, {147.062500f, 117.112549f}, {147.076050f, 116.915527f},
        {147.061157f, 116.705811f}, {147.016846f, 116.484863f}, {147.016846f, 116.484863f}, {146.918823f, 116.032471f},
        {146.868652f, 115.604980f}, {146.867065f, 115.203613f}, {146.915771f, 114.830078f}, {147.015625f, 114.486816f},
        {147.168091f, 114.175049f}, {147.374146f, 113.896484f}, {147.635376f, 113.652832f}, {147.952515f, 113.446289f},
        {148.327271f, 113.278320f}, {148.327271f, 113.278320f}, {148.721802f, 113.156006f}, {149.109375f, 113.082764f},
        {149.487915f, 113.060547f}, {149.856323f, 113.091064f}, {150.212891f, 113.176270f}, {150.556030f, 113.318115f},
        {150.884399f, 113.517822f}, {151.196289f, 113.777832f}, {151.490234f, 114.099854f}, {151.764648f, 114.485352f},
        {151.764648f, 114.485352f}, {151.855713f, 114.633301f}, {151.944092f, 114.782959f}, {152.031006f, 114.934326f},
        {152.117432f, 115.085693f}, {152.204102f, 115.237061f}, {152.292236f, 115.386963f}, {152.382690f, 115.535645f},
        {152.476562f, 115.680908f}, {152.574951f, 115.823486f}, {152.678345f, 115.961670f}, {152.678345f, 115.961670f},
        {153.124023f, 116.196777f}, {153.527222f, 116.357666f}, {153.893188f, 116.442139f}, {154.227295f, 116.447266f},
        {154.534790f, 116.370850f}, {154.820679f, 116.210205f}, {155.090576f, 115.963135f}, {155.349365f, 115.627197f},
        {155.602539f, 115.199219f}, {155.855469f, 114.677734f}, {155.855469f, 114.677734f}, {156.029297f, 114.243896f},
        {156.154419f, 113.824951f}, {156.226807f, 113.423340f}, {156.242310f, 113.040527f}, {156.196655f, 112.678223f},
        {156.085815f, 112.338623f}, {155.905640f, 112.023682f}, {155.651978f, 111.734863f}, {155.320801f, 111.474365f},
        {154.907715f, 111.243896f}, {154.907715f, 111.243896f}, {154.757446f, 111.173584f}, {154.603394f, 111.099121f},
        {154.452026f, 111.017578f}, {154.309570f, 110.926270f}, {154.183105f, 110.822510f}, {154.078735f, 110.703857f},
        {154.003418f, 110.567627f}, {153.963745f, 110.410400f}, {153.965820f, 110.230713f}, {154.016724f, 110.024902f},
        {154.016724f, 110.024902f}, {154.112549f, 109.820068f}, {154.234375f, 109.663818f}, {154.377441f, 109.551514f},
        {154.536743f, 109.479004f}, {154.707397f, 109.442871f}, {154.884521f, 109.438232f}, {155.063477f, 109.461426f},
        {155.239014f, 109.508301f}, {155.406616f, 109.574707f}, {155.561035f, 109.656494f}, {155.561035f, 109.656494f},
        {156.035889f, 109.916016f}, {156.523804f, 110.150635f}, {157.011963f, 110.381348f}, {157.488037f, 110.628662f},
        {157.939453f, 110.914062f}, {158.353882f, 111.258301f}, {158.718872f, 111.681885f}, {159.021973f, 112.205566f},
        {159.250854f, 112.850586f}, {159.392822f, 113.638184f}, {159.392822f, 113.638184f}, {159.486694f, 114.120850f},
        {159.654175f, 114.584717f}, {159.884644f, 115.029785f}, {160.167847f, 115.456055f}, {160.493286f, 115.864014f},
        {160.850342f, 116.253418f}, {161.229126f, 116.624756f}, {161.618530f, 116.977539f}, {162.008667f, 117.312744f},
        {162.389038f, 117.630127f}, {162.389038f, 117.630127f}, {162.707886f, 117.845459f}, {163.000366f, 117.949463f},
        {163.267944f, 117.954102f}, {163.510864f, 117.871338f}, {163.730469f, 117.712891f}, {163.927490f, 117.491211f},
        {164.102783f, 117.218262f}, {164.257202f, 116.905762f}, {164.391724f, 116.566162f}, {164.506958f, 116.211670f},
        {164.506958f, 116.211670f}, {164.542725f, 116.062256f}, {164.569458f, 115.903076f}, {164.592773f, 115.739746f},
        {164.619263f, 115.578369f}, {164.654297f, 115.424561f}, {164.703857f, 115.283691f}, {164.774048f, 115.161865f},
        {164.870605f, 115.064453f}, {164.999634f, 114.997559f}, {165.166748f, 114.966797f}, {165.166748f, 114.966797f},
        {165.318115f, 114.976807f}, {165.450317f, 115.022217f}, {165.565674f, 115.097412f}, {165.666992f, 115.197510f},
        {165.756836f, 115.317383f}, {165.837524f, 115.450928f}, {165.911865f, 115.593750f}, {165.982422f, 115.739990f},
        {166.051636f, 115.884521f}, {166.122070f, 116.022217f}, {166.122070f, 116.022217f}, {166.258667f, 116.278076f},
        {166.393066f, 116.535400f}, {166.527466f, 116.791992f}, {166.664307f, 117.046387f}, {166.806519f, 117.296631f},
        {166.956299f, 117.540527f}, {167.116577f, 117.776367f}, {167.289551f, 118.002441f}, {167.477905f, 118.217041f},
        {167.684082f, 118.417969f}, {167.684082f, 118.417969f}, {168.314453f, 118.937744f}, {168.910767f, 119.334229f},
        {169.478882f, 119.606201f}, {170.025024f, 119.752441f}, {170.554810f, 119.771973f}, {171.074585f, 119.663086f},
        {171.590332f, 119.424805f}, {172.107910f, 119.055908f}, {172.633179f, 118.554932f}, {173.172607f, 117.920654f},
        {173.172607f, 117.920654f}, {173.380127f, 117.651855f}, {173.564087f, 117.420654f}, {173.733765f, 117.233887f},
        {173.898560f, 117.099121f}, {174.067871f, 117.024414f}, {174.251221f, 117.016846f}, {174.458008f, 117.084473f},
        {174.697266f, 117.234375f}, {174.978882f, 117.474609f}, {175.312134f, 117.812012f}, {175.312134f, 117.812012f},
        {175.644043f, 118.178711f}, {175.955322f, 118.544434f}, {176.246460f, 118.911865f}, {176.519165f, 119.283936f},
        {176.773804f, 119.663818f}, {177.011719f, 120.054443f}, {177.233765f, 120.458496f}, {177.441162f, 120.879395f},
        {177.634766f, 121.319824f}, {177.815674f, 121.782227f}, {177.815674f, 121.782227f}, {177.993042f, 122.164795f},
        {178.218628f, 122.486084f}, {178.487549f, 122.745117f}, {178.794556f, 122.940918f}, {179.134644f, 123.072998f},
        {179.502686f, 123.140625f}, {179.893555f, 123.142090f}, {180.302368f, 123.077637f}, {180.723877f, 122.945557f},
        {181.153198f, 122.745361f}, {181.153198f, 122.745361f}, {181.594727f, 122.499756f}, {182.033691f, 122.247803f},
        {182.471558f, 121.994141f}, {182.910278f, 121.742676f}, {183.351196f, 121.497070f}, {183.796265f, 121.261963f},
        {184.247070f, 121.041260f}, {184.705322f, 120.839111f}, {185.172607f, 120.659668f}, {185.650757f, 120.507324f},
        {185.650757f, 120.507324f}, {185.805420f, 120.450684f}, {185.946411f, 120.374023f}, {186.074341f, 120.279053f},
        {186.190186f, 120.167236f}, {186.294556f, 120.040039f}, {186.388428f, 119.899170f}, {186.472656f, 119.746582f},
        {186.547974f, 119.582764f}, {186.615479f, 119.410156f}, {186.675659f, 119.230469f}, {186.675659f, 119.230469f},
        {186.754761f, 119.030029f}, {186.851929f, 118.874756f}, {186.964722f, 118.759033f}, {187.091187f, 118.677979f},
        {187.228760f, 118.627441f}, {187.375244f, 118.602295f}, {187.528687f, 118.597656f}, {187.686401f, 118.608398f},
        {187.846313f, 118.630371f}, {188.006348f, 118.657959f}, {188.006348f, 118.657959f}, {188.157349f, 118.696289f},
        {188.289185f, 118.751709f}, {188.403198f, 118.824463f}, {188.501221f, 118.913086f}, {188.584351f, 119.017578f},
        {188.654541f, 119.137939f}, {188.713257f, 119.272705f}, {188.761963f, 119.422119f}, {188.802124f, 119.585449f},
        {188.835449f, 119.762695f}, {188.835449f, 119.762695f}, {188.990967f, 120.505127f}, {189.197021f, 121.164795f},
        {189.454346f, 121.742432f}, {189.764771f, 122.237793f}, {190.129150f, 122.651123f}, {190.548828f, 122.982666f},
        {191.025024f, 123.232910f}, {191.558960f, 123.401367f}, {192.151733f, 123.489014f}, {192.804932f, 123.495361f},
        {192.804932f, 123.495361f}, {193.365234f, 123.463135f}, {193.923584f, 123.416260f}, {194.476440f, 123.345459f},
        {195.021484f, 123.242676f}, {195.555664f, 123.098389f}, {196.076294f, 122.904297f}, {196.580688f, 122.651611f},
        {197.065796f, 122.331543f}, {197.528931f, 121.935303f}, {197.967285f, 121.454102f}, {197.967285f, 121.454102f},
        {198.221680f, 121.182129f}, {198.492920f, 120.971191f}, {198.778076f, 120.816895f}, {199.074097f, 120.713867f},
        {199.378784f, 120.657227f}, {199.688843f, 120.642334f}, {200.001587f, 120.664307f}, {200.314575f, 120.718506f},
        {200.624756f, 120.799561f}, {200.929443f, 120.903076f}, {200.929443f, 120.903076f}, {201.196777f, 121.040283f},
        {201.397583f, 121.219238f}, {201.540405f, 121.433105f}, {201.633789f, 121.675537f}, {201.686768f, 121.939209f},
        {201.708008f, 122.218262f}, {201.706177f, 122.505371f}, {201.690063f, 122.793945f}, {201.668335f, 123.077637f},
        {201.649780f, 123.349609f}, {201.649780f, 123.349609f}, {201.650513f, 123.953125f}, {201.716187f, 124.510498f},
        {201.841187f, 125.025635f}, {202.019409f, 125.503662f}, {202.245361f, 125.949463f}, {202.513184f, 126.366455f},
        {202.817017f, 126.759033f}, {203.151123f, 127.132568f}, {203.509644f, 127.490967f}, {203.886719f, 127.838623f},
        {203.886719f, 127.838623f}, {204.352295f, 127.992920f}, {204.806152f, 128.073486f}, {205.246094f, 128.085693f},
        {205.671265f, 128.032959f}, {206.079712f, 127.919189f}, {206.470337f, 127.748779f}, {206.841309f, 127.525635f},
        {207.191284f, 127.253662f}, {207.518677f, 126.936768f}, {207.821899f, 126.579346f}, {207.821899f, 126.579346f},
        {208.211792f, 126.124268f}, {208.609863f, 125.757568f}, {209.015015f, 125.475342f}, {209.427368f, 125.276611f},
        {209.846436f, 125.157959f}, {210.271606f, 125.116943f}, {210.702515f, 125.150635f}, {211.139038f, 125.256592f},
        {211.580444f, 125.431885f}, {212.026367f, 125.674561f}, {212.026367f, 125.674561f}, {212.481323f, 125.928467f},

        {212.939819f, 126.138428f}, {213.401245f, 126.309326f}, {213.866089f, 126.446533f}, {214.334229f, 126.555420f},
        {214.805908f, 126.640381f}, {215.281128f, 126.707764f}, {215.759644f, 126.762939f}, {216.241699f, 126.810303f},
        {216.727539f, 126.855713f}, {216.727539f, 126.855713f}, {217.140015f, 126.894775f}, {217.554688f, 126.940186f},
        {217.966797f, 127.001221f}, {218.372437f, 127.087158f}, {218.767334f, 127.207275f}, {219.147217f, 127.370850f},
        {219.507935f, 127.586670f}, {219.845337f, 127.864990f}, {220.154907f, 128.214111f}, {220.432739f, 128.644287f},
        {220.432739f, 129.447998f}, {220.432739f, 129.447998f}, {220.702637f, 129.944092f}, {221.013184f, 130.338135f},
        {221.358765f, 130.644287f}, {221.733887f, 130.875244f}, {222.133301f, 131.045654f}, {222.551636f, 131.168213f},
        {222.983276f, 131.257568f}, {223.422974f, 131.326904f}, {223.865479f, 131.389404f}, {224.304932f, 131.459229f},
        {224.304932f, 131.459229f}, {224.340088f, 131.539307f}, {224.375488f, 131.619873f}, {224.410767f, 131.699951f},
        {224.446045f, 131.780518f}, {224.481323f, 131.861084f}, {224.516479f, 131.941162f}, {224.551758f, 132.022217f},
        {224.587036f, 132.102295f}, {224.622192f, 132.182861f}, {224.657349f, 132.262939f}, {224.657349f, 132.262939f},
        {224.780151f, 132.491943f}, {224.908691f, 132.716553f}, {225.044800f, 132.930420f}, {225.191284f, 133.126221f},
        {225.350220f, 133.296631f}, {225.524170f, 133.434814f}, {225.715454f, 133.533936f}, {225.926270f, 133.586182f},
        {226.159058f, 133.585205f}, {226.416504f, 133.523682f}, {226.416504f, 133.523682f}, {226.697266f, 133.400635f},
        {226.941895f, 133.242920f}, {227.152344f, 133.052490f}, {227.330322f, 132.832764f}, {227.477905f, 132.587158f},
        {227.596924f, 132.317139f}, {227.689331f, 132.026611f}, {227.756958f, 131.717529f}, {227.801758f, 131.393799f},
        {227.825562f, 131.056885f},
    };

    Vec2 sprite_polygon_crash[] = {
        {60.000000f, 11.400000f}, {60.400002f, 15.500000f}, {62.000000f, 16.100000f}, {62.000000f, 16.900000f},
        {65.000000f, 16.500000f}, {65.000000f, 14.100000f}, {64.000000f, 12.700000f}, {64.000000f, 7.300000f},
        {65.300003f, 6.000000f},  {67.199997f, 6.000000f},  {71.199997f, 9.000000f},  {73.300003f, 9.000000f},
        {73.699997f, 10.000000f}, {77.400002f, 10.600000f}, {77.900002f, 12.700000f}, {85.000000f, 16.700001f},
        {85.000000f, 20.299999f}, {82.699997f, 22.000000f}, {75.599998f, 22.400000f}, {75.699997f, 22.500000f},
        {71.400002f, 23.900000f}, {71.000000f, 30.000000f}, {72.699997f, 33.500000f}, {80.000000f, 34.900002f},
        {84.500000f, 34.500000f}, {84.500000f, 33.700001f}, {83.000000f, 33.000000f}, {78.500000f, 34.500000f},
        {74.099998f, 32.400002f}, {72.900002f, 29.200001f}, {76.900002f, 27.500000f}, {90.699997f, 27.500000f},
        {92.500000f, 29.299999f}, {92.500000f, 40.500000f}, {91.500000f, 45.700001f}, {89.699997f, 47.500000f},
        {86.699997f, 47.500000f}, {84.099998f, 42.299999f}, {80.599998f, 40.299999f}, {80.099998f, 39.000000f},
        {78.199997f, 39.400002f}, {77.300003f, 41.000000f}, {75.400002f, 41.000000f}, {69.699997f, 38.400002f},
        {68.699997f, 37.000000f}, {67.599998f, 37.000000f}, {67.099998f, 34.000000f}, {66.000000f, 34.000000f},
        {66.000000f, 32.900002f}, {64.500000f, 32.400002f}, {64.500000f, 31.000000f}, {63.500000f, 31.000000f},
        {63.500000f, 30.000000f}, {54.500000f, 30.000000f}, {52.900002f, 30.799999f}, {52.299999f, 31.500000f},
        {57.599998f, 32.000000f}, {62.799999f, 34.099998f}, {64.000000f, 35.299999f}, {64.400002f, 37.599998f},
        {66.000000f, 39.299999f}, {66.000000f, 43.799999f}, {65.000000f, 44.200001f}, {65.000000f, 45.700001f},
        {63.200001f, 47.500000f}, {60.700001f, 47.500000f}, {59.500000f, 44.599998f}, {59.500000f, 41.599998f},
        {58.700001f, 40.400002f}, {55.299999f, 39.000000f}, {55.299999f, 38.900002f}, {50.400002f, 38.500000f},
        {50.000000f, 40.700001f}, {50.900002f, 41.200001f}, {51.400002f, 43.700001f}, {52.500000f, 44.200001f},
        {52.500000f, 48.000000f}, {48.799999f, 48.000000f}, {44.400002f, 45.000000f}, {42.500000f, 45.400002f},
        {42.900002f, 48.700001f}, {44.400002f, 49.700001f}, {44.900002f, 51.500000f}, {45.799999f, 51.500000f},
        {47.500000f, 54.400002f}, {46.900002f, 58.500000f}, {40.799999f, 58.500000f}, {36.700001f, 53.400002f},
        {31.900000f, 52.000000f}, {26.200001f, 52.400002f}, {25.000000f, 54.099998f}, {25.000000f, 56.700001f},
        {26.000000f, 57.799999f}, {26.000000f, 59.200001f}, {27.400000f, 60.299999f}, {31.799999f, 56.000000f},
        {33.200001f, 56.000000f}, {35.000000f, 57.799999f}, {35.000000f, 59.500000f}, {38.700001f, 67.000000f},
        {39.599998f, 67.000000f}, {40.099998f, 65.599998f}, {41.500000f, 65.000000f}, {42.000000f, 63.200001f},
        {44.299999f, 61.000000f}, {45.700001f, 61.000000f}, {47.400002f, 62.700001f}, {50.700001f, 69.500000f},
        {54.099998f, 70.500000f}, {58.500000f, 70.500000f}, {60.000000f, 69.699997f}, {61.000000f, 66.800003f},
        {61.000000f, 63.700001f}, {60.000000f, 63.299999f}, {60.000000f, 61.000000f}, {58.700001f, 58.400002f},
        {56.700001f, 58.000000f}, {55.000000f, 59.799999f}, {55.000000f, 65.500000f}, {51.599998f, 65.500000f},
        {51.000000f, 63.700001f}, {50.000000f, 63.299999f}, {50.000000f, 57.799999f}, {56.299999f, 51.500000f},
        {62.500000f, 52.000000f}, {62.500000f, 53.000000f}, {63.700001f, 53.000000f}, {65.699997f, 54.500000f},
        {67.300003f, 54.500000f}, {68.800003f, 53.299999f}, {68.000000f, 51.099998f}, {68.000000f, 47.799999f},
        {72.800003f, 44.000000f}, {76.699997f, 44.000000f}, {78.300003f, 45.500000f}, {80.500000f, 46.099998f},
        {80.500000f, 48.299999f}, {76.500000f, 51.200001f}, {76.500000f, 53.799999f}, {78.199997f, 55.900002f},
        {82.500000f, 55.500000f}, {82.500000f, 49.500000f}, {85.199997f, 49.500000f}, {86.300003f, 50.500000f},
        {93.500000f, 50.500000f}, {93.000000f, 67.900002f}, {94.000000f, 77.699997f}, {92.500000f, 79.199997f},
        {92.500000f, 82.300003f}, {95.000000f, 85.800003f}, {95.000000f, 89.199997f}, {93.699997f, 90.500000f},
        {90.699997f, 90.500000f}, {90.199997f, 89.500000f}, {89.199997f, 89.500000f}, {90.699997f, 90.900002f},
        {94.699997f, 90.500000f}, {95.500000f, 89.000000f}, {95.500000f, 85.599998f}, {93.000000f, 81.599998f},
        {93.000000f, 79.300003f}, {94.400002f, 77.699997f}, {93.500000f, 70.000000f}, {94.000000f, 50.500000f},
        {99.500000f, 50.500000f}, {99.500000f, 95.500000f}, {98.500000f, 95.500000f}, {98.500000f, 97.000000f},
        {13.000000f, 96.500000f}, {13.000000f, 84.000000f}, {86.000000f, 84.000000f}, {86.000000f, 80.800003f},
        {87.500000f, 79.099998f}, {88.000000f, 75.900002f}, {88.000000f, 69.699997f}, {86.099998f, 64.000000f},
        {83.300003f, 64.000000f}, {81.300003f, 62.500000f}, {78.500000f, 62.500000f}, {78.500000f, 60.799999f},
        {73.800003f, 59.000000f}, {69.699997f, 59.000000f}, {68.199997f, 59.500000f}, {66.400002f, 61.599998f},
        {66.000000f, 65.099998f}, {66.900002f, 70.199997f}, {69.400002f, 73.199997f}, {71.000000f, 74.000000f},
        {75.800003f, 74.400002f}, {78.000000f, 73.599998f}, {78.000000f, 72.099998f}, {75.000000f, 72.599998f},
        {75.000000f, 68.300003f}, {76.300003f, 67.000000f}, {80.300003f, 67.000000f}, {82.500000f, 70.300003f},
        {82.500000f, 74.199997f}, {79.300003f, 77.500000f}, {70.500000f, 79.500000f}, {57.400002f, 79.000000f},
        {54.700001f, 77.900002f}, {52.299999f, 75.000000f}, {50.799999f, 75.000000f}, {48.200001f, 72.500000f},
        {42.700001f, 72.500000f}, {39.099998f, 73.800003f}, {39.400002f, 74.599998f}, {42.000000f, 75.699997f},
        {42.000000f, 79.000000f}, {34.900002f, 79.400002f}, {34.400002f, 82.400002f}, {30.000000f, 83.000000f},
        {27.100000f, 82.400002f}, {26.500000f, 79.300003f}, {28.799999f, 77.000000f}, {31.200001f, 76.500000f},
        {33.900002f, 74.300003f}, {32.500000f, 68.800003f}, {31.299999f, 68.000000f}, {26.400000f, 68.000000f},
        {17.600000f, 65.900002f}, {16.900000f, 63.000000f}, {19.500000f, 63.000000f}, {19.500000f, 62.599998f},
        {18.200001f, 61.000000f}, {17.299999f, 61.000000f}, {16.000000f, 62.599998f}, {16.000000f, 65.199997f},
        {20.000000f, 68.800003f}, {20.000000f, 72.199997f}, {17.700001f, 74.599998f}, {13.200000f, 73.400002f},
        {12.000000f, 71.099998f}, {12.000000f, 64.300003f}, {13.000000f, 63.200001f}, {13.000000f, 62.500000f},
        {12.200000f, 62.500000f}, {9.300000f, 64.900002f},  {8.500000f, 66.500000f},  {8.500000f, 70.300003f},
        {10.400000f, 76.199997f}, {13.500000f, 78.000000f}, {18.400000f, 78.000000f}, {21.600000f, 77.000000f},
        {25.000000f, 73.699997f}, {25.000000f, 72.500000f}, {28.000000f, 72.500000f}, {28.000000f, 77.199997f},
        {25.799999f, 79.400002f}, {22.200001f, 81.000000f}, {20.200001f, 83.500000f}, {10.900000f, 83.500000f},
        {8.600000f, 82.400002f},  {6.100000f, 77.300003f},  {6.100000f, 77.400002f},  {2.100000f, 73.300003f},
        {0.000000f, 68.599998f},  {0.000000f, 65.000000f},  {0.100000f, 64.699997f},  {1.000000f, 64.199997f},
        {1.600000f, 62.200001f},  {3.700000f, 60.599998f},  {5.200000f, 57.500000f},  {10.000000f, 57.500000f},
        {11.300000f, 56.799999f}, {10.200000f, 55.000000f}, {7.500000f, 55.599998f},  {7.500000f, 52.200001f},
        {6.500000f, 51.799999f},  {6.500000f, 45.900002f},  {8.000000f, 38.700001f},  {10.800000f, 36.500000f},
        {17.600000f, 37.000000f}, {22.000000f, 39.500000f}, {27.500000f, 39.500000f}, {29.000000f, 38.700001f},
        {30.000000f, 35.400002f}, {30.000000f, 31.600000f}, {29.200001f, 30.500000f}, {27.400000f, 30.500000f},
        {26.900000f, 32.299999f}, {22.700001f, 35.500000f}, {9.300000f, 35.000000f},  {4.500000f, 30.200001f},
        {4.000000f, 23.400000f},  {5.100000f, 20.100000f},  {6.000000f, 19.700001f},  {6.600000f, 18.000000f},
        {8.200000f, 18.000000f},  {8.700000f, 17.000000f},  {11.000000f, 17.000000f}, {13.900000f, 15.500000f},
        {20.200001f, 15.500000f}, {23.500000f, 18.200001f}, {25.000000f, 27.100000f}, {25.000000f, 21.400000f},
        {26.500000f, 18.500000f}, {26.500000f, 16.200001f}, {24.500000f, 15.300000f}, {24.000000f, 11.700000f},
        {23.000000f, 11.300000f}, {23.000000f, 10.500000f}, {22.299999f, 10.500000f}, {20.600000f, 8.900000f},
        {17.799999f, 8.500000f},  {15.200000f, 6.000000f},  {14.300000f, 6.000000f},  {13.900000f, 6.900000f},
        {9.900000f, 8.700000f},   {9.000000f, 12.700000f},  {7.300000f, 15.000000f},  {4.100000f, 15.000000f},
        {3.500000f, 9.900000f},   {4.600000f, 7.200000f},   {9.800000f, 4.000000f},   {19.700001f, 3.500000f},
        {20.799999f, 4.500000f},  {22.299999f, 4.500000f},  {22.700001f, 5.500000f},  {26.299999f, 6.000000f},
        {26.700001f, 7.000000f},  {29.799999f, 8.100000f},  {32.500000f, 12.900000f}, {32.000000f, 20.100000f},
        {31.000000f, 22.900000f}, {32.700001f, 25.000000f}, {34.000000f, 25.000000f}, {34.000000f, 26.200001f},
        {35.900002f, 27.100000f}, {37.400002f, 31.700001f}, {39.500000f, 32.700001f}, {39.500000f, 35.200001f},
        {38.299999f, 37.000000f}, {35.099998f, 37.400002f}, {33.500000f, 38.700001f}, {33.500000f, 42.900002f},
        {30.100000f, 44.000000f}, {20.200001f, 44.000000f}, {16.900000f, 45.400002f}, {14.000000f, 48.299999f},
        {14.000000f, 51.299999f}, {16.200001f, 54.900002f}, {19.700001f, 54.500000f}, {20.500000f, 53.299999f},
        {20.500000f, 50.500000f}, {18.200001f, 46.000000f}, {29.100000f, 46.500000f}, {37.200001f, 48.900002f},
        {37.700001f, 48.400002f}, {34.500000f, 44.700001f}, {34.500000f, 42.000000f}, {35.700001f, 42.000000f},
        {37.299999f, 40.500000f}, {45.500000f, 40.900002f}, {45.500000f, 37.799999f}, {46.599998f, 36.599998f},
        {45.099998f, 37.500000f}, {42.000000f, 37.500000f}, {41.500000f, 31.900000f}, {42.200001f, 30.500000f},
        {45.299999f, 30.500000f}, {45.700001f, 29.600000f}, {49.099998f, 28.700001f}, {47.500000f, 26.700001f},
        {46.500000f, 23.100000f}, {46.500000f, 18.299999f}, {48.299999f, 16.000000f}, {51.500000f, 16.000000f},
        {51.900002f, 21.700001f}, {56.700001f, 25.000000f}, {62.400002f, 25.000000f}, {65.500000f, 24.100000f},
        {65.500000f, 23.200001f}, {63.299999f, 21.500000f}, {55.599998f, 22.600000f}, {54.500000f, 16.200001f},
        {53.599998f, 15.900000f}, {52.599998f, 12.900000f}, {51.200001f, 11.500000f}, {46.599998f, 11.500000f},
        {44.099998f, 11.900000f}, {40.000000f, 14.700000f}, {40.000000f, 16.700001f}, {40.500000f, 17.200001f},
        {41.500000f, 16.200001f}, {41.500000f, 14.000000f}, {43.200001f, 14.000000f}, {46.000000f, 16.799999f},
        {46.000000f, 20.799999f}, {44.400002f, 21.700001f}, {43.400002f, 27.100000f}, {38.200001f, 25.900000f},
        {35.500000f, 22.200001f}, {36.000000f, 9.100000f},  {38.700001f, 8.500000f},  {39.200001f, 7.500000f},
        {41.000000f, 7.500000f},  {46.299999f, 4.500000f},  {50.900002f, 4.000000f},  {53.400002f, 2.500000f},
        {56.900002f, 2.500000f},
    };

    DrawNodeEx* drawNode[3];
    for (int i = 0; i < 3; i++)
    {
        drawNode[i] = DrawNodeEx::create();
        addChild(drawNode[i]);
    }

    // draw a solid circle
    drawNode[1]->drawSolidCircle(VisibleRect::center() + Vec2(140.0f, 0.0f), 40, AX_DEGREES_TO_RADIANS(90), 30, 2.0f,
                                 2.0f, Color4F::BLUE);

    drawNode[1]->drawSolidCircle(VisibleRect::center() + Vec2(-40.0f, 0.0f), 40, AX_DEGREES_TO_RADIANS(90), 30, 2.0f,
                                 2.0f, Color4F::WHITE);

    drawNode[0]->setPosition(Vec2(-30, -20));
    // drawNode[0]->drawPolygon(vertices24, sizeof(vertices24) / sizeof(vertices24[0]), Color4F::RED, 0.3f,
    //                          Color4F::GREEN);

    drawNode[1]->drawPolygon(vertices1, sizeof(vertices1) / sizeof(vertices1[0]), Color4F::YELLOW, 0.3f, Color4F::RED);
    drawNode[1]->drawPolygon(vertices2, sizeof(vertices2) / sizeof(vertices2[0]), Color4F::YELLOW, 0.3f, Color4F::RED);
    drawNode[1]->drawPolygon(vertices3, sizeof(vertices3) / sizeof(vertices3[0]), Color4F::YELLOW, 0.3f, Color4F::RED);
    drawNode[1]->drawPolygon(vertices4, sizeof(vertices4) / sizeof(vertices4[0]), Color4F::YELLOW, 0.3f, Color4F::RED);
    drawNode[1]->drawPolygon(vertices5, sizeof(vertices5) / sizeof(vertices5[0]), Color4F::YELLOW, 0.3f, Color4F::RED);
    drawNode[1]->drawPolygon(vertices6, sizeof(vertices6) / sizeof(vertices6[0]), Color4F::YELLOW, 0.3f, Color4F::RED);
    drawNode[1]->drawPolygon(vertices7, sizeof(vertices7) / sizeof(vertices7[0]), Color4F::YELLOW, 0.3f, Color4F::RED);
    drawNode[1]->drawPolygon(vertices8, sizeof(vertices8) / sizeof(vertices8[0]), Color4F::YELLOW, 0.3f, Color4F::RED);
    drawNode[1]->drawPolygon(vertices9, sizeof(vertices9) / sizeof(vertices9[0]), Color4F::YELLOW, 0.3f, Color4F::RED);
    drawNode[1]->drawPolygon(vertices10, sizeof(vertices10) / sizeof(vertices10[0]), Color4F::YELLOW, 0.3f,
                             Color4F::RED);
    drawNode[1]->drawPolygon(vertices11, sizeof(vertices11) / sizeof(vertices11[0]), Color4F::YELLOW, 0.3f,
                             Color4F::RED);
    drawNode[1]->drawPolygon(vertices12, sizeof(vertices12) / sizeof(vertices12[0]), Color4F::WHITE, 0.3f,
                             Color4F::RED);
    drawNode[1]->drawPolygon(vertices13, sizeof(vertices13) / sizeof(vertices13[0]), Color4F::YELLOW, 0.3f,
                             Color4F::RED);
    drawNode[1]->drawPolygon(vertices14, sizeof(vertices14) / sizeof(vertices14[0]), Color4F::YELLOW, 0.3f,
                             Color4F::RED);
    drawNode[1]->drawPolygon(vertices15, sizeof(vertices15) / sizeof(vertices15[0]), Color4F::YELLOW, 0.3f,
                             Color4F::RED);
    drawNode[1]->drawPolygon(vertices16, sizeof(vertices16) / sizeof(vertices16[0]), Color4F::YELLOW, 0.3f,
                             Color4F::RED);
    drawNode[1]->drawPolygon(vertices17, sizeof(vertices17) / sizeof(vertices17[0]), Color4F::YELLOW, 0.3f,
                             Color4F::RED);
    drawNode[1]->drawPolygon(vertices18, sizeof(vertices18) / sizeof(vertices18[0]), Color4F::YELLOW, 0.3f,
                             Color4F::RED);
    drawNode[1]->drawPolygon(vertices19, sizeof(vertices19) / sizeof(vertices19[0]), Color4F::YELLOW, 0.3f,
                             Color4F::RED);
    drawNode[1]->drawPolygon(vertices20, sizeof(vertices20) / sizeof(vertices20[0]), Color4F::YELLOW, 0.3f,
                             Color4F::RED);
    drawNode[2]->setPosition(Vec2(0, -10));
    drawNode[2]->setLocalZOrder(5);
    drawNode[2]->drawPolygon(vertices21, sizeof(vertices21) / sizeof(vertices21[0]), Color4F::GREEN, 0.3f,
                             Color4F::YELLOW);

    drawNode[2]->drawPolygon(vertices24, sizeof(vertices24) / sizeof(vertices24[0]), Color4F::AX_TRANSPARENT, 5.3f,
                             Color4F::RED);
}

string DrawNode2FilledPolygonTest::title() const
{
    return "Filled Polygon Test #2";
}

string DrawNode2FilledPolygonTest::subtitle() const
{
    return "";
}

// DrawMethodesThicknessTest
DrawNodePart1Test::DrawNodePart1Test()
{
    _currentSeletedItemIndex = 0;

    auto director = Director::getInstance();
    director->setClearColor(Color4F(0, 0, 0, 0));
    auto origin = director->getVisibleOrigin();
    auto size   = director->getVisibleSize();
    Vec2 center(origin.x + size.width / 2 + 50, origin.y + size.height / 2);

    auto listview = createListView();
    listview->setPosition(Vec2(0.0f, 90.0f));
    addChild(listview);

    draw = DrawNodeEx::create();
    draw->setScale(0.5);
    draw->setPosition(size / 4);
    addChild(draw);

    draw1 = DrawNode::create();
    draw1->setScale(0.5);
    draw1->setPosition(size / 4);
    addChild(draw1);

    auto thicknessSlider = createSlider();
    thicknessSlider->setPosition(Vec2(center.x, 60.0f));
    addChild(thicknessSlider);

    label = Label::createWithTTF("Thickness: ", "fonts/Marker Felt.ttf", 10);
    label->setPosition(Vec2(Vec2(center.x, 80.0f)));
    this->addChild(label, 1);

    scheduleUpdate();
}

std::string DrawNodePart1Test::title() const
{
    return "DrawNode #1 Scale/Rotation/LineWidth/Position Test";
}

string DrawNodePart1Test::subtitle() const
{
    return "";
}

ax::ui::Slider* DrawNodePart1Test::createSlider()
{
    auto slider = ui::Slider::create();
    slider->setTouchEnabled(true);
    slider->loadBarTexture("cocosui/sliderTrack.png");
    slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider->addEventListener(AX_CALLBACK_2(DrawNodePart1Test::sliderCallback, this));
    slider->setTag(101);
    slider->setPercent(10);

    return slider;
}

void DrawNodePart1Test::listviewCallback(ax::Ref* sender, ax::ui::ListView::EventType type)
{
    // clear all text to white
    auto listview = static_cast<ax::ui::ListView*>(sender);
    for (auto&& item : listview->getItems())
    {
        static_cast<ax::ui::Text*>(item)->setColor(ax::Color3B::WHITE);
    }
    _currentSeletedItemIndex = (int)listview->getCurSelectedIndex();
    listview->getItem(_currentSeletedItemIndex)->setColor(ax::Color3B::RED);
    isDirty   = true;
    verticess = makePolygons();
}

void DrawNodePart1Test::sliderCallback(ax::Ref* sender, ax::ui::Slider::EventType type)
{
    if (type == ax::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        auto slider = dynamic_cast<ax::ui::Slider*>(sender);
        thickness   = slider->getPercent() * 0.1f;
    }
    isDirty = true;
}

ax::ui::ListView* DrawNodePart1Test::createListView()
{
    auto listview = ax::ui::ListView::create();

    auto drawLine = ax::ui::Text::create();
    drawLine->setString("drawLine");
    drawLine->setTouchEnabled(true);
    listview->pushBackCustomItem(drawLine);

    auto drawRect = ax::ui::Text::create();
    drawRect->setString("drawRect");
    drawRect->setTouchEnabled(true);
    listview->pushBackCustomItem(drawRect);

    auto drawCircle = ax::ui::Text::create();
    drawCircle->setString("drawCircle");
    drawCircle->setTouchEnabled(true);
    listview->pushBackCustomItem(drawCircle);

    auto drawQuadBezier = ax::ui::Text::create();
    drawQuadBezier->setString("drawQuadBezier");
    drawQuadBezier->setTouchEnabled(true);
    listview->pushBackCustomItem(drawQuadBezier);

    auto drawCubicBezier = ax::ui::Text::create();
    drawCubicBezier->setString("drawCubicBezier");
    drawCubicBezier->setTouchEnabled(true);
    listview->pushBackCustomItem(drawCubicBezier);

    auto drawCardinalSpline = ax::ui::Text::create();
    drawCardinalSpline->setString("drawCardinalSpline");
    drawCardinalSpline->setTouchEnabled(true);
    listview->pushBackCustomItem(drawCardinalSpline);

    auto drawCatmullRom = ax::ui::Text::create();
    drawCatmullRom->setString("drawCatmullRom");
    drawCatmullRom->setTouchEnabled(true);
    listview->pushBackCustomItem(drawCatmullRom);

    auto drawPoly = ax::ui::Text::create();
    drawPoly->setString("drawPoly");
    drawPoly->setTouchEnabled(true);
    listview->pushBackCustomItem(drawPoly);

    auto drawPolygon = ax::ui::Text::create();
    drawPolygon->setString("drawPolygon");
    drawPolygon->setTouchEnabled(true);
    listview->pushBackCustomItem(drawPolygon);

    listview->setContentSize(drawLine->getContentSize() * 9);
    listview->setCurSelectedIndex(0);
    listview->setTouchEnabled(true);
    listview->addEventListener(
        (ui::ListView::ccListViewCallback)AX_CALLBACK_2(DrawNodePart1Test::listviewCallback, this));
    listview->setTag(100);

    listview->getItem(_currentSeletedItemIndex)->setColor(Color3B::RED);

    return listview;
}

void DrawNodePart1Test::update(float dt)
{
    if (isDirty)
    {
        drawAll();
        isDirty = false;
    }
}

void DrawNodePart1Test::drawAll()
{

    auto s = Director::getInstance()->getWinSize();

    draw->clear();
    label->setString("Thickness: (" + Value(thickness).asString() + ")");

    switch (_currentSeletedItemIndex)
    {
    case 0:
    {
        // drawLine
        draw->drawLine(Vec2(200, 200), Vec2(s.width - 200, s.height - 200), Color4F(1.0, 0.0, 0.0, 1.0), thickness);
        draw->drawLine(Vec2(300, 320), Vec2(s.width - 200, s.height - 200), Color4F(1.0, 1.0, 0.0, 1.0), thickness);
        break;
    }
    case 1:
    {
        // drawRect
        draw->drawRect(Vec2(23, 23), Vec2(7, 7), Color4F(1, 1, 0, 1), thickness);
        draw->drawRect(Vec2(15, 30), Vec2(30, 15), Vec2(15, 0), Vec2(0, 15),
                       Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1), thickness);
        draw->drawRect(Vec2(123, 123), Vec2(227, 227), Color4F(1, 1, 0, 1), thickness);
        draw->drawRect(Vec2(115, 130), Vec2(130, 115), Vec2(115, 100), Vec2(100, 115), Color4F::MAGENTA, thickness);
        break;
    }
    case 2:
    {
        // drawCircle
        draw->drawCircle(VisibleRect::center() + Vec2(140, 0), 100, AX_DEGREES_TO_RADIANS(90), 50, true, 1.0f, 2.0f,
                         Color4F(1.0f, 0.0f, 0.0f, 0.5f), thickness);
        draw->drawCircle(VisibleRect::center() - Vec2(140, 0), 50, AX_DEGREES_TO_RADIANS(90), 30, true,
                         Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f), thickness);
        break;
    }
    case 3:
    {
        // drawCubicBezier
        draw->drawQuadBezier(Vec2(s.width - 150, s.height - 150), Vec2(s.width - 70, s.height - 10),
                             Vec2(s.width - 10, s.height - 10), 10, Color4F::BLUE, thickness);
        draw->drawQuadBezier(Vec2(0.0f + 100, s.height - 100), Vec2(s.width / 2, s.height / 2),
                             Vec2(s.width - 100, s.height - 100), 50, Color4F::RED, thickness);
        break;
    }
    case 4:
    {
        // drawCubicBezier
        draw->drawCubicBezier(VisibleRect::center(), Vec2(VisibleRect::center().x + 30, VisibleRect::center().y + 50),
                              Vec2(VisibleRect::center().x + 60, VisibleRect::center().y - 50), VisibleRect::right(),
                              100, Color4F::WHITE, thickness);
        draw->drawCubicBezier(Vec2(s.width - 250, 40.0f), Vec2(s.width - 70, 100.0f), Vec2(s.width - 30, 250.0f),
                              Vec2(s.width - 10, s.height - 50), 10, Color4F::GRAY, thickness);
        break;
    }
    case 5:
    {
        // drawCardinalSpline
        auto array = ax::PointArray::create(20);
        array->addControlPoint(Vec2(0.0f, 0.0f));
        array->addControlPoint(Vec2(80.0f, 80.0f));
        array->addControlPoint(Vec2(s.width - 80, 80.0f));
        array->addControlPoint(Vec2(s.width - 80, s.height - 80));
        array->addControlPoint(Vec2(80.0f, s.height - 80));
        array->addControlPoint(Vec2(80.0f, 80.0f));
        array->addControlPoint(Vec2(s.width / 2, s.height / 2));
        draw->drawCardinalSpline(array, 0.5f, 50, Color4F::MAGENTA, thickness);

        auto array2 = ax::PointArray::create(20);
        array2->addControlPoint(Vec2(s.width / 2, 80.0f));
        array2->addControlPoint(Vec2(s.width - 80, 80.0f));
        array2->addControlPoint(Vec2(s.width - 80, s.height - 80));
        array2->addControlPoint(Vec2(s.width / 2, s.height - 80));
        array2->addControlPoint(Vec2(s.width / 2, 80.0f));
        draw->drawCardinalSpline(array2, 5.0f, 50, Color4F::ORANGE, thickness);
        break;
    }
    case 6:
    {
        // drawCatmullRom
        auto array2 = ax::PointArray::create(20);
        array2->addControlPoint(Vec2(s.width / 2, 80.0f));
        array2->addControlPoint(Vec2(s.width - 80, 80.0f));
        array2->addControlPoint(Vec2(s.width - 80, s.height - 80));
        array2->addControlPoint(Vec2(s.width / 2, s.height - 80));
        array2->addControlPoint(Vec2(s.width / 2, 80.0f));
        draw->drawCatmullRom(array2, 50, Color4F::ORANGE, thickness);

        auto array = ax::PointArray::create(20);
        array->addControlPoint(Vec2(0.0f, 0.0f));
        array->addControlPoint(Vec2(80.0f, 80.0f));
        array->addControlPoint(Vec2(s.width - 80, 80.0f));
        array->addControlPoint(Vec2(s.width - 80, s.height - 80));
        array->addControlPoint(Vec2(80.0f, s.height - 80));
        array->addControlPoint(Vec2(80.0f, 80.0f));
        array->addControlPoint(Vec2(s.width / 2, s.height / 2));
        draw->drawCatmullRom(array, 50, Color4F::MAGENTA, thickness);
        break;
    }
    case 7:
    {
        // drawPoly
        // for (int n = 0; n < 10; n++)
        bool isReal = false;

        //draw->drawPoly(verticess, sizeof(verticess) / sizeof(verticess[0]), true,
        //               Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f), thickness);

        Vec2 vertices[5] = {Vec2(0.0f, 0.0f), Vec2(50.0f, 50.0f), Vec2(100.0f, 50.0f), Vec2(100.0f, 100.0f),
                            Vec2(50.0f, 100.0f)};
        draw->drawPoly(vertices, 5, false, Color4B::BLUE, thickness);

        Vec2 vertices2[3] = {Vec2(30.0f, 130.0f), Vec2(30.0f, 230.0f), Vec2(50.0f, 200.0f)};
        draw->drawPoly(vertices2, 3, true, Color4B::GREEN, thickness);

        Vec2 vertices24[] = {
            {45.750000f, 144.375000f},  {75.500000f, 136.875000f},  {75.500000f, 159.125000f},
            {100.250000f, 161.375000f}, {65.500000f, 181.375000f},  {102.250000f, 179.125000f},
            {95.000000f, 215.125000f},  {129.331467f, 189.926208f}, {131.371460f, 206.366196f},
            {139.651474f, 192.446198f}, {161.851471f, 200.606201f}, {151.000000f, 220.375000f},
            {110.500000f, 244.375000f}, {153.750000f, 238.125000f}, {142.500000f, 253.875000f},
            {220.750000f, 259.375000f}, {250.500000f, 244.375000f}, {168.750000f, 241.875000f},
            {182.250000f, 154.125000f}, {190.250000f, 227.375000f}, {196.500000f, 197.375000f},
            {208.750000f, 210.625000f}, {220.750000f, 194.375000f}, {208.750000f, 176.375000f},
            {253.250000f, 173.875000f}, {243.750000f, 154.125000f}, {213.750000f, 161.375000f},
            {202.250000f, 139.875000f}, {236.000000f, 131.875000f}, {218.500000f, 120.875000f},
            {206.500000f, 125.625000f}, {184.500000f, 110.375000f}, {157.000000f, 108.625000f},
            {147.500000f, 96.625000f},  {153.750000f, 85.125000f},  {147.500000f, 75.375000f},
            {126.500000f, 74.125000f},  {110.500000f, 86.625000f},  {127.750000f, 85.125000f},
            {135.250000f, 91.125000f},  {135.250000f, 97.875000f},  {124.000000f, 93.875000f},
            {115.500000f, 100.875000f}, {115.500000f, 111.875000f}, {135.250000f, 108.625000f},
            {151.000000f, 124.125000f}, {90.500000f, 131.875000f},  {113.250000f, 120.875000f},
            {88.000000f, 116.875000f},  {106.000000f, 103.875000f}, {88.000000f, 97.875000f},
        };

        draw->drawPoly(vertices24, sizeof(vertices24) / sizeof(vertices24[0]), true, Color4B::RED, thickness);

        break;
    }
    case 8:
    {
        // drawPolygon

        Vec2 vertices24[] = {
            {45.750000f, 144.375000f},  {75.500000f, 136.875000f},  {75.500000f, 159.125000f},
            {100.250000f, 161.375000f}, {65.500000f, 181.375000f},  {102.250000f, 179.125000f},
            {95.000000f, 215.125000f},  {129.331467f, 189.926208f}, {131.371460f, 206.366196f},
            {139.651474f, 192.446198f}, {161.851471f, 200.606201f}, {151.000000f, 220.375000f},
            {110.500000f, 244.375000f}, {153.750000f, 238.125000f}, {142.500000f, 253.875000f},
            {220.750000f, 259.375000f}, {250.500000f, 244.375000f}, {168.750000f, 241.875000f},
            {182.250000f, 154.125000f}, {190.250000f, 227.375000f}, {196.500000f, 197.375000f},
            {208.750000f, 210.625000f}, {220.750000f, 194.375000f}, {208.750000f, 176.375000f},
            {253.250000f, 173.875000f}, {243.750000f, 154.125000f}, {213.750000f, 161.375000f},
            {202.250000f, 139.875000f}, {236.000000f, 131.875000f}, {218.500000f, 120.875000f},
            {206.500000f, 125.625000f}, {184.500000f, 110.375000f}, {157.000000f, 108.625000f},
            {147.500000f, 96.625000f},  {153.750000f, 85.125000f},  {147.500000f, 75.375000f},
            {126.500000f, 74.125000f},  {110.500000f, 86.625000f},  {127.750000f, 85.125000f},
            {135.250000f, 91.125000f},  {135.250000f, 97.875000f},  {124.000000f, 93.875000f},
            {115.500000f, 100.875000f}, {115.500000f, 111.875000f}, {135.250000f, 108.625000f},
            {151.000000f, 124.125000f}, {90.500000f, 131.875000f},  {113.250000f, 120.875000f},
            {88.000000f, 116.875000f},  {106.000000f, 103.875000f}, {88.000000f, 97.875000f},
        };

        draw->setDNScale(Vec2(thickness, thickness));
        draw->setDNPosition(Vec2(0, 0));
        draw->drawPolygon(vertices24, sizeof(vertices24) / sizeof(vertices24[0]), Color4F::GREEN, thickness,
                          Color4F::YELLOW);
        draw->setDNPosition(Vec2(10, 0));
        draw->drawPolygon(vertices24, sizeof(vertices24) / sizeof(vertices24[0]), Color4F::GREEN, thickness,
                          Color4F::YELLOW);


        draw1->clear();
        draw1->setPosition(Vec2(200, 0));
        draw1->setScale(thickness);
        draw1->drawPolygon(vertices24, sizeof(vertices24) / sizeof(vertices24[0]), Color4F::RED, thickness,
                           Color4F::YELLOW);

        // for (int i = 0; i < 0; i++)
        //{
        //     PathsD solution, clip, subject;
        //     PathD p, c;
        //     for (int i = 0; i < 3; i++)
        //     {
        //         p.push_back(
        //             PointD(AXRANDOM_0_1() * VisibleRect::rightTop().x, AXRANDOM_0_1() * VisibleRect::rightTop().y));
        //         c.push_back(
        //             PointD(AXRANDOM_0_1() * VisibleRect::rightTop().x, AXRANDOM_0_1() * VisibleRect::rightTop().y));
        //     }
        //
        //     subject.push_back(p);
        //     clip.push_back(c);
        //     solution = Intersect(subject, clip, FillRule::Positive);

        //    if (solution.size() > 0)
        //    {
        //        Vec2* vertices;
        //        int verCount = 0;
        //        ax::any_buffer myBuf;
        //        for (auto&& p : solution)
        //        {
        //            int i    = 0;
        //            verCount = p.size();
        //            vertices = myBuf.get<Vec2>(verCount);
        //            for (auto&& pt : p)
        //            {
        //                vertices[i] = Vec2(pt.x, pt.y);
        //                i++;
        //            }
        //        }
        ////        if (verCount > 8)
        //        {
        //            draw->drawPolygon(vertices, verCount, Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(),
        //            AXRANDOM_0_1(), 1.0),
        //                              thickness, Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f));
        //        }
        //    }

        // PathsD solution, clip, subject;
        // PathD p, c;
        // for (int i = 0; i < 10; i++)
        //{
        //     p.push_back(
        //         PointD(AXRANDOM_0_1() * VisibleRect::rightTop().x, AXRANDOM_0_1() * VisibleRect::rightTop().y));
        //     c.push_back(
        //         PointD(AXRANDOM_0_1() * VisibleRect::rightTop().x, AXRANDOM_0_1() * VisibleRect::rightTop().y));
        // }
        // subject.push_back(p);
        // clip.push_back(c);
        // solution = Intersect(subject, clip, FillRule::NonZero);
        // if (solution.size() > 0)
        //{
        //     Vec2* vertices;
        //     int verCount = 0;
        //     ax::any_buffer myBuf;
        //     for (auto&& p : solution)
        //     {
        //         int i    = 0;
        //         verCount = p.size();
        //         vertices = myBuf.get<Vec2>(verCount+1);
        //         for (auto&& pt : p)
        //         {
        //             vertices[i] = Vec2(pt.x, pt.y);
        //             i++;
        //         }
        //     }
        //     if (sizeof(vertices) / sizeof(vertices) > 8)
        //     {
        //         draw->drawPolygon(vertices, sizeof(vertices) / sizeof(vertices), Color4B::AX_TRANSPARENT,
        //         thickness,
        //                           Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 0.1f));
        //     }
        //}

        // Vec2 points[] = {Vec2(s.height / 4, 0.0f), Vec2(s.width, s.height / 5), Vec2(s.width / 3 * 2, s.height)};
        // draw->drawPolygon(points, 3, Color4B::AX_TRANSPARENT, thickness, Color4F(0.0f, 0.0f, 1.0f, 0.5f));

        // Vec2 vertices24[] = {
        //     {45.750000f, 144.375000f},  {75.500000f, 136.875000f},  {75.500000f, 159.125000f},
        //     {100.250000f, 161.375000f}, {65.500000f, 181.375000f},  {102.250000f, 179.125000f},
        //     {95.000000f, 215.125000f},  {129.331467f, 189.926208f}, {131.371460f, 206.366196f},
        //     {139.651474f, 192.446198f}, {161.851471f, 200.606201f}, {151.000000f, 220.375000f},
        //     {110.500000f, 244.375000f}, {153.750000f, 238.125000f}, {142.500000f, 253.875000f},
        //     {220.750000f, 259.375000f}, {250.500000f, 244.375000f}, {168.750000f, 241.875000f},
        //     {182.250000f, 154.125000f}, {190.250000f, 227.375000f}, {196.500000f, 197.375000f},
        //     {208.750000f, 210.625000f}, {220.750000f, 194.375000f}, {208.750000f, 176.375000f},
        //     {253.250000f, 173.875000f}, {243.750000f, 154.125000f}, {213.750000f, 161.375000f},
        //     {202.250000f, 139.875000f}, {236.000000f, 131.875000f}, {218.500000f, 120.875000f},
        //     {206.500000f, 125.625000f}, {184.500000f, 110.375000f}, {157.000000f, 108.625000f},
        //     {147.500000f, 96.625000f},  {153.750000f, 85.125000f},  {147.500000f, 75.375000f},
        //     {126.500000f, 74.125000f},  {110.500000f, 86.625000f},  {127.750000f, 85.125000f},
        //     {135.250000f, 91.125000f},  {135.250000f, 97.875000f},  {124.000000f, 93.875000f},
        //     {115.500000f, 100.875000f}, {115.500000f, 111.875000f}, {135.250000f, 108.625000f},
        //     {151.000000f, 124.125000f}, {90.500000f, 131.875000f},  {113.250000f, 120.875000f},
        //     {88.000000f, 116.875000f},  {106.000000f, 103.875000f}, {88.000000f, 97.875000f},
        // };
        // BENCHMARK_SECTION_BEGIN("drawPolygon");
        // draw->drawPolygon(vertices24, sizeof(vertices24) / sizeof(vertices24[0]), Color4B::AX_TRANSPARENT, thickness,
        //                   Color4F::RED);
        // BENCHMARK_SECTION_END()
        ////     break;

        // Vec2 vertices0[] = {{50.0, 20.0}, {100.0, 0.0}, {80.0, 50.0}, {100.0, 100.0},
        //                     {50.0, 80.0}, {0.0, 100.0}, {20.0, 50.0}, {0, 0}};

        // Vec2 vertices4[] = {{362, 148}, {326, 241}, {295, 219}, {258, 88}, {440, 129},
        //                     {370, 196}, {372, 275}, {348, 257}, {364, 148}};

        // Vec2* ver[] = {vertices0, vertices4};

        // draw->drawPolygon(vertices0, sizeof(vertices0) / sizeof(vertices0[0]), Color4F::AX_TRANSPARENT, thickness,
        //                   Color4F(0.0f, 0.0f, 1.0f, 1.0f));

        // draw->drawPolygon(vertices4, sizeof(vertices4) / sizeof(vertices4[0]), Color4F::AX_TRANSPARENT, thickness,
        //                   Color4F(0.0f, 0.0f, 1.0f, 1.0f));

        // const float o = 80;
        // const float w = 20;
        // const float h = 50;
        //{  // star
        //     Vec2 star[] = {
        //         Vec2(o, o),
        //         Vec2(o + w, o - h),
        //         Vec2(o + w * 2, o),  // lower spike
        //         Vec2(o + w * 2 + h, o + w),
        //         Vec2(o + w * 2, o + w * 2),  // right spike
        //         Vec2(o + w, o + w * 2 + h),
        //         Vec2(o, o + w * 2),  // top spike
        //         Vec2(o - h, o + w),  // left spike
        //     };

        //    draw->drawPolygon(star, sizeof(star) / sizeof(star[0]), Color4F::AX_TRANSPARENT, thickness,
        //                      Color4F(0.0f, 0.0f, 1.0f, 1.0f));
        //}

        //{  // wrong order

        //    Vec2 wrongOrder[] = {Vec2(o + w, o - h), Vec2(o + w * 2, o), Vec2(o + w * 2 + h, o + w),
        //                         Vec2(o + w * 2, o + w * 2)};

        //    draw->drawPolygon(wrongOrder, sizeof(wrongOrder) / sizeof(wrongOrder[0]), Color4F::AX_TRANSPARENT,
        //                      thickness, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
        //}
        //{  // correct order
        //    Vec2 correctOrder[] = {Vec2(o + w * 2, o), Vec2(o + w * 2 + h, o + w), Vec2(o + w * 2, o + w * 2),
        //                           Vec2(o + w, o - h)};

        //    draw->drawPolygon(correctOrder, sizeof(correctOrder) / sizeof(correctOrder[0]), Color4F::AX_TRANSPARENT,
        //                      thickness, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
        //}
        //{
        //    Vec2 vertices0[] = {{50.0, 20.0}, {100.0, 0.0}, {80.0, 50.0}, {100.0, 100.0},
        //                        {50.0, 80.0}, {0.0, 100.0}, {20.0, 50.0}, {0, 0}};

        //    Vec2 vertices4[] = {{362, 148}, {326, 241}, {295, 219}, {258, 88}, {440, 129},
        //                        {370, 196}, {372, 275}, {348, 257}, {364, 148}};

        //    Vec2* ver[] = {vertices0, vertices4};

        //    draw->drawPolygon(vertices0, sizeof(vertices0) / sizeof(vertices0[0]), Color4F::AX_TRANSPARENT, thickness,
        //                      Color4F(0.0f, 0.0f, 1.0f, 1.0f));

        //    draw->drawPolygon(vertices4, sizeof(vertices4) / sizeof(vertices4[0]), Color4F::AX_TRANSPARENT, thickness,
        //                      Color4F(0.0f, 0.0f, 1.0f, 1.0f));
        //}
        //{
        //    const float o = 80;
        //    const float w = 20;
        //    const float h = 50;
        //    {  // star

        //        Vec2 star[] = {
        //            Vec2(o, o),
        //            Vec2(o + w, o - h),
        //            Vec2(o + w * 2, o),  // lower spike
        //            Vec2(o + w * 2 + h, o + w),
        //            Vec2(o + w * 2, o + w * 2),  // right spike
        //            Vec2(o + w, o + w * 2 + h),
        //            Vec2(o, o + w * 2),  // top spike
        //            Vec2(o - h, o + w),  // left spike
        //        };

        //        draw->drawPolygon(star, sizeof(star) / sizeof(star[0]), Color4F::AX_TRANSPARENT, thickness,
        //                          Color4F(0.0f, 0.0f, 1.0f, 1.0f));
        //    }
        //}

        //{  // wrong order

        //    Vec2 wrongOrder[] = {Vec2(o + w, o - h), Vec2(o + w * 2, o), Vec2(o + w * 2 + h, o + w),
        //                         Vec2(o + w * 2, o + w * 2)};

        //    draw->drawPolygon(wrongOrder, sizeof(wrongOrder) / sizeof(wrongOrder[0]), Color4F::AX_TRANSPARENT,
        //                      thickness, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
        //}
        //{  // correct order
        //    Vec2 correctOrder[] = {Vec2(o + w * 2, o), Vec2(o + w * 2 + h, o + w), Vec2(o + w * 2, o + w * 2),
        //                           Vec2(o + w, o - h)};

        //    draw->drawPolygon(correctOrder, sizeof(correctOrder) / sizeof(correctOrder[0]), Color4F::AX_TRANSPARENT,
        //                      thickness, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
        //}
        break;
    }
    default:
        break;
    }
}

// DrawFilledPrimitivesTest
DrawNodePart2Test::DrawNodePart2Test()
{
    _currentSeletedItemIndex = 0;

    auto director = Director::getInstance();
    director->setClearColor(Color4F(0, 0, 0, 0));
    auto origin = director->getVisibleOrigin();
    auto size   = director->getVisibleSize();
    Vec2 center(origin.x + size.width / 2 + 50, origin.y + size.height / 2);

    auto listview = createListView();
    listview->setPosition(Vec2(0.0f, 90.0f));
    addChild(listview);

    draw = DrawNodeEx::create();
    draw->setScale(0.5);
    draw->setPosition(size / 4);
    addChild(draw);

    auto thicknessSlider = createSlider();
    thicknessSlider->setPosition(Vec2(center.x, 60.0f));
    addChild(thicknessSlider);

    label = Label::createWithTTF("Count: ", "fonts/Marker Felt.ttf", 10);
    label->setPosition(Vec2(Vec2(center.x, 80.0f)));
    this->addChild(label, 1);

    scheduleUpdate();
}

std::string DrawNodePart2Test::title() const
{
    return "DrawNode #2 Test";
}

string DrawNodePart2Test::subtitle() const
{
    return "";
}

ax::ui::Slider* DrawNodePart2Test::createSlider()
{
    auto slider = ui::Slider::create();
    slider->setTouchEnabled(true);
    slider->loadBarTexture("cocosui/sliderTrack.png");
    slider->loadSlidBallTextures("cocosui/sliderThumb.png", "cocosui/sliderThumb.png", "");
    slider->loadProgressBarTexture("cocosui/sliderProgress.png");
    slider->addEventListener(AX_CALLBACK_2(DrawNodePart2Test::sliderCallback, this));
    //     slider->setRotation(90);
    slider->setTag(101);
    slider->setPercent(10);

    return slider;
}

void DrawNodePart2Test::listviewCallback(ax::Ref* sender, ax::ui::ListView::EventType type)
{
    // clear all text to white
    auto listview = static_cast<ax::ui::ListView*>(sender);
    for (auto&& item : listview->getItems())
    {
        static_cast<ax::ui::Text*>(item)->setColor(ax::Color3B::WHITE);
    }
    _currentSeletedItemIndex = (int)listview->getCurSelectedIndex();
    listview->getItem(_currentSeletedItemIndex)->setColor(ax::Color3B::RED);
}

void DrawNodePart2Test::sliderCallback(ax::Ref* sender, ax::ui::Slider::EventType type)
{
    if (type == ax::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        auto slider = dynamic_cast<ax::ui::Slider*>(sender);
        count       = slider->getPercent() * 10;
    }
}

ax::ui::ListView* DrawNodePart2Test::createListView()
{
    auto listview = ax::ui::ListView::create();

    auto drawLine = ax::ui::Text::create();
    drawLine->setString("drawDot");
    drawLine->setTouchEnabled(true);
    listview->pushBackCustomItem(drawLine);

    auto drawSegment = ax::ui::Text::create();
    drawSegment->setString("drawPoint");
    drawSegment->setTouchEnabled(true);
    listview->pushBackCustomItem(drawSegment);

    auto drawTriangle = ax::ui::Text::create();
    drawTriangle->setString("drawPoints");
    drawTriangle->setTouchEnabled(true);
    listview->pushBackCustomItem(drawTriangle);

    auto drawRect = ax::ui::Text::create();
    drawRect->setString("drawTriangle");
    drawRect->setTouchEnabled(true);
    listview->pushBackCustomItem(drawRect);

    auto drawCircle = ax::ui::Text::create();
    drawCircle->setString("drawSegment");
    drawCircle->setTouchEnabled(true);
    listview->pushBackCustomItem(drawCircle);

    auto drawQuadBezier = ax::ui::Text::create();
    drawQuadBezier->setString("drawSolidCircle");
    drawQuadBezier->setTouchEnabled(true);
    listview->pushBackCustomItem(drawQuadBezier);

    auto drawCubicBezier = ax::ui::Text::create();
    drawCubicBezier->setString("drawSolidPoly");
    drawCubicBezier->setTouchEnabled(true);
    listview->pushBackCustomItem(drawCubicBezier);

    auto drawCardinalSpline = ax::ui::Text::create();
    drawCardinalSpline->setString("drawSolidRect");
    drawCardinalSpline->setTouchEnabled(true);
    listview->pushBackCustomItem(drawCardinalSpline);

    listview->setContentSize(drawLine->getContentSize() * 8);
    listview->setCurSelectedIndex(0);
    listview->setTouchEnabled(true);
    listview->addEventListener(
        (ui::ListView::ccListViewCallback)AX_CALLBACK_2(DrawNodePart2Test::listviewCallback, this));
    listview->setTag(100);

    listview->getItem(_currentSeletedItemIndex)->setColor(Color3B::RED);

    return listview;
}

void DrawNodePart2Test::update(float dt)
{

    auto s = Director::getInstance()->getWinSize();

    draw->clear();

    label->setString("Count: (" + Value(count).asString() + ")");
    switch (_currentSeletedItemIndex)
    {
    case 0:
    {
        // Draw 10 circles/dots
        for (int i = 0; i < count / 100; i++)
        {
            draw->drawDot(Vec2(100.f + AXRANDOM_0_1() * VisibleRect::rightTop().x,
                               100.f + AXRANDOM_0_1() * VisibleRect::rightTop().y),
                          AXRANDOM_0_1() * 20 + 20, Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f));
        }
        break;
    }
    case 1:
    {
        for (int i = 0; i < 100; i++)
        {
            draw->drawPoint(Vec2(i * 7.0f, 50.0f), (float)i / 5 + 1,
                            Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1.0f));
        }
        break;
    }
    case 2:
    {
        // drawPoints
        for (int i = 0; i < count; i++)
        {
            Vec2 position[] = {
                {60 + AXRANDOM_0_1() * VisibleRect::rightTop().x, 60 + AXRANDOM_0_1() * VisibleRect::rightTop().y},
                {70 + AXRANDOM_0_1() * VisibleRect::rightTop().x, 70 + AXRANDOM_0_1() * VisibleRect::rightTop().y},
                {60 + AXRANDOM_0_1() * VisibleRect::rightTop().x, 60 + AXRANDOM_0_1() * VisibleRect::rightTop().y},
                {70 + AXRANDOM_0_1() * VisibleRect::rightTop().x, 70 + AXRANDOM_0_1() * VisibleRect::rightTop().y}};
            draw->drawPoints(position, 4, 5, Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 1));
        }

        break;
    }
    case 3:
    {
        // drawTriangle
        for (int i = 0; i < count; i++)
        {
            Vec2 pos = Vec2(AXRANDOM_0_1() * VisibleRect::rightTop().x, AXRANDOM_0_1() * VisibleRect::rightTop().y);
            draw->drawTriangle(pos + Vec2(10.0f, 10.0f), pos + Vec2(70.0f, 30.0f), pos + Vec2(100.0f, 140.0f),
                               Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 0.5f));
        }
        break;
    }
    case 4:
    {
        // Draw segment
        draw->drawSegment(Vec2(20.0f, s.height), Vec2(20.0f, s.height / 2), 10,
                          Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 0.5f));

        draw->drawSegment(Vec2(10.0f, s.height / 2), Vec2(s.width / 2, s.height / 2), 40,
                          Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 0.5f));
        break;
    }
    case 5:
    {
        // draw a solid circle
        for (int i = 0; i < count; i++)
        {
            draw->drawSolidCircle(
                Vec2(AXRANDOM_0_1() * VisibleRect::rightTop().x, AXRANDOM_0_1() * VisibleRect::rightTop().y),
                AXRANDOM_0_1() * 40.f + 40.f, AX_DEGREES_TO_RADIANS(90), 50, 2.0f, 2.0f,
                Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 0.5f));
        }
        break;
    }
    case 6:
    {
        // draw a solid polygon
        // Paths64 subject, clip, solution;
        // subject.push_back(MakePath({100, 50, 10, 79, 65, 2, 65, 98, 10, 21}));
        // clip.push_back(MakePath({98, 63, 4, 68, 77, 8, 52, 100, 19, 12}));
        // solution = Intersect(subject, clip, FillRule::NonZero);

        // Vec2* vertices;
        // int verCount = 0;
        // ax::any_buffer myBuf;
        // for (auto&& p : solution)
        //{
        //     int i    = 0;
        //     verCount = p.size();
        //     vertices = myBuf.get<Vec2>(verCount);
        //     for (auto&& pt : p)
        //     {
        //         vertices[i] = Vec2(pt.x, pt.y);
        //         i++;
        //     }
        // }
        // draw->drawSolidPoly(vertices, verCount, Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 0.5f));

        for (int i = 0; i < 1; i++)
        {
            PathsD solution, clip, subject;
            PathD p, c;
            for (int i = 0; i < 10; i++)
            {
                p.push_back(
                    PointD(AXRANDOM_0_1() * VisibleRect::rightTop().x, AXRANDOM_0_1() * VisibleRect::rightTop().y));
                c.push_back(
                    PointD(AXRANDOM_0_1() * VisibleRect::rightTop().x, AXRANDOM_0_1() * VisibleRect::rightTop().y));
            }
            subject.push_back(p);
            clip.push_back(c);
            solution = Intersect(subject, clip, FillRule::NonZero);

            if (solution.size() > 0)
            {
                Vec2* vertices = nullptr;
                int verCount = 0;
                ax::any_buffer myBuf;
                for (auto&& p : solution)
                {
                    int i    = 0;
                    verCount = p.size();
                    vertices = myBuf.get<Vec2>(verCount);
                    for (auto&& pt : p)
                    {
                        vertices[i] = Vec2(pt.x, pt.y);
                        i++;
                    }
                }
                draw->drawSolidPoly(vertices, verCount, Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 0.5f));
            }
        }

        break;
    }
    case 7:
    {
        // draw a solid rectangle
        for (int i = 0; i < count; i++)
        {
            Vec2 pos = Vec2(AXRANDOM_0_1() * VisibleRect::rightTop().x, AXRANDOM_0_1() * VisibleRect::rightTop().y);
            draw->drawSolidRect(pos, pos + Vec2(20.0f, 20.0f),
                                Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 0.5f));
        }
        break;
    }
    default:
        break;
    }
}
//
// makeP(int count)
//{
//    for (int i = 0; i < count; i++)
//    {
//        PathsD solution, clip, subject;
//        PathD p, c;
//        for (int i = 0; i < 5; i++)
//        {
//            p.push_back(PointD(AXRANDOM_0_1() * VisibleRect::leftTop().x, AXRANDOM_0_1() * VisibleRect::leftTop().y));
//            c.push_back(PointD(AXRANDOM_0_1() * VisibleRect::leftTop().x, AXRANDOM_0_1() * VisibleRect::leftTop().y));
//        }
//        subject.push_back(p);
//        clip.push_back(p);
//        solution = Intersect(subject, clip, FillRule::NonZero);
//
//        Vec2* vertices;
//        int verCount = 0;
//        ax::any_buffer myBuf;
//        for (auto&& p : solution)
//        {
//            int i    = 0;
//            verCount = p.size();
//            vertices = myBuf.get<Vec2>(verCount);
//            for (auto&& pt : p)
//            {
//                vertices[i] = Vec2(pt.x, pt.y);
//                i++;
//            }
//        }
//        draw->drawSolidPoly(vertices, verCount, Color4F(AXRANDOM_0_1(), AXRANDOM_0_1(), AXRANDOM_0_1(), 0.5f));
//    }
//}