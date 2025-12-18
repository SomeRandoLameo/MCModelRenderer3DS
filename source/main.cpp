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
#include "ResourceManager.h"

const auto SCREEN_WIDTH = 400.0f;
const auto SCREEN_HEIGHT = 480.0f;
const auto FB_SCALE = 1.0f;

class MCMR : public Amy::App {
public:
    MCMR() {
        Amy::GTrace::Scope s("Init");
        gfxInitDefault();
        romfsInit();
        C3D::Init();
        m_Top = C3D::CreateScreen(GFX_TOP);
        m_Bottom = C3D::CreateScreen(GFX_BOTTOM);

        m_Mgr = new Amy::AssetMgr();
        Iron::Init();

        auto fnt = Iron::Font::New();
        fnt->LoadBMF("romfs:/ComicNeue.png");
        m_Mgr->AutoLoad("icon", "romfs:/icon.png");
        m_Mgr->Add("font", fnt);
        // Mgr->AutoLoad("font", "romfs:/ComicNeue.ttf");
        m_dl = Iron::Drawlist::New();
        m_dl->SetFont(m_Mgr->Get<Iron::Font>("font"));

        ImGui::CreateContext();
        m_io = &ImGui::GetIO();
        auto& style = ImGui::GetStyle();
        style.ScaleAllSizes(0.5f);
        m_io->IniFilename = nullptr;
        ImGui_ImplCtr_Init();
        ImGui_ImplCitro3D_Init();

    }

    ~MCMR() {
        C3D::DeleteScreen(m_Top);
        C3D::DeleteScreen(m_Bottom);
        m_dl.reset();
        m_Mgr->Remove("font");
        m_Mgr->Remove("icon");
        delete m_Mgr;

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

        std::string metrics = std::format(
                "Delta: {:.3} -> {:.3} FPS\n"
                "Time: {}\n"
                "LinearRam: {}\n"
                "VIT: [{}/{}/{}]\n"
                "Assets: {}\n"
                "Main: {}",
                this->Delta(), 1000.0 / this->Delta(),
                Amy::Utils::FormatMillis(this->Time() * 1000.f),
                Amy::Utils::FormatBytes(linearSpaceFree()), Amy::Iron::VerticesDrawn(),
                Amy::Iron::IndicesDrawn(), Amy::Iron::IndicesDrawn() / 3,
                m_Mgr->CountAll(),
                Amy::Utils::FormatNanos(Amy::GTrace::GetTraceRef("Main")->GetLastDiff()));

        C3D::StartFrame(true);
        Amy::GTrace::Beg("Main");

        m_io->DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);
        m_io->DisplayFramebufferScale = ImVec2(FB_SCALE, FB_SCALE);
        ImGui_ImplCitro3D_NewFrame();
        ImGui_ImplCtr_NewFrame();
        ImGui::NewFrame();

        if (!m_amy_allowed) {
            ImGui::SetNextWindowPos(ImVec2(10, 180));
            ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
            ImGui::Begin("Overlay", nullptr,
                         ImGuiWindowFlags_NoDecoration |
                         ImGuiWindowFlags_AlwaysAutoResize |
                         ImGuiWindowFlags_NoSavedSettings |
                         ImGuiWindowFlags_NoFocusOnAppearing |
                         ImGuiWindowFlags_NoNav);

            ImGui::Text("Preview Rendering Disabled");
            ImGui::Text("Settings -> [EXP] Allow Amy Rendering");

            ImGui::End();
        }

        ImGui::SetNextWindowPos(ImVec2(40, 240), ImGuiCond_FirstUseEver); // Center horizontally: (400-320)/2 = 40
        ImGui::SetNextWindowSize(ImVec2(320, 240), ImGuiCond_FirstUseEver);
        ImGui::Begin("Toolbar", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    Exit();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View")) {
                ImGui::MenuItem("Show Amethyst Metrics", nullptr, &m_amy_metrics, m_amy_allowed);
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("Amy is disabled!");
                }

                ImGui::MenuItem("Show ImGUI Demo Window", nullptr, &m_show_demo_window);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Settings")) {
                ImGui::MenuItem("Dark mode", nullptr, &m_dark_mode);
                ImGui::MenuItem("[EXP] Allow Amy Rendering", nullptr, &m_amy_allowed);
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        if (m_resourceManager.CheckRootAssets()) {
            //dl->DrawText(Amy::fvec2(5, 0), , Amy::Color(255, 0, 255));
            ImGui::Text("Assets: exist");
        }else{
            //dl->DrawText(Amy::fvec2(5, 0), , Amy::Color(255, 0, 255));
            ImGui::Text("Assets: missing");
        }

        ImGui::End();

        if (m_show_demo_window) {
            ImGui::ShowDemoWindow(&m_show_demo_window);
        }
        if (m_dark_mode) {
            ImGui::StyleColorsDark();
        } else {
            ImGui::StyleColorsLight();
        }

        m_Top->Clear();
        m_Bottom->Clear();
        m_Top->Use();
        //dl->DrawTex(Mgr->Get<Amy::Texture>("icon"));
        //dl->DrawRectFilled(Amy::fvec2(50, 0), 48, Amy::Color(255, 255, 255, 160));
        //dl->DrawCircleFilled(Amy::fvec2(200, 120), 50, Amy::Color("#ffffff"), 40);
        //dl->DrawSolid();
        //dl->DrawRectFilled(0, 50, Amy::Color(0.f, 1.f, 0.f, 1.f));

        //TODO: Respect light/dark mode from Imgui
        if(m_amy_metrics) {
            m_dl->DrawText(Amy::fvec2(5, 5), metrics, Amy::Color(255, 255, 255));
        }

        // Required for rendering, do not remove
        Iron::NewFrame();
        if(m_amy_allowed){
            Iron::DrawOn(m_Top);
            Iron::Draw(*m_dl);
        }
        m_dl->Clear();

        ImGui::Render();
        ImGui_ImplCitro3D_RenderDrawData(ImGui::GetDrawData(), reinterpret_cast<void*>(m_Top->Ptr()), reinterpret_cast<void*>(m_Bottom->Ptr()));

        C3D_DepthTest(true, GPU_GREATER, GPU_WRITE_ALL);
        C3D_CullFace(GPU_CULL_BACK_CCW);

        C3D::EndFrame();
        Amy::GTrace::End("Main");
    }

private:
    ResourceManager m_resourceManager = ResourceManager();

    C3D::Screen *m_Top = nullptr;
    C3D::Screen* m_Bottom = nullptr;
    Amy::AssetMgr* m_Mgr = nullptr;
    Iron::Drawlist::Ref m_dl = nullptr;
    ImGuiIO* m_io = nullptr;

    bool m_show_demo_window = false;
    bool m_dark_mode = false;

    bool m_amy_metrics = true;
    bool m_amy_allowed = false;
};

int main() {
    Amy::RegisterCxxExceptionHandler();
    MCMR modelRenderer;
    modelRenderer.Run();
    return 0;
}