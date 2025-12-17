// Enable Npi Assert to write Errors to file
#define IMGUI_IMPL_CITRO3D_USE_NPI_ASSERT
#define IMGUI_IMPL_CIR_USE_NPI_ASSERT

#include <amethyst.hpp>
#include <iostream>
#include <3ds.h>
#include <citro3d.h>
#include <map>
#include <vector>
#include "imgui_impl_ctr.h"
#include "imgui_impl_citro3d.h"

const auto SCREEN_WIDTH = 400.0f;
const auto SCREEN_HEIGHT = 480.0f;
const auto FB_SCALE = 1.0f;

std::vector<std::string> styles = {
        "ImGui Light",
        "ImGui Dark",
        "ImGui Classic",
};

std::string cstyle = styles[1];

void LoadStyle() {
    if (cstyle == styles[0])
        ImGui::StyleColorsLight();
    else if (cstyle == styles[1])
        ImGui::StyleColorsDark();
    else if (cstyle == styles[2])
        ImGui::StyleColorsClassic();
    else
        ImGui::StyleColorsDark();
}


class MCMR : public Amy::App {
public:
    MCMR() {
        Amy::GTrace::Scope s("Init");
        gfxInitDefault();
        romfsInit();
        C3D::Init();
        Top = C3D::CreateScreen(GFX_TOP);
        Bottom = C3D::CreateScreen(GFX_BOTTOM);

        Mgr = new Amy::AssetMgr();
        Iron::Init();

        auto fnt = Iron::Font::New();
        fnt->LoadBMF("romfs:/ComicNeue.png");
        Mgr->AutoLoad("icon", "romfs:/icon.png");
        Mgr->Add("font", fnt);
        // Mgr->AutoLoad("font", "romfs:/ComicNeue.ttf");
        dl = Iron::Drawlist::New();
        dl->SetFont(Mgr->Get<Iron::Font>("font"));

        ImGui::CreateContext();
        LoadStyle();
        io = &ImGui::GetIO();
        auto& style = ImGui::GetStyle();
        style.ScaleAllSizes(0.5f);
        io->IniFilename = nullptr;
        ImGui_ImplCtr_Init();
        ImGui_ImplCitro3D_Init();

    }

    ~MCMR() {
        C3D::DeleteScreen(Top);
        C3D::DeleteScreen(Bottom);
        dl.reset();
        Mgr->Remove("font");
        Mgr->Remove("icon");
        delete Mgr;

        ImGui_ImplCitro3D_Shutdown();
        ImGui_ImplCtr_Shutdown();

        Iron::Exit();
        C3D::Deinit();
        romfsExit();
        gfxExit();
    }

    void Main() {
        hidScanInput();
        if (hidKeysDown() & KEY_START) {
            Exit();
        }

        std::string stats = std::format(
                "Delta: {:.3} -> {:.3} FPS\nTime: {}\nLinearRam: {}\nVIT: "
                "[{}/{}/{}]\nAssets: {}\nMain: {}",
                this->Delta(), 1000.0 / this->Delta(),
                Amy::Utils::FormatMillis(this->Time() * 1000.f),
                Amy::Utils::FormatBytes(linearSpaceFree()), Amy::Iron::VerticesDrawn(),
                Amy::Iron::IndicesDrawn(), Amy::Iron::IndicesDrawn() / 3,
                Mgr->CountAll(),
                Amy::Utils::FormatNanos(
                        Amy::GTrace::GetTraceRef("Main")->GetLastDiff()));

        C3D::StartFrame(true);
        Amy::GTrace::Beg("Main");

        io->DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);
        io->DisplayFramebufferScale = ImVec2(FB_SCALE, FB_SCALE);
        ImGui_ImplCitro3D_NewFrame();
        ImGui_ImplCtr_NewFrame();
        ImGui::NewFrame();


        ImGui::Begin("Test");
        ImGui::Text("Hold Y and use CIRCLEPAD to Move\nThe Window f.e. to Bottom Screen!");

        if (ImGui::BeginCombo("##StyleSelect", cstyle.c_str())) {
            for (const auto & style : styles) {
                bool is_selected = (cstyle.c_str() == style);
                if (ImGui::Selectable(style.c_str(), is_selected)) {
                    cstyle = style;
                    LoadStyle();
                }
                if (is_selected) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::Checkbox("Show Demo Window", &show_demo_window);
        ImGui::Checkbox("Allow Iron Draw", &draw_iron_allow);
        ImGui::End();

        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        Top->Clear();
        Bottom->Clear();
        Top->Use();
        dl->DrawTex(Mgr->Get<Amy::Texture>("icon"));
        dl->DrawRectFilled(Amy::fvec2(50, 0), 48, Amy::Color(255, 255, 255, 160));
        dl->DrawCircleFilled(Amy::fvec2(200, 120), 50, Amy::Color("#ffffff"), 40);
        dl->DrawSolid();
        dl->DrawRectFilled(0, 50, Amy::Color(0.f, 1.f, 0.f, 1.f));
        dl->DrawText(Amy::fvec2(5, 50), stats, Amy::Color(255, 0, 255));

        Iron::NewFrame();
        if(draw_iron_allow) {
            Iron::DrawOn(Top);
            Iron::Draw(*dl);
        }
        dl->Clear();

        ImGui::Render();
        ImGui_ImplCitro3D_RenderDrawData(ImGui::GetDrawData(), reinterpret_cast<void*>(Top->Ptr()), reinterpret_cast<void*>(Bottom->Ptr()));

        C3D_DepthTest(true, GPU_GREATER, GPU_WRITE_ALL);
        C3D_CullFace(GPU_CULL_BACK_CCW);

        C3D::EndFrame();
        Amy::GTrace::End("Main");
    }

    C3D::Screen *Top = nullptr;
    C3D::Screen* Bottom = nullptr;
    Amy::AssetMgr* Mgr = nullptr;
    Iron::Drawlist::Ref dl = nullptr;

    bool show_demo_window = false;
    bool draw_iron_allow = false;
    ImGuiIO* io = nullptr;
};

int main() {
    Amy::RegisterCxxExceptionHandler();
    MCMR modelRenderer;
    modelRenderer.Run();
    return 0;
}