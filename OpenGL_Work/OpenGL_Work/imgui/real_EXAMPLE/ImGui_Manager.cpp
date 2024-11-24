#include "ImGui_Manager.h"
#include "GameInstance.h"
#include "Customize_UI.h"
#include "Edge_UI.h"
#include "TextBox.h"

#ifdef IMGUI STYLE
/* IMGUI STYLE */
ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
ImVec4* colors = style->Colors;

colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.85f);
colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.11f, 0.14f, 0.92f);
colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
colors[ImGuiCol_FrameBg] = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
colors[ImGuiCol_FrameBgHovered] = ImVec4(0.47f, 0.47f, 0.69f, 0.40f);
colors[ImGuiCol_FrameBgActive] = ImVec4(0.42f, 0.41f, 0.64f, 0.69f);
colors[ImGuiCol_TitleBg] = ImVec4(0.27f, 0.27f, 0.54f, 0.83f);
colors[ImGuiCol_TitleBgActive] = ImVec4(0.32f, 0.32f, 0.63f, 0.87f);
colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.40f, 0.80f, 0.30f);
colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.80f, 0.40f);
colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
colors[ImGuiCol_SliderGrabActive] = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
colors[ImGuiCol_Button] = ImVec4(0.35f, 0.40f, 0.61f, 0.62f);
colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.48f, 0.71f, 0.79f);
colors[ImGuiCol_ButtonActive] = ImVec4(0.46f, 0.54f, 0.80f, 1.00f);
colors[ImGuiCol_Header] = ImVec4(0.40f, 0.40f, 0.90f, 0.45f);
colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.60f, 0.70f, 1.00f);
colors[ImGuiCol_SeparatorActive] = ImVec4(0.70f, 0.70f, 0.90f, 1.00f);
colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.78f, 0.82f, 1.00f, 0.60f);
colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.82f, 1.00f, 0.90f);
colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
colors[ImGuiCol_TableHeaderBg] = ImVec4(0.27f, 0.27f, 0.38f, 1.00f);
colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.45f, 1.00f);   // Prefer using Alpha=1.0 here
colors[ImGuiCol_TableBorderLight] = ImVec4(0.26f, 0.26f, 0.28f, 1.00f);   // Prefer using Alpha=1.0 here
colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
colors[ImGuiCol_NavHighlight] = colors[ImGuiCol_HeaderHovered];
colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
/*========================================================================*/
#endif
#define SL  ImGui::SameLine()
#define NL  ImGui::NewLine()

IMPLEMENT_SINGLETON(CImgui_Manager)

CImgui_Manager::CImgui_Manager()
    : m_pGameInstance { CGameInstance::Get_Instance() }
{
    Safe_AddRef(m_pGameInstance);
}

void CImgui_Manager::Set_GraphicDevice(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
    m_pDevice = { pDevice };
    m_pContext = { pContext };
    Safe_AddRef(m_pDevice);
    Safe_AddRef(m_pContext);
}

HRESULT CImgui_Manager::Initialize()
{
    ::ShowWindow(g_hWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(g_hWnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    m_ImGuiIO = ImGui::GetIO();
    (void)m_ImGuiIO;
    m_ImGuiIO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    m_ImGuiIO.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    m_ImGuiIO.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 18.0f, NULL, m_ImGuiIO.Fonts->GetGlyphRangesKorean());

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(g_hWnd);
    ImGui_ImplDX11_Init(m_pDevice, m_pContext);

    m_pCameraFree = (CCamera_Free*)m_pGameInstance->Get_ObjLayer(LEVEL_GAMEPLAY, L"Layer_Camera")->front();
    Safe_AddRef(m_pCameraFree);
    //m_pObjectList.clear();

    InitFileDialog();

    return S_OK;
}

void CImgui_Manager::ResetVariable()
{
    _float3 campos = {};

    XMStoreFloat3(&campos, m_pGameInstance->Get_CamPosition_Vector());

    m_fCamPos.x = campos.x;
    m_fCamPos.y = campos.y;
    m_fCamPos.z = campos.z;
    m_fCamPos.w = 1;

    m_IsMouseHover = false;
}

void CImgui_Manager::Tick()
{
    ResetVariable();//벨류 리셋

    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    static ImVec4 ref_color_v(1.0f, 0.0f, 1.0f, 0.5f); // Color 변수

    if (m_pGameInstance->Get_DIKeyState(DIK_TAB, KEY_UP))
    {
        if (m_bToolWindow == false)
        {
            m_bToolWindow = true;
            m_eEditState = STATE_CREATE;
        }

        else
        {
            m_bToolWindow = false;
            m_eEditState = STATE_NUN;
        }
    }

    if (m_pGameInstance->Get_DIKeyState(DIK_ESCAPE, KEY_UP))
    {
        ReleaseClick();
    }

    if (m_pGameInstance->Get_DIKeyState(DIK_F3, KEY_UP))
        m_pGameInstance->Make_DDSFile_FromRT(TEXT("Target_Subject"), TEXT("../Bin/Resources/Textures/UI/SceneCapture/Text.dds"));

    if (m_pGameInstance->Get_DIKeyState(DIK_F1, KEY_UP))
        m_bTextureFileDialogWindow = !m_bTextureFileDialogWindow;

    if (true == m_bTextureFileDialogWindow)
        WindowTextureFileDialog();

    if (true == m_bDatDialogWindow)
        WindowDatDialog();

    if (true == m_bDirectoryChooserWindow)
        WindowDirectoryDialog();

    if (true == m_bToolWindow)
    {
        ImGui::Begin("TOOL_BOX");
        Tab_Create_UI(ref_color_v);
        if (true == ImGui::IsAnyItemHovered() || true == ImGui::IsWindowHovered())
            m_IsMouseHover = true;
        ImGui::End();
		/* Store 상태를 확인할 수 있는 Bar */
        if (m_isLook_StoreState && NULL != m_pSelectCustom)
        {
            ImGui::Begin("STATE BOX");
            Status_Box();
            ImGui::End();
        }
    }
        

    if (m_pGameInstance->Get_DIKeyState(DIK_F2, KEY_UP))
        m_isGridGizmo = !m_isGridGizmo;

    if (true == m_isUse_UIGizmo)
    {
        if (m_pGameInstance->Get_DIMouseState(DIMKS_LBUTTON, KEY_PRESS) ||
            m_pGameInstance->Get_DIMouseState(DIMKS_LBUTTON, KEY_UP))
        {
            if (NULL != m_pGizmoTransform && m_isGridGizmo)
            {
                _float4 vGrid = m_pGizmoTransform->Get_State_Float4(CTransform::STATE_POSITION);
                vGrid.x = m_vMousePos.x;
                vGrid.y = m_vMousePos.y;

                // Z값이 자꾸 밀려서 만약 안 보이는 값이 된다면 0으로 만들어 놓음
                if (vGrid.z < 0 || vGrid.z >= 1.5f)
                    vGrid.z = 0.f;

                m_pGizmoTransform->Set_State(CTransform::STATE_POSITION, vGrid);
            }
        }

        if (m_pGizmoTransform != nullptr)
            UI_Gizmo(*(m_pGizmoTransform->Get_Const_WorldFloat4x4()));
    }
        

    ObjectPicking();
}

void CImgui_Manager::ObjectPicking()
{
    if (false == IsCanClick())
        return;

    if (m_pGameInstance->Get_DIMouseState(DIMKS_LBUTTON, KEY_UP))
    {
        _float fShortestZ = { 0.f };
        _bool bFirst = { true };
        CGameObject* pSelectedOBJ = { nullptr };

        for (auto& iter : m_vecCutomizeUI)
        {
            _float fCurShortest = { 0.f };

            if (iter->Point_Size())
            {
                if (true == bFirst)
                {
                    iter->Point_Size(fCurShortest);
                    fShortestZ = fCurShortest;
                    pSelectedOBJ = iter;
                    bFirst = false;
                    m_eEdit_UIID = EDIT_ID::UI_RECT;
                }

                else
                {
                    iter->Point_Size(fCurShortest);
                    if (fShortestZ >= fCurShortest)
                    {
                        fShortestZ = fCurShortest;
                        pSelectedOBJ = iter;
                        m_eEdit_UIID = EDIT_ID::UI_RECT;
                    }
                }
            }

            for (auto& IterEdge : *(iter->Get_EdgeVec()))
            {
                if (IterEdge->Point_Size(fCurShortest))
                {
                    if (fShortestZ >= fCurShortest)
                    {
                        fShortestZ = fCurShortest;
                        pSelectedOBJ = IterEdge;
                        m_eEdit_UIID = EDIT_ID::UI_POINT;
                    }
                }
            }
        }

        if (nullptr != pSelectedOBJ)
        {
            m_isUse_UIGizmo = true;
            m_pGizmoTransform = dynamic_cast<CTransform*>(pSelectedOBJ->Get_Component(g_strTransformTag));
            switch (m_eEdit_UIID)
            {
            case Client::CImgui_Manager::UI_POINT: {
                dynamic_cast<CEdge_UI*>(pSelectedOBJ)->Follow_Rect(true);
                for (auto iter : m_vecCutomizeUI)
                    iter->Follow_Edge(false);
                break;
            }
                
            case Client::CImgui_Manager::UI_RECT: {
                m_pSelectObject = pSelectedOBJ;
                m_strSelected_UI_inList = Find_ObjTag(m_pSelectObject);
                m_pSelectCustom = dynamic_cast<CCustomize_UI*>(m_pSelectObject);
                m_pSelectCustom->Follow_Edge(true);
                Set_MapTextBox(m_pSelectCustom);
                for (auto& iter : *(m_pSelectCustom->Get_EdgeVec()))
                    dynamic_cast<CEdge_UI*>(iter)->Follow_Rect(false);
                break;
            }
            default:
                break;
            }
        }
        
        else
        {
            for (auto& iter : m_vecCutomizeUI)
            {
                if (nullptr != iter)
                    iter->Follow_Edge(false);
            }
        }
    }

}

void CImgui_Manager::Render()
{
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CImgui_Manager::EditTransform(CTransform* pTransformCom)
{
#ifndef _DEBUG
    return;
#endif
    ImGuizmo::BeginFrame();

    _float4x4 matrix = pTransformCom->Get_WorldFloat4x4();

    static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);

    if (CGameInstance::Get_Instance()->Get_DIKeyState(DIK_TAB, KEY_UP))
    {
        switch (m_eGizmoState)
        {
        case ImGuizmo::TRANSLATE:
            m_eGizmoState = ImGuizmo::ROTATE;
            break;

        case ImGuizmo::ROTATE:
            m_eGizmoState = ImGuizmo::SCALE;
            break;

        case ImGuizmo::SCALE:
            m_eGizmoState = ImGuizmo::TRANSLATE;
            break;
        default:
            break;
        }
    }

    if (ImGui::RadioButton("Translate", m_eGizmoState == ImGuizmo::TRANSLATE))
        m_eGizmoState = ImGuizmo::TRANSLATE;
    ImGui::SameLine();

    if (ImGui::RadioButton("Rotate", m_eGizmoState == ImGuizmo::ROTATE))
        m_eGizmoState = ImGuizmo::ROTATE;
    ImGui::SameLine();

    if (ImGui::RadioButton("Scale", m_eGizmoState == ImGuizmo::SCALE))
        m_eGizmoState = ImGuizmo::SCALE;

    float matrixTranslation[3], matrixRotation[3], matrixScale[3];
    ImGuizmo::DecomposeMatrixToComponents(matrix.m[0], matrixTranslation, matrixRotation, matrixScale);
    ImGui::InputFloat3("Tr", matrixTranslation);
    ImGui::InputFloat3("Rt", matrixRotation);
    ImGui::InputFloat3("Sc", matrixScale);
    ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, matrix.m[0]);

    if (m_eGizmoState != ImGuizmo::SCALE)
    {
        if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
            mCurrentGizmoMode = ImGuizmo::LOCAL;

        ImGui::SameLine();

        if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
            mCurrentGizmoMode = ImGuizmo::WORLD;
    }

    static bool useSnap(false);
    ImGui::Checkbox("##UseSnap", &useSnap);
    ImGui::SameLine();

    static _float snap[3] = { 1.f, 1.f, 1.f };
    switch (m_eGizmoState)
    {
    case ImGuizmo::TRANSLATE:
        ImGui::InputFloat3("Snap", &snap[0]);
        break;
    case ImGuizmo::ROTATE:
        ImGui::InputFloat("Angle Snap", &snap[0]);
        break;
    case ImGuizmo::SCALE:
        ImGui::InputFloat("Scale Snap", &snap[0]);
        break;
    }

    ImGuiIO& io = ImGui::GetIO();
    ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

    _float4x4 ViewMatrix, ProjMatrix;
    ViewMatrix = m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW);
    ProjMatrix = m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ);
    ImGuizmo::Manipulate(ViewMatrix.m[0], ProjMatrix.m[0], m_eGizmoState, mCurrentGizmoMode, matrix.m[0], NULL, useSnap ? &snap[0] : NULL);
    pTransformCom->Set_WorldMatrix(matrix);
    ImGui::End();
}

void CImgui_Manager::UI_Gizmo(_float4x4& matrix)
{
    ImGui::Begin(u8"Guizmo TOOL");

    ImGuizmo::BeginFrame();

    // 이제 mat의 첫 번째 요소의 주소를 얻습니다.
    static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
    static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);

    if (ImGui::RadioButton(u8"Transform", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
        mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Rotate", m_eGizmoState == ImGuizmo::ROTATE))
        mCurrentGizmoOperation = ImGuizmo::ROTATE;
    ImGui::SameLine();
    if (ImGui::RadioButton(u8"Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
        mCurrentGizmoOperation = ImGuizmo::SCALE;

    float matrixTranslation[3], matrixRotation[3], matrixScale[3];

    ImGuizmo::DecomposeMatrixToComponents(reinterpret_cast<float*>(&matrix), matrixTranslation, matrixRotation, matrixScale);

    ImGui::InputFloat3(u8"Transform", matrixTranslation);
    ImGui::InputFloat3("Rotation", matrixRotation);
    ImGui::InputFloat3(u8"Scale", matrixScale);
    ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, reinterpret_cast<float*>(&matrix));

    static bool useSnap(true);
    ImGui::Checkbox(u8"Grap", &useSnap);
    ImGui::SameLine();

    _float3 snap = { 0.f,0.f,0.f };

    switch (mCurrentGizmoOperation)
    {
    case ImGuizmo::TRANSLATE:
        ImGui::InputFloat3(u8"Transform Grap", &snap.x);
        break;

    case ImGuizmo::ROTATE:
        ImGui::InputFloat("Angle Snap", &snap.x);
        break;

    case ImGuizmo::SCALE:
        ImGui::InputFloat(u8"Scale Grap", &snap.x);
        break;
    }

    ImGuiIO& io = ImGui::GetIO();
    ImGuizmo::SetOrthographic(true); // 직교 투영 설정
    ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

    _float4x4	ProjMatrix, ViewMatrix;
    _matrix orthoMatrix = XMMatrixOrthographicLH(g_iWinSizeX, g_iWinSizeY, 0.f, 1.f);
    ProjMatrix = m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_PROJ);
    ViewMatrix = m_pGameInstance->Get_Transform_Float4x4(CPipeLine::D3DTS_VIEW);
    ImGuizmo::Manipulate(reinterpret_cast<float*>(&ViewMatrix), reinterpret_cast<float*>(&orthoMatrix), mCurrentGizmoOperation, ImGuizmo::LOCAL, reinterpret_cast<float*>(&matrix), NULL, useSnap ? &snap.x : NULL);
    
    if (true == ImGui::IsAnyItemHovered() || true == ImGui::IsWindowHovered())
        m_IsMouseHover = true;
    
    ImGui::End();
}

void CImgui_Manager::Gizmo(CTransform* pTransform)
{
    ImGui::Begin("Editor");

    if (ImGuizmo::IsUsing())
    {
        ImGui::Text("Using gizmo");
    }
    else
    {
        ImGui::Text(ImGuizmo::IsOver() ? "Over gizmo" : "");
        ImGui::SameLine();
        ImGui::Text(ImGuizmo::IsOver(ImGuizmo::TRANSLATE) ? "Over translate gizmo" : "");
        ImGui::SameLine();
        ImGui::Text(ImGuizmo::IsOver(ImGuizmo::ROTATE) ? "Over rotate gizmo" : "");
        ImGui::SameLine();
        ImGui::Text(ImGuizmo::IsOver(ImGuizmo::SCALE) ? "Over scale gizmo" : "");
    }

    ImGui::Separator();
 
    EditTransform(pTransform);

    if (true == ImGui::IsAnyItemHovered() || true == ImGui::IsWindowHovered())
        m_IsMouseHover = true;

    ImGui::End();
}

HRESULT CImgui_Manager::Tab_Create_UI(ImVec4& ref_color_v)
{
    /* 0. Create UI Object*/
    static char chDatFileName[MAX_PATH] = "";
    static _int iSelect_UIType = (_int)UI_ID::UI_END;

    ImGui::InputText("Input UI Name", chDatFileName, MAX_PATH);

    string strDatFileName = chDatFileName;

    string strBlank = { "" };

    NL;

    if (ImGui::Button(u8"Create Canvas", ImVec2(100.f, 30.f)) && strDatFileName != strBlank)
    {
        if (FAILED(CreateCanvas(strDatFileName)))
            return E_FAIL;
    }

    ImGui::SeparatorText("UI TYPE");
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "UI TYPE SELECT");

    ImGui::Combo("WindowMenuButtonPosition", (_int*)&iSelect_UIType,
        "Button : Default\0Button : Text\0None\0\0");

    if (NULL != m_pSelectObject)
        m_pSelectCustom->Set_UIID((UI_ID)iSelect_UIType);



    // 1. Create Texture
    if (ImGui::CollapsingHeader(u8"List Tap"))
    {
        if (ImGui::BeginTabBar("UI LIST"))
        {
            if (FAILED(UI_ListEditor()))
                return E_FAIL;

            if (FAILED(DAT_ListEditor()))
                return E_FAIL;

        }
        ImGui::EndTabBar();
    }

    m_pSelectCustom = dynamic_cast<CCustomize_UI*>(m_pSelectObject);

    if (nullptr == m_pSelectObject)
    {
        m_pPrevCustom = nullptr;
        return S_OK;
    }

    // 2. Create Texture
    if (ImGui::CollapsingHeader(u8"FUNCTION"))
    {
        if (ImGui::BeginTabBar("SHADER"))
        {            
            if (FAILED(ShaderEditor(ref_color_v)))
                return E_FAIL;

            if (FAILED(TextBoxEditor()))
                return E_FAIL;

             ImGui::EndTabBar();
        }
    }

    return S_OK;
}

HRESULT CImgui_Manager::ShaderEditor(ImVec4& ref_color_v)
{
    if (ImGui::BeginTabItem("UI COLOR"))
    {
        static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
        static float col4f[4] = { 0.5f, 0.0, 0.0f, 1.0f };

        static bool alpha_preview = true;
        static bool alpha_half_preview = false;
        static bool drag_and_drop = true;
        static bool options_menu = true;
        static bool hdr = false;
        ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

        ImGui::Text("Color button only:");
        static bool no_border = false;
        ImGui::ColorButton("MyColor##3c", *(ImVec4*)&color, misc_flags | (no_border ? ImGuiColorEditFlags_NoBorder : 0), ImVec2(80, 80));

        ImGui::SeparatorText("Color picker");
        static bool alpha = true;
        static bool alpha_bar = true;
        static bool side_preview = true;
        static bool ref_color = false;
        static int display_mode = 0;
        static int picker_mode = 0;

        static _int iStore = 0; /* 저장할 Number*/
        static _int iPrevStore = 0; /* 저장했던 Number*/
        static _int iMaxStore = -1; /* 최대 저장 */

        static _int iCurrentNumber = 0;
        static _float fCurrent_Timer = 0; /* 프레임 재생 시 현재 프레임*/
        static _float fInterver_Timer = 0; /* 프레임 간격*/
        static _float iSpeed = 0; /* Color Speed 값*/
        static _bool isCheck = false; /* Blending 할 것인가?*/

        static _float fBlending = 0; /* 얼마만큼 Blending 할 것인가?*/
        static _float4 vColor = {}; /* 어떤 컬러를 사용할 것인가?*/
        static _int iEnding = { -1 };

        /* Mask */
        // Mask 
        static _bool isMask = {};
        static _float2 fMaskControl = {};
        static _float fMaskSpeed = {};
        static _int iMaskStore = {};

        if (m_pSelectCustom != m_pPrevCustom) /* 다른 객체로 옮겨갈 때 현재 값을 유지하면서 돌릴 것이다. */
        {
            if (NULL == m_pSelectCustom)
                return E_FAIL;

            CCustomize_UI::Value_Color _desc = {};
            _desc = *m_pSelectCustom->Get_Current_Value();

            // 변수 유지 : 다음 배열로 넘어갈 때 그 배열의 값을 되돌린다.
            fBlending = _desc.fBlender_Value;
            isCheck = _desc.isBlender;
            m_isColorChange = _desc.isColorChange;
            m_isAlpaChange = _desc.isAlphaChange;

            vColor = _desc.vColor;
            color.x = vColor.x;
            color.y = vColor.y;
            color.z = vColor.z;
            color.w = vColor.w;

            m_isWave = _desc.isWave;
            m_fWaveSpeed = _desc.WaveSpeed;
            m_isPush = _desc.isPush;
            m_fPushX_Speed = _desc.fPushSpeed.x;
            m_fPushY_Speed = _desc.fPushSpeed.y;
            m_fUVSplit = _desc.fSplit;
            m_fUVRotation = _desc.fPushRotation;

            // m_pSelectCustom->Set_StoreTransform(iStore, pCustomTrans->Get_WorldFloat4x4());
            m_pSelectCustom->Set_Value_Color(&_desc);
            m_pPrevCustom = m_pSelectCustom;
        }


        ImGui::Combo("Display Mode", &display_mode, "Auto/Current\0None\0RGB Only\0HSV Only\0Hex Only\0");
        ImGuiColorEditFlags flags = misc_flags;
        if (!alpha)            flags |= ImGuiColorEditFlags_NoAlpha;        // This is by default if you call ColorPicker3() instead of ColorPicker4()
        if (alpha_bar)         flags |= ImGuiColorEditFlags_AlphaBar;
        if (!side_preview)     flags |= ImGuiColorEditFlags_NoSidePreview;
        if (picker_mode == 1)  flags |= ImGuiColorEditFlags_PickerHueBar;
        if (picker_mode == 2)  flags |= ImGuiColorEditFlags_PickerHueWheel;
        if (display_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;       // Disable all RGB/HSV/Hex displays
        if (display_mode == 2) flags |= ImGuiColorEditFlags_DisplayRGB;     // Override display mode
        if (display_mode == 3) flags |= ImGuiColorEditFlags_DisplayHSV;
        if (display_mode == 4) flags |= ImGuiColorEditFlags_DisplayHex;
        ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, ref_color ? &ref_color_v.x : NULL);

        if (NULL != m_pSelectCustom)
            m_pSelectCustom->Set_EndingType(iEnding);

        /*▶ 버튼 소개 */
        /* 1.1 All Color 바꾸기*/
        ImGui::SeparatorText("Color Change :");
        ImGui::BulletText("You can change the color");

        ImGui::TextColored(ImVec4(1, 1, 0, 1), "COLOR BLENDING");
        ImGui::Checkbox("COLOR BLENDER", &isCheck);
        ImGui::SliderFloat("COLOR BLENDING ", &fBlending, 0.f, 2.f);

        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Color Change");
        if (ImGui::Button("Color Change", ImVec2(110, 20)))
            m_isColorChange = true;

        /* 2. 알파 값 '만' 따로 뺀다 */
        if (ImGui::Button("ONLY ALPA START", ImVec2(110, 20)))
            m_isAlpaChange = true;

        /* 3. Texture 되돌리기*/
        if (ImGui::Button("Return Texture", ImVec2(110, 20)))
        {
            if (nullptr != m_pSelectObject)
            {
                m_isColorChange = false;
                m_isAlpaChange = false;
                col4f[0] = 0.0f;
                m_pSelectCustom->ColorChange_Stop();

            }
        }

#pragma region 컬러 변환
        /* 1. 만약 Color가 시작되고 Player를 하지 않았다면 : 실시간으로 컬러를 집어 넣는다.*/
        if (nullptr != m_pSelectCustom && !m_isPlayControl)
        {
            // Rect의 색상을 넘겨줘야 한다.
            vColor = _float4(color.x, color.y, color.z, color.w);

            if (isCheck) /* Blending 시*/
                m_pSelectCustom->Set_EditColor(vColor, true, fBlending);
            else
                m_pSelectCustom->Set_EditColor(vColor, false);
        }

        if (NULL != m_pSelectCustom)
        {
            m_pSelectCustom->Set_Alpha(m_isAlpaChange);
            m_pSelectCustom->Set_Color(m_isColorChange);
        }

        /* 3. 만약 Color를 키지 않았다면 */
        if (false == m_isColorChange)
        {
            vColor = _float4(1, 1, 1, 1);
            fBlending = false;

            if (NULL != m_pSelectCustom)
                m_pSelectCustom->Set_EditColor(vColor, false, fBlending);
        }

#pragma endregion

#pragma region 프레임 저장 및 프레임 관련 기능
        /*▶ Show Status */
        if (ImGui::Button("SHOW STATUS", ImVec2(110, 30)))
            m_isLook_StoreState = !m_isLook_StoreState;
        SL;
        if (m_isLook_StoreState) {
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "TRUE");
        }
        else {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "FALSE");
        }

        /*▶ FRAME SAVE */
        ImGui::SeparatorText("Frame SAVE :");
        ImGui::BulletText("You can store up to '10 pieces'.");

        /* 1. Color Store : 배열에 컬러를 저장한다, 2가지 색을 반복해서 변환할 수 있음 */
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Frame Save");
        ImGui::SliderInt("FRAME SAVE ", &iStore, 0, 10);

        CTransform* pCustomTrans = {};

        if (NULL != m_pSelectObject)
            pCustomTrans = dynamic_cast<CTransform*>(m_pSelectObject->Get_Component(g_strTransformTag));
       
        if (iPrevStore != iStore) /* 다른 스토어로 변환할 때마다 저장했던 값을 찾아 전달해줄 것이다 */
        {
            if (NULL == m_pSelectObject || NULL == pCustomTrans)
                return E_FAIL;

            CCustomize_UI::Value_Color _desc = {};
            CCustomize_UI::Value_Mask    _mask = {};

            // 변수 유지 : 다음 배열로 넘어갈 때 그 배열의 값을 되돌린다.
            _desc.fBlender_Value = fBlending = m_pSelectCustom->Get_Value_Color(iStore).fBlender_Value;
            _desc.isBlender = isCheck = m_pSelectCustom->Get_Value_Color(iStore).isBlender;
            _desc.isColorChange = m_isColorChange = m_pSelectCustom->Get_Value_Color(iStore).isColorChange;
            _desc.isAlphaChange = m_isAlpaChange = m_pSelectCustom->Get_Value_Color(iStore).isAlphaChange;
            _desc.vColor = vColor = m_pSelectCustom->Get_Value_Color(iStore).vColor;
            color.x = vColor.x;
            color.y = vColor.y;
            color.z = vColor.z;
            color.w = vColor.w;

            _desc.isWave = m_isWave = m_pSelectCustom->Get_Value_Color(iStore).isWave;
            _desc.WaveSpeed = m_fWaveSpeed = m_pSelectCustom->Get_Value_Color(iStore).WaveSpeed;
            _desc.isPush = m_isPush = m_pSelectCustom->Get_Value_Color(iStore).isPush;
            _desc.fPushSpeed.x = m_fPushX_Speed = m_pSelectCustom->Get_Value_Color(iStore).fPushSpeed.x;
            _desc.fPushSpeed.y = m_fPushY_Speed = m_pSelectCustom->Get_Value_Color(iStore).fPushSpeed.y;
            _desc.fSplit = m_fUVSplit = m_pSelectCustom->Get_Value_Color(iStore).fSplit;
            _desc.fPushRotation = m_fUVRotation = m_pSelectCustom->Get_Value_Color(iStore).fPushRotation;

            _mask.isMask = isMask = m_pSelectCustom->Get_Value_Mask(iStore).isMask;
            _mask.fMaskControl = fMaskControl = m_pSelectCustom->Get_Value_Mask(iStore).fMaskControl;
            _mask.fMaskSpeed = fMaskSpeed = m_pSelectCustom->Get_Value_Mask(iStore).fMaskSpeed;

            m_pSelectCustom->Set_StoreTransform(iStore, pCustomTrans->Get_WorldFloat4x4());
            m_pSelectCustom->Set_CurrentMask(&_mask);
            m_pSelectCustom->Set_Value_Color(&_desc);

            iPrevStore = iStore;
        }

        /* 2. Save */
        if (ImGui::Button(u8"FRAME SAVE", ImVec2(100.f, 20.f)))
        {
            if (nullptr != m_pSelectObject)
            {
                CCustomize_UI::Value_Color tDesc = {};
                _float4 vColor = _float4(color.x, color.y, color.z, color.w);

                tDesc.vColor = vColor;
                tDesc.fBlender_Value = fBlending;
                tDesc.isBlender = isCheck;

                tDesc.isColorChange = m_isColorChange;
                tDesc.isAlphaChange = m_isAlpaChange;

                tDesc.WaveSpeed = m_fWaveSpeed;
                tDesc.isWave = m_isWave;

                tDesc.isPush = m_isPush;
                tDesc.fPushSpeed = _float2(m_fPushX_Speed, m_fPushY_Speed);
                tDesc.fPushRotation = m_fUVRotation;
                tDesc.fSplit = m_fUVSplit;

                m_pSelectCustom->isColor_Size(iStore, tDesc, iEnding);
                m_pSelectCustom->Set_StoreTransform(iStore, pCustomTrans->Get_WorldFloat4x4());

                // Mask
                CCustomize_UI::Value_Mask maskDesc = {};
                maskDesc.isMask = isMask;
                maskDesc.fMaskControl = fMaskControl;
                maskDesc.fMaskSpeed = fMaskSpeed;

                m_pSelectCustom->Set_StoreMask(iStore, &maskDesc);

                if (iStore < 0)
                    return E_FAIL;

                /* 만약 Max보다 더 크다면 Save 최대 값을 올려줍니다. */
                if (iMaxStore <= iStore)
                {
                    m_pSelectCustom->Set_MaxColor(iStore);
                    iMaxStore = iStore;
                }
            }
        }
        
        struct Funcs
        {
            static float Sin(void*, int i) { return sinf(i * 0.1f); }
            static float Saw(void*, int i) { return (i & 1) ? 1.0f : -1.0f; }
        };

        static _int iFramePlay = -1;
        static _float fRatioTimes = 0;
        float (*func)(void*, int) = Funcs::Sin;

        ImGui::SeparatorText("FRAME STATUS");
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Ending Type");

        ImGui::RadioButton("Ending Change", &iEnding, PLAY_BUTTON::PLAY_DEFAULT);
        ImGui::RadioButton("Ending Default Play", &iEnding, PLAY_BUTTON::PLAY_CHANGE);
        ImGui::RadioButton("Ending Cutting ", &iEnding, PLAY_BUTTON::PLAY_CUT);

        ImGui::SeparatorText("");
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Play Frame");
        ImGui::RadioButton("FRAME START", &iFramePlay, PLAY_BUTTON::PLAY_DEFAULT);
        ImGui::RadioButton("FRAME STOP", &iFramePlay, PLAY_BUTTON::PLAY_CHANGE);

        /* 0. 보간 시간을 보여준다.  */
        if (NULL != m_pSelectCustom)
            fRatioTimes = m_pSelectCustom->Get_CurrentRatioTime();

        ImGui::PlotLines("Lines", func, NULL, (_int)(fRatioTimes * 10), 0, NULL, -1.0f, 1.0f, ImVec2(0.f, 80.f));

        /* 1. Play Default 관련 */
        if (PLAY_BUTTON::PLAY_DEFAULT == iFramePlay)
        {
            if (nullptr != m_pSelectCustom)
            {
                /* m_isPlayControl : Play가 된다면 Save 했던 값들을 보간하기 위해서 현재 조정하던 값들을 종료한다. */
                m_isPlayControl = true;

                fCurrent_Timer = m_pSelectCustom->Get_ColorTimer();

                if (NULL != m_pSelectCustom)
                    m_pSelectCustom->Set_ColorPlay(true);
            }
        }

        /* 2. Play Change 관련 기능 */
        if (PLAY_BUTTON::PLAY_CHANGE == iFramePlay)
        {
            fCurrent_Timer = 0.f;
            m_isPlayControl = false;

            if (NULL != m_pSelectCustom)
                m_pSelectCustom->Set_ColorPlay(false);
        }

        if (NULL == m_pSelectCustom)
        {
            col4f[0] = 0;
            ImGui::SliderFloat("COLOR TIMER", &col4f[0], 0.0f, 0.f);

            ImGui::Text("CURRENT FRAME: (%g)", 0.f);
            ImGui::Text("INTERVER FRAME: (%g)", 0.f);
        }
        else
        {
            ImGui::Text("CURRENT TIMER: (%g)", m_pSelectCustom->Get_ColorTimer());
            ImGui::Text("INTERVER TIMER: (%g)", m_pSelectCustom->Get_Interver_Timer());
        }

        /* 3. Frame 시간 관련 기능 */
        ImGui::SeparatorText("PLAY Timer :");
        ImGui::BulletText("'Max time == speed value' is natural");
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Current Frame");
        ImGui::BulletText("Tish Current Frame.");
        ImGui::SliderFloat("CURRENT FRAME", &fCurrent_Timer, 0.0f, 10.0f);

        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Interver Frame");
        ImGui::BulletText("The arrangement changes every few seconds.");
        ImGui::SliderFloat("INTERVER FRAME", &fInterver_Timer, 0.0f, 10.0f);

        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Speed Frame");
        ImGui::BulletText("Adjust the frame speed.");
        ImGui::SliderFloat("FRAME SPEED", &iSpeed, 0.0f, 1.0f);

        if (nullptr != m_pSelectCustom)
        {
            m_pSelectCustom->Set_ColorTimer(fCurrent_Timer);
            m_pSelectCustom->Set_Interver_Timer(fInterver_Timer);
            m_pSelectCustom->Set_ColorSpeed(iSpeed);
        }

#pragma endregion

#pragma region Mask
        /////////////////////////////// [ Mask ] ///////////////////////////////////
        ImGui::SeparatorText("MASK STATE");

        /* 실시간으로 확인할 수 있는 확인용 함수*/
        if (ImGui::Button("Mask", ImVec2(110, 20)))
            isMask = true;

        /* 멈출 시에 초기화*/
        if (ImGui::Button("NonMask", ImVec2(110, 20)))
        {
            isMask = false;

            CCustomize_UI::Value_Mask* _customMask = new CCustomize_UI::Value_Mask{};

            if (NULL != _customMask)
            {
                _customMask->isMask = false;
                _customMask->fMaskControl = _float2(0, 0);
                _customMask->fMaskSpeed = 0.f;

                m_pSelectCustom->Set_CurrentMask(_customMask);
            }
        }

        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mask State");
        ImGui::SliderFloat("MASK ALPHA", &fMaskControl.x, 0.0f, 2.0f);
        ImGui::SliderFloat("MASK WITH", &fMaskControl.y, 0.0f, 2.0f);
        ImGui::SliderFloat("MASK SPEED", &fMaskSpeed, 0.0f, 5.0f);

        /* 현재 마스크 Value*/
        if (isMask && !m_isPlayControl)
        {
            if (NULL != m_pSelectCustom)
            {
                CCustomize_UI::Value_Mask* _customMask = new CCustomize_UI::Value_Mask{};

                if (NULL != _customMask)
                {
                    _customMask->isMask = isMask;
                    _customMask->fMaskControl = fMaskControl;
                    _customMask->fMaskSpeed = fMaskSpeed;

                    m_pSelectCustom->Set_CurrentMask(_customMask);
                }
            }
        }
        

#pragma region Wave 관련 기능
        static _int iWavePlay = -1;

        ImGui::SeparatorText(" WAVE ");
        ImGui::Text(u8"SPEED WAVE");
        ImGui::SliderFloat("SPEED WAVE", &m_fWaveSpeed, 0.0f, 2.0f);
        ImGui::RadioButton("WAVE START", &iWavePlay, PLAY_BUTTON::PLAY_DEFAULT);
        ImGui::RadioButton("WAVE STOP", &iWavePlay, PLAY_BUTTON::PLAY_CHANGE);

        /* 1. Wave Play 관련  */
        if (PLAY_BUTTON::PLAY_DEFAULT == iWavePlay)
        {
            m_isWave = true;
        }

        if (PLAY_BUTTON::PLAY_CHANGE == iWavePlay)
        {
            if (NULL != m_pSelectCustom)
            {
                if (nullptr != m_pSelectCustom)
                    m_pSelectCustom->Set_Wave(false, 0.0f);
            }

            m_isWave = false;
        }

        if (m_isWave && !m_isPlayControl)
        {
            if (NULL != m_pSelectCustom)
                m_pSelectCustom->Set_Wave(true, m_fWaveSpeed);
        }

#pragma endregion

#pragma region Push 관련 기능
        static _int iPushPlay = -1;

        ImGui::SeparatorText(" PUSH ");
        ImGui::Text(u8"SPEED PUSH");
        ImGui::SliderFloat("X SPEED PUSH", &m_fPushX_Speed, 0.0f, 2.0f);
        ImGui::SliderFloat("Y SPEED PUSH", &m_fPushY_Speed, 0.0f, 2.0f);

        ImGui::Text(u8"UV ROTATION");
        ImGui::SliderFloat("UV ROTATION", &m_fUVRotation, 0.0f, 3.0f);

        ImGui::Text(u8"UV SPILT");
        ImGui::SliderFloat("UV SPILT", &m_fUVSplit, 0.0f, 30.f);

        ImGui::RadioButton("PUSH START", &iPushPlay, PLAY_BUTTON::PLAY_DEFAULT);
        ImGui::RadioButton("PUSH STOP", &iPushPlay, PLAY_BUTTON::PLAY_CHANGE);

        m_fUVSplit = (_float)((_int)m_fUVSplit);

        if (PLAY_BUTTON::PLAY_DEFAULT == iPushPlay)
        {
            m_isPush = true;
        }

        if (PLAY_BUTTON::PLAY_CHANGE == iPushPlay)
        {
            if (NULL != m_pSelectCustom)
                m_pSelectCustom->Set_PushUV(false, 0.0f, 0.0f, 0.f, 1.f);

            m_isPush = false;
        }

        if (m_isPush && !m_isPlayControl)
        {
            if (NULL != m_pSelectCustom)
                m_pSelectCustom->Set_PushUV(true, m_fPushX_Speed, m_fPushY_Speed, m_fUVRotation, m_fUVSplit);
        }
        ImGui::EndTabItem();
    }
#pragma endregion

    return S_OK;
}

HRESULT CImgui_Manager::Status_Box()
{
    ImGui::Text("STATUS BOX");
    static _int iBoxSize = 0;
    static _int mode = 0;
    static _int selected_fish = -1;
    static _int select = -1;
    static const char* names[11] =
    {
        "STORE0", "STORE1", "STORE2", "STORE3", "STORE4", "STORE5", "STORE6", "STORE7", "STORE8", "STORE9", "STORE10"
    };

    if (NULL != m_pSelectCustom)
        iBoxSize = m_pSelectCustom->Get_MaxSize();

    /* ▶ Box 생성 */
    if (ImGui::RadioButton("Copy", mode == Mode_Copy)) { mode = Mode_Copy; } SL;
    if (ImGui::RadioButton("Move", mode == Mode_Move)) { mode = Mode_Move; } SL;
    if (ImGui::RadioButton("Swap", mode == Mode_Swap)) { mode = Mode_Swap; }

    for (int n = 0; n < IM_ARRAYSIZE(names); n++)
    {
        // 만약 생성보다 많다면 Break;
        if (n > iBoxSize)
            break;

        ImGui::PushID(n);
        if ((n % 5) != 0) SL;

        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
        {
            ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(_int));

            select = n - 1;
            if (mode == Mode_Copy) { ImGui::Text("Copy %s", names[select]); }
            if (mode == Mode_Move) { ImGui::Text("Move %s", names[select]); }
            if (mode == Mode_Swap) { ImGui::Text("Swap %s", names[select]); }
            ImGui::EndDragDropSource();
        }

        if (ImGui::Button(names[n], ImVec2(60, 30)))
            ImGui::OpenPopup("my_select_popup");

        if (ImGui::BeginPopup("my_select_popup"))
        {
            ImGui::SeparatorText("Status");

            /* 클릭한 것만 출력해야 함*/
            for (int i = n; i < n + 1; i++)
            {
                CCustomize_UI::Value_Color _color = {};
                char buffer[32];
                string colorName[13];
                const char* cstr[13];
                const char* cTag[14] =
                {
                    "Color Change : " ,"Only Alpha Change : ", "Blending : ", "Blending Value : ",
                    "R :", "G :", "B :", "A :",
                    "Wave : ", "Wave Speed : ", "Push : ", "Push Rotation Speed : ", "Split : "
                };

                if (NULL != m_pSelectCustom)
                    _color = m_pSelectCustom->Get_Value_Color(i);

                /* 1. Color를 바꿀 수 있는가? */
                if (TRUE == _color.isColorChange)
                    colorName[0] = "TRUE";
                else
                    colorName[0] = "FALSE";

                cstr[0] = colorName[0].c_str();

                /* 2. 오직 Alpha 만 바꿀 수 있는가? */
                if (TRUE == _color.isAlphaChange)
                    colorName[1] = "TRUE";
                else
                    colorName[1] = "FALSE";

                cstr[1] = colorName[1].c_str();

                /* 3. Blending을 할 수 있는가? */
                if (TRUE == _color.isBlender)
                    colorName[2] = "TRUE";
                else
                    colorName[2] = "FALSE";

                cstr[2] = colorName[2].c_str();

                /* 4. Blending이 가능하다면 값이 얼마인가? */
                sprintf_s(buffer, "%f", _color.fBlender_Value);
                colorName[3] = buffer;
                cstr[3] = colorName[3].c_str();

                /* 5. 사용 중인 Color는 RGBA 값이 얼마인가? */
                sprintf_s(buffer, "%f", _color.vColor.x);
                colorName[4] = buffer;
                cstr[4] = colorName[4].c_str();

                sprintf_s(buffer, "%f", _color.vColor.y);
                colorName[5] = buffer;
                cstr[5] = colorName[5].c_str();

                sprintf_s(buffer, "%f", _color.vColor.z);
                colorName[6] = buffer;
                cstr[6] = colorName[6].c_str();

                sprintf_s(buffer, "%f", _color.vColor.w);
                colorName[7] = buffer;
                cstr[7] = colorName[7].c_str();

                /* 6. Wave 가 가능한가? */
                if (TRUE == _color.isWave)
                    colorName[8] = "TRUE";
                else
                    colorName[8] = "FALSE";
                cstr[8] = colorName[8].c_str();

                /* 7. 그렇다면 Wave speed 가 얼마인가? */
                sprintf_s(buffer, "%f", _color.WaveSpeed);
                colorName[9] = buffer;
                cstr[9] = colorName[9].c_str();

                /* 8. Push 가 가능한가? */
                if (TRUE == _color.isPush)
                    colorName[10] = "TRUE";
                else
                    colorName[10] = "FALSE";
                cstr[10] = colorName[10].c_str();

                /* 10. 그렇다면 Push Rotation가 얼마인가? */
                sprintf_s(buffer, "%f", _color.fPushRotation);
                colorName[11] = buffer;
                cstr[11] = colorName[11].c_str();

                /* 11. Split 가 얼마인가? */
                sprintf_s(buffer, "%f", _color.fSplit);
                colorName[12] = buffer;
                cstr[12] = colorName[12].c_str();

                if (NULL != m_pSelectCustom)
                    _color = m_pSelectCustom->Get_Value_Color(i);

                for (_uint i = 0; i < IM_ARRAYSIZE(colorName); i++)
                {
                    ImGui::TextUnformatted(selected_fish == -1 ? "<None>" : cTag[i]); SL;
                    ImGui::TextUnformatted(selected_fish == -1 ? "<None>" : cstr[i]);

                    if (5 <= i && 8 > i)
                        SL;
                }

                selected_fish = i;
            }

            ImGui::EndPopup();
        }
        ImGui::PopID();

        /* ▶ 값을 변경하는 기능 */
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
            {
                IM_ASSERT(payload->DataSize == sizeof(int));
                _int payload_n = *(const int*)payload->Data;

                if (0 > n)
                    return E_FAIL;

                /* 1. 값을 복사 한다 */
                if (mode == Mode_Copy)
                {
                    m_pSelectCustom->isColor_Size(payload_n, m_pSelectCustom->Get_Value_Color(n - 1), m_pSelectCustom->Get_EndingType());
                }

                /* 2. 값을 이동시킨다.*/
                if (mode == Mode_Move)
                {
                    CCustomize_UI::Value_Color pColor_Struct = {};

                    m_pSelectCustom->isColor_Size(payload_n, m_pSelectCustom->Get_Value_Color(n - 1), m_pSelectCustom->Get_EndingType());
                    m_pSelectCustom->isColor_Size(n - 1, pColor_Struct, 0);
                }

                /* 3. 값을 바꾼다. */
                if (mode == Mode_Swap)
                {
                    CCustomize_UI::Value_Color pColor_Struct1 = {};
                    CCustomize_UI::Value_Color pColor_Struct2 = {};

                    pColor_Struct1 = m_pSelectCustom->Get_Value_Color(n - 1);
                    pColor_Struct2 = m_pSelectCustom->Get_Value_Color(payload_n);

                    m_pSelectCustom->isColor_Size(payload_n, pColor_Struct1, m_pSelectCustom->Get_EndingType());
                    m_pSelectCustom->isColor_Size(n - 1, pColor_Struct2, m_pSelectCustom->Get_EndingType());
                 }
             }
             ImGui::EndDragDropTarget();
         }
    }
       
    return S_OK;
}


HRESULT CImgui_Manager::TextBoxEditor()
{
    if (ImGui::BeginTabItem("TEXT_BOX"))
    {
        ImGui::SeparatorText("Add Text Box");

        wstring strBlank = {TEXT("")};

        static char chText[1024] = "";

        ImGui::InputText("Edit Text", chText, sizeof(chText));

        wstring wstrText = UTF8ToUTF16(chText);

        if (ImGui::Button(u8"Create TextBox", ImVec2(100.f, 30.f) ) && wstrText != strBlank)
        {
            CTextBox::TextBox_DESC TextBoxDesc = {};
            TextBoxDesc.vPos = _float3(g_iWinSizeX / 2, g_iWinSizeY / 2, 0);
            TextBoxDesc.vSize = _float2(200.f, 200.f);
            TextBoxDesc.wstrText = wstrText;
            TextBoxDesc.wstrFontType = TEXT("Font_CG");
            TextBoxDesc.iFontSize = 14;
            TextBoxDesc.vFontColor = XMVectorSet(0.f, 0.f, 0.f, 1.f);
            CGameObject* pTextBox = m_pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_TextBox"), &TextBoxDesc);
            if (nullptr == pTextBox)
                return E_FAIL;

            dynamic_cast<CCustomize_UI*>(m_pSelectObject)->PushBack_TextBox(pTextBox);
            m_mapTextBoxes.emplace(wstrText, dynamic_cast<CTextBox*>(pTextBox));
        }

        ImGui::SeparatorText("TextBox List");

        if (ImGui::BeginListBox(u8"##TEXT_BOX LIST", ImVec2(100.f, 100.f)))
        {
            _int TextlistCount = 0;

            for (auto& iter : *dynamic_cast<CCustomize_UI*>(m_pSelectObject)->Get_vecTextBoxes())
            {
                wstring wstrText = iter->Get_TextBoxDesc().wstrText;
                string strText = wstring_to_utf8(wstrText);

                if (ImGui::Selectable(strText.c_str(), m_iSelectedNumInTextBox == TextlistCount))
                {
                    CComponent* pComponent = Find_TextBox(wstrText)->Get_Component(g_strTransformTag);
                    m_pGizmoTransform = dynamic_cast<CTransform*>(pComponent);
                    m_strSelectedTextBox = wstrText;
                    m_iSelectedNumInTextBox = TextlistCount;
                }
                TextlistCount++;
            }
            ImGui::EndListBox();
        }

        static char str[MAX_PATH] = "";
        ImGui::InputTextMultiline("##Edit_TextBoxText", str, sizeof(str), ImVec2(200, 50));

        if (ImGui::Button(u8"Edit TextBoxText", ImVec2(100.f, 30.f)) && TEXT("") != m_strSelectedTextBox)
        {
            wstring wstrEditText = UTF8ToUTF16(str);
            m_mapTextBoxes.find(m_strSelectedTextBox)->second->Set_Text(wstrEditText);
        }

        ImGui::SeparatorText("FontColor Editor");

        FontColor_Editor();

        ImGui::SeparatorText("TextSize Editor");
        static int FontSize = 10;
        ImGui::SliderInt("##FontSizeSlider", &FontSize, 10, 20);
        if (ImGui::Button(u8"FontSizeSliderButton", ImVec2(100.f, 30.f)) && TEXT("") != m_strSelectedTextBox)
        {
            wstring wstrEditText = UTF8ToUTF16(str);
            m_mapTextBoxes.find(m_strSelectedTextBox)->second->Set_FontSize(FontSize);
        }

        ImGui::SeparatorText("TextOutLine");
        if (ImGui::Button(u8"FontOutLine", ImVec2(100.f, 30.f)) && TEXT("") != m_strSelectedTextBox)
        {
            wstring wstrEditText = UTF8ToUTF16(str);
            _bool IsOutLine = m_mapTextBoxes.find(m_strSelectedTextBox)->second->Get_isOutLine();
            m_mapTextBoxes.find(m_strSelectedTextBox)->second->Set_isOutLine(!IsOutLine);
        }

        ImGui::EndTabItem();
    }

    return S_OK;
}

HRESULT CImgui_Manager::FontColor_Editor()
{
    static ImVec4 ref_color_a(1.0f, 0.0f, 1.0f, 0.5f); // Color 변수
    static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
    static float col4f[4] = { 0.5f, 0.0, 0.0f, 1.0f };

    static bool alpha_preview = true;
    static bool alpha_half_preview = false;
    static bool drag_and_drop = true;
    static bool options_menu = true;
    static bool hdr = false;
    ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

    static bool alpha = true;
    static bool alpha_bar = true;
    static bool side_preview = true;
    static bool ref_color = false;
    static int display_mode = 0;
    static int picker_mode = 0;

    static _int iStore = 0; /* 저장할 Number*/
    static _int iPrevStore = 0; /* 저장했던 Number*/

    static _int iCurrentNumber = 0;
    static _float fCurrent_Timer = 0; /* 프레임 재생 시 현재 프레임*/
    static _float fInterver_Timer = 0; /* 프레임 간격*/
    static _int iMaxStore = 0; /* 최대 저장 */
    static _float iSpeed = 0; /* Color Speed 값*/
    static _bool isCheck = false; /* Blending 할 것인가?*/

    static _float fBlending = 0; /* 얼마만큼 Blending 할 것인가?*/
    static _float4 vColor = {}; /* 어떤 컬러를 사용할 것인가?*/
    static _int iEnding = { -1 };

    ImGui::Combo("Display Mode", &display_mode, "Auto/Current\0None\0RGB Only\0HSV Only\0Hex Only\0");
    ImGuiColorEditFlags flags = misc_flags;
    if (!alpha)            flags |= ImGuiColorEditFlags_NoAlpha;        // This is by default if you call ColorPicker3() instead of ColorPicker4()
    if (alpha_bar)         flags |= ImGuiColorEditFlags_AlphaBar;
    if (!side_preview)     flags |= ImGuiColorEditFlags_NoSidePreview;
    if (picker_mode == 1)  flags |= ImGuiColorEditFlags_PickerHueBar;
    if (picker_mode == 2)  flags |= ImGuiColorEditFlags_PickerHueWheel;
    if (display_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;       // Disable all RGB/HSV/Hex displays
    if (display_mode == 2) flags |= ImGuiColorEditFlags_DisplayRGB;     // Override display mode
    if (display_mode == 3) flags |= ImGuiColorEditFlags_DisplayHSV;
    if (display_mode == 4) flags |= ImGuiColorEditFlags_DisplayHex;
    ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, ref_color ? &ref_color_a.x : NULL);

    _vector vSetColor = XMVectorSet(color.x, color.y, color.z, color.w);

    if (TEXT("") != m_strSelectedTextBox)
        m_mapTextBoxes.find(m_strSelectedTextBox)->second->Set_FontColor(vSetColor);

    return S_OK;
}

HRESULT CImgui_Manager::UI_ListEditor()
{
    if (ImGui::BeginTabItem("UI LIST"))
    {
        // List Box
        if (ImGui::BeginListBox(u8"UI LIST"))
        {
            if (!m_mapGameObjects.empty())
            {
                _int listCount = 0;
                for (const auto& pair : m_mapGameObjects)
                {
                    string strName = { "" };
                    strName.assign(pair.first.begin(), pair.first.end());

                    if (ImGui::Selectable(strName.c_str(), m_iUI_Selected == listCount))
                    {
                        m_strSelected_UI_inList = strName;
                        CGameObject* pGameobj = Find_GameObject(m_strSelected_UI_inList);
                        if (nullptr != pGameobj)
                        {
                            m_iUI_Selected = listCount;
                            m_pSelectObject = pGameobj;//Find Object
                            m_isUse_UIGizmo = true;
                            m_pGizmoTransform = dynamic_cast<CTransform*>(m_pSelectObject->Get_Component(g_strTransformTag));
                        }
                    }
                    listCount++;
                }
            }
            ImGui::EndListBox();
        }

        if (ImGui::Button(u8"Child Create", ImVec2(100.f, 30.f)))
        {
            if (FAILED(CreateChild()))
                return E_FAIL;
        }

        SL;


        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.0f, 1.0f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));

        /* 해당 객체를 삭제 시킨다. */
        if (ImGui::Button(u8"DELETE", ImVec2(100.f, 30.f)))
        {
            Delete_GameObject(m_strSelected_UI_inList);
            m_iUI_Selected = -1;
            //CGameObject* pGameObj = Find_GameObject(m_strSelected_UI_inList);

            //if (nullptr != pGameObj)
            //    Delete_GameObject(pGameObj);
        }

        ImGui::PopStyleColor(3);

        NL;

        if (ImGui::Button(u8"Save", ImVec2(100.f, 30.f)))
        {
            m_bDirectoryChooserWindow = true;
        }


        //여기가 탭끝
        ImGui::EndTabItem();
    }

    return S_OK;
}



HRESULT CImgui_Manager::DAT_ListEditor()
{
    if (ImGui::BeginTabItem("DatFileList"))
    {
        if (ImGui::Button(u8"OPEN DAT FILE DIALOG", ImVec2(100.f, 30.f)))
        {
            m_bDatDialogWindow = true;
        }

        // List Box
        if (ImGui::BeginListBox(u8"DatFileList"))
        {
            if (!m_mapDatFailes.empty())
            {
                _int listCount = 0;
                for (const auto& pair : m_mapDatFailes)
                {
                    string strName = { "" };
                    strName.assign(pair.first.begin(), pair.first.end());

                    if (ImGui::Selectable(strName.c_str(), m_iSelectNumInDatList == listCount))
                    {
                        m_iSelectNumInDatList = listCount;
                        strSelected_Data_inList = strName;
                    }
                    listCount++;
                }
            }
            ImGui::EndListBox();
        }

        if (ImGui::Button(u8"LOAD DATA FILE", ImVec2(105.f, 30.f)))
        {
            if (strSelected_Data_inList != "")
            {
                wstring selectedFilePath = m_mapDatFailes.find(strSelected_Data_inList)->second;
                ifstream inputFileStream;
                inputFileStream.open(selectedFilePath, ios::binary);
                CreatFromDat(inputFileStream, (""), nullptr);
            }
        }
        SL;

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.0f, 1.0f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));

        /*리스트에서 삭제한다*/
        if (ImGui::Button(u8"DELETE", ImVec2(100.f, 30.f)))
        {
            if (strSelected_Data_inList != "")
            {
                auto it = m_mapDatFailes.find(strSelected_Data_inList);
                if (m_mapDatFailes.end() != it)
                {
                    m_mapDatFailes.erase(it);
                }
            }
        }

        ImGui::PopStyleColor(3);
        ImGui::EndTabItem();
    }

    return S_OK;
}

HRESULT CImgui_Manager::CreateChild()
{
    if (nullptr != m_pSelectObject)
    {
        CCustomize_UI::CUSTOM_UI_DESC   tDesc = {};

        tDesc.vPos = _float3(g_iWinSizeX / 2, g_iWinSizeY / 2, 0);
        tDesc.vSize = _float2(200.f, 200.f);
        tDesc.strTextureName = TEXT("../Bin/Resources/Textures/UI/White_BackGround.png");
        tDesc.strModelName = TEXT("Prototype_Component_Texture_White_BackGround");
        tDesc.iColorMaxNum = 0;
        tDesc.isPlay = false;
        tDesc.fColorTimer_Limit = { 0.f };
        tDesc.iEndingType = PLAY_BUTTON_END;

        if (FAILED(m_pGameInstance->Add_Clone(m_pGameInstance->Get_CurrentLevel(), TEXT("Layer_UI"), TEXT("Prototype_GameObject_CCustomize_UI"), &tDesc)))
            return E_FAIL;

        CGameObject* pGameObjact = m_pGameInstance->Get_LayerList(m_pGameInstance->Get_CurrentLevel(), TEXT("Layer_UI"))->back();

        string ObjName = m_strSelected_UI_inList + ("_Child");
        auto iter = m_mapGameObjects.find(ObjName);
        if (iter != m_mapGameObjects.end())
        {
            _bool IsSameName = true;
            _uint NameNum = 0;

            while (true == IsSameName)
            {
                string FileNameTrashCan = ObjName + to_string(NameNum);
                iter = m_mapGameObjects.find(FileNameTrashCan);
                if (iter == m_mapGameObjects.end())
                {
                    IsSameName = false;
                    ObjName = FileNameTrashCan;
                }
                NameNum++;
            }
        }

        m_mapGameObjects.emplace(ObjName, pGameObjact);
        m_vecCutomizeUI.push_back(dynamic_cast<CCustomize_UI*>(pGameObjact));
        m_pSelectCustom->PushBack_Child(pGameObjact);
    }

    return S_OK;
}

HRESULT CImgui_Manager::CreateCanvas(string strDatFileName)
{
    auto iter = m_mapGameObjects.find(strDatFileName);
    if (iter != m_mapGameObjects.end())
    {
        _bool IsSameName = true;
        _uint NameNum = 0;

        while (true == IsSameName)
        {
            string FileNameTrashCan = strDatFileName + to_string(NameNum);
            iter = m_mapGameObjects.find(FileNameTrashCan);
            if (iter == m_mapGameObjects.end())
            {
                IsSameName = false;
                strDatFileName = FileNameTrashCan;
            }
            NameNum++;
        }
    }

    CCustomize_UI::CUSTOM_UI_DESC   tDesc = {};

    tDesc.vPos = _float3(g_iWinSizeX / 2, g_iWinSizeY / 2, 0);
    tDesc.vSize = _float2(200.f, 200.f);
    tDesc.strTextureName = TEXT("../Bin/Resources/Textures/UI/White_BackGround.png");
    tDesc.strModelName = TEXT("Prototype_Component_Texture_White_BackGround");
    tDesc.iColorMaxNum = 0;
    tDesc.isPlay = false;
    tDesc.fColorTimer_Limit = { 0.f };
    tDesc.iEndingType = PLAY_BUTTON_END;

    if (FAILED(m_pGameInstance->Add_Clone(m_pGameInstance->Get_CurrentLevel(), TEXT("Layer_UI"), TEXT("Prototype_GameObject_CCustomize_UI"), &tDesc)))
        return E_FAIL;

    CGameObject* pGameObjact = m_pGameInstance->Get_LayerList(m_pGameInstance->Get_CurrentLevel(), TEXT("Layer_UI"))->back();
    m_mapGameObjects.emplace(strDatFileName, pGameObjact);
    m_vecCutomizeUI.push_back(dynamic_cast<CCustomize_UI*>(pGameObjact));

    return E_NOTIMPL;
}

void CImgui_Manager::InitFileDialog()
{
    m_pFDFM_OBJList.SetCreateThumbnailCallback([this](IGFD_Thumbnail_Info* vThumbnail_Info) -> void
        {
            if (vThumbnail_Info &&
                vThumbnail_Info->isReadyToUpload &&
                vThumbnail_Info->textureFileDatas)
            {
                // 텍스처 설명 구조체를 준비합니다.
                D3D11_TEXTURE2D_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                desc.Width = vThumbnail_Info->textureWidth;
                desc.Height = vThumbnail_Info->textureHeight;
                desc.MipLevels = 1;
                desc.ArraySize = 1;
                desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // RGBA
                desc.SampleDesc.Count = 1;
                desc.Usage = D3D11_USAGE_DEFAULT;
                desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                desc.CPUAccessFlags = 0;

                // 초기 데이터를 준비합니다.
                D3D11_SUBRESOURCE_DATA initData;
                initData.pSysMem = vThumbnail_Info->textureFileDatas;
                initData.SysMemPitch = vThumbnail_Info->textureWidth * 4; // RGBA는 4바이트입니다.
                initData.SysMemSlicePitch = 0; // 2D 텍스처에는 사용되지 않습니다.

                // 텍스처를 생성합니다.
                ID3D11Texture2D* pTexture = nullptr;
                HRESULT hr = m_pDevice->CreateTexture2D(&desc, &initData, &pTexture);

                // 텍스처 뷰를 생성합니다.
                ID3D11ShaderResourceView* pTextureView = nullptr;
                if (SUCCEEDED(hr))
                {
                    hr = m_pDevice->CreateShaderResourceView(pTexture, nullptr, &pTextureView);
                }

                // 사용한 리소스를 정리합니다.
                if (pTexture) pTexture->Release();

                delete[] vThumbnail_Info->textureFileDatas;
                vThumbnail_Info->textureFileDatas = nullptr;

                // 콜백 정보를 업데이트합니다.
                vThumbnail_Info->textureID = pTextureView; // DirectX11에서는 Shader Resource View를 사용합니다.
                vThumbnail_Info->isReadyToUpload = false;
                vThumbnail_Info->isReadyToDisplay = true;
            }
        });


    m_pFDFM_OBJList.SetDestroyThumbnailCallback([](IGFD_Thumbnail_Info* vThumbnail_Info)
        {
            if (vThumbnail_Info)
            {
                // DirectX11에서 텍스처는 ID3D11ShaderResourceView* 형태로 관리됩니다. 
                // 이 예제에서는 textureID가 ID3D11ShaderResourceView* 형태로 캐스팅되어 사용되고 있다고 가정합니다.
                ID3D11ShaderResourceView* texSRV = static_cast<ID3D11ShaderResourceView*>(vThumbnail_Info->textureID);
                if (texSRV)
                {
                    // 텍스처 뷰를 먼저 해제합니다.
                    texSRV->Release();

                    // 이후에 필요하다면 텍스처 자체도 해제할 수 있습니다.
                    // 예제 코드에서는 textureID가 ID3D11ShaderResourceView만을 가리키고 있다고 가정합니다.
                    // 실제 사용 시 ID3D11Texture2D*와 같은 텍스처 자체의 포인터도 관리해야 할 수 있습니다.

                    // 리소스 해제 후 포인터를 nullptr로 설정합니다.
                    vThumbnail_Info->textureID = nullptr;
                }
            }
        });


    IGFD::FileDialogConfig config;
    config.countSelectionMax = 0;
    config.path = "../Bin/Resources/";
    m_pFDFM_OBJList.OpenDialog("ChooseFileDlgKey", "TextureFile", ".*,.jpg,.png,.dds", config);

    m_pFDFM_DatList.OpenDialog("ChooseDatDlgKey", "DatFile", ".dat", config);

    IGFD::FileDialogConfig DirectoryConfig;
    DirectoryConfig.countSelectionMax = 1;
    DirectoryConfig.path = "../Bin/Resources/";
    DirectoryConfig.flags = ImGuiFileDialogFlags_Modal | ImGuiFileDialogFlags_ConfirmOverwrite;


    m_pFDFM_DirectoryChooser.OpenDialog("ChooseDirectoryDlgKey", " Choose a File", ".dat", DirectoryConfig);
}

void CImgui_Manager::WindowTextureFileDialog()
{
    // GPU Rendering Zone // To call for Create/ Destroy Textures
    m_pFDFM_OBJList.ManageGPUThumbnails();

    if (m_pFDFM_OBJList.Display("ChooseFileDlgKey"))
    {
        if (m_pFDFM_OBJList.IsOk())
        {
            if (nullptr != m_pSelectObject)
            {
                std::string strFullfilePath = m_pFDFM_OBJList.GetFilePathName();
                wstring wstrFilePath = UTF8ToUTF16(strFullfilePath);

                CCustomize_UI* pCustomize_UI = nullptr;
                pCustomize_UI = m_pSelectCustom;

                _tchar      szDir[MAX_PATH] = TEXT("");
                _tchar      szFileName[MAX_PATH] = TEXT("");
                _tchar		szEXT[MAX_PATH] = TEXT("");
                _tchar      chBase[MAX_PATH] = TEXT("Bin");
                wstring     wstrTexturePath = { TEXT("../") };

                _wsplitpath_s(wstrFilePath.c_str(), nullptr, 0, szDir, MAX_PATH, szFileName, MAX_PATH, szEXT, MAX_PATH);

                wstring strDat = { TEXT(".dat") };
                wstring strEXT = { szEXT };

                if (strDat == strEXT)
                {
                    const wchar_t* foundPosition = wcsstr(szDir, chBase);
                    if (foundPosition != nullptr)
                    {
                        wstrTexturePath += foundPosition;
                        wstrTexturePath += szFileName;
                        wstrTexturePath += szEXT;
                    }
                }

                else
                {
                    const wchar_t* foundPosition = wcsstr(szDir, chBase);
                    if (foundPosition != nullptr)
                    {
                        wstrTexturePath += foundPosition;
                        wstrTexturePath += szFileName;
                        wstrTexturePath += szEXT;

                        wstring     wstrPrototype = { TEXT("Prototype_Component_Texture_") };
                        wstrPrototype += szFileName;

                        /* For.Prototype_Component_Texture_CardTexture */
                        if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, wstrPrototype, CTexture::Create(m_pDevice, m_pContext, wstrTexturePath)))) {

                        }
                           /* ShowFailMassageBox("텍스쳐 생성에 실패했습니다.");*/

                        pCustomize_UI->Change_Texture(wstrPrototype, wstrTexturePath);
                    }
                }
            }
        }

        m_bTextureFileDialogWindow = false;

        if (true == ImGui::IsAnyItemHovered() || true == ImGui::IsWindowHovered())
            m_IsMouseHover = true;
    }
}

void CImgui_Manager::WindowDatDialog()
{
    if (m_pFDFM_DatList.Display("ChooseDatDlgKey"))
    {
        if (m_pFDFM_DatList.IsOk())
        {
            auto selectedFiles = m_pFDFM_DatList.GetSelection();
            for (const auto& file : selectedFiles)
            {
                string strfileName = file.first;
                wstring strfilePath = UTF8ToUTF16(file.second);
                 
                m_mapDatFailes.emplace(strfileName, strfilePath);
            }
        }
        m_bDatDialogWindow = false;

        if (true == ImGui::IsAnyItemHovered() || true == ImGui::IsWindowHovered())
            m_IsMouseHover = true;
    }
}

void CImgui_Manager::WindowDirectoryDialog()
{
    if (m_pFDFM_DirectoryChooser.Display("ChooseDirectoryDlgKey"))
    {
        if (m_pFDFM_DirectoryChooser.IsOk())
        {
            if (nullptr != m_pSelectObject)
            {
                string  wstrFullPath = m_pFDFM_DirectoryChooser.GetFilePathName();

                ofstream outputFileStream;
                outputFileStream.open(wstrFullPath, ios::out | ios::binary);

                Save_UI(m_pSelectObject, outputFileStream);
            }
        }
        m_bDirectoryChooserWindow = false;

        if (true == ImGui::IsAnyItemHovered() || true == ImGui::IsWindowHovered())
            m_IsMouseHover = true;
    }
}

wstring CImgui_Manager::UTF8ToUTF16(const string& utf8Str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(utf8Str);
}

string CImgui_Manager::wstring_to_utf8(const std::wstring& wstr)
{
    if (wstr.empty())
        return std::string();

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);

    std::string strTo(size_needed, 0);

    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);

    return strTo;
}


void CImgui_Manager::Save_UI(CGameObject* SelectedObj, ofstream& outputFileStream, _bool isFirst)
{
    CCustomize_UI::CUSTOM_UI_DESC CutomizeUIDesc = {};

    CutomizeUIDesc = dynamic_cast<CCustomize_UI*>(SelectedObj)->Get_Cutomize_DESC();

    _char TextureName[MAX_PATH] = "";

    WideCharToMultiByte(CP_UTF8, 0, CutomizeUIDesc.strTextureName.c_str(), -1, TextureName, MAX_PATH, NULL, NULL);

    outputFileStream.write(reinterpret_cast<_char*>(TextureName), sizeof(_char) * MAX_PATH);

    outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.fWorldMatrix), sizeof(_float4x4));

    outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.vSize), sizeof(_float2));

    outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.iColorMaxNum), sizeof(_uint));

    for (_int i = 0; i <= (_int)CutomizeUIDesc.iColorMaxNum; i++)
    {
        outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.SavePos[i]), sizeof(_float4x4));

        outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.vColor[i]), sizeof(CCustomize_UI::Value_Color));
    }

    outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.isPlay), sizeof(_bool));

    outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.fColorTimer_Limit), sizeof(_float));

    outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.iEndingType), sizeof(_int));

    outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.iTextBoxCount), sizeof(_uint));

    for (_int i = 0; i < CutomizeUIDesc.iTextBoxCount; i++)
    {
        CTextBox::TextBox_DESC TextBoxDesc = CutomizeUIDesc.vecTextBoxDesc[i];
        
        _tchar FontString[MAX_PATH] = L"";
        _char FontType[MAX_PATH] = "";

        std::copy(TextBoxDesc.wstrText.begin(), TextBoxDesc.wstrText.end(), FontString);
        FontString[TextBoxDesc.wstrText.size()] = L'\0'; // 널 종단자를 명시적으로 추가

        WideCharToMultiByte(CP_UTF8, 0, TextBoxDesc.wstrFontType.c_str(), -1, FontType, MAX_PATH, NULL, NULL);

        outputFileStream.write(reinterpret_cast<_char*>(FontString), sizeof(_tchar) * MAX_PATH);

        outputFileStream.write(reinterpret_cast<_char*>(FontType), sizeof(_char) * MAX_PATH);

        outputFileStream.write(reinterpret_cast<_char*>(&TextBoxDesc.vFontColor), sizeof(_vector));

        outputFileStream.write(reinterpret_cast<_char*>(&TextBoxDesc.iFontSize), sizeof(_uint));

        outputFileStream.write(reinterpret_cast<_char*>(&TextBoxDesc.vPos), sizeof(_float3));

        outputFileStream.write(reinterpret_cast<_char*>(&TextBoxDesc.vSize), sizeof(_float2));

        outputFileStream.write(reinterpret_cast<_char*>(&TextBoxDesc.isOuterLine), sizeof(_bool));

        outputFileStream.write(reinterpret_cast<_char*>(&TextBoxDesc.vOutLineColor), sizeof(_vector));
    }

    outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.IsChild), sizeof(_bool));
    
    /*자식이 있으면 자식 정보 Write*/

    outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.iChild), sizeof(_int));

    if (true == 0 < CutomizeUIDesc.iChild)
    {
        vector<CGameObject*>* pvecGameObj = dynamic_cast<CCustomize_UI*>(SelectedObj)->Get_Child();
        
        for (auto& iter : *pvecGameObj)
        {
            Save_UI(iter, outputFileStream, false);
        }
    }

    if(true == isFirst)
    {
        outputFileStream.close();
    }

}

void CImgui_Manager::CreatFromDat(ifstream& inputFileStream, string strListName, CGameObject* pGameParentsObj)
{
    CCustomize_UI::CUSTOM_UI_DESC CustomizeUIDesc;

    _char TextureName[MAX_PATH] = "";

    inputFileStream.read(reinterpret_cast<_char*>(TextureName), sizeof(_char) * MAX_PATH);

    CustomizeUIDesc.strTextureName = wstring(TextureName, TextureName + strlen(TextureName));

    inputFileStream.read(reinterpret_cast<_char*>(&CustomizeUIDesc.fWorldMatrix), sizeof(_float4x4));

    inputFileStream.read(reinterpret_cast<_char*>(&CustomizeUIDesc.vSize), sizeof(_float2));

    inputFileStream.read(reinterpret_cast<_char*>(&CustomizeUIDesc.iColorMaxNum), sizeof(_uint));
    
    _int iColorMAxnum = CustomizeUIDesc.iColorMaxNum;

    for (_int i = 0; i <= iColorMAxnum; i++)
    {
        inputFileStream.read(reinterpret_cast<_char*>(&CustomizeUIDesc.SavePos[i]), sizeof(_float4x4));

        inputFileStream.read(reinterpret_cast<_char*>(&CustomizeUIDesc.vColor[i]), sizeof(CCustomize_UI::Value_Color));
    }

    inputFileStream.read(reinterpret_cast<_char*>(&CustomizeUIDesc.isPlay), sizeof(_bool));

    inputFileStream.read(reinterpret_cast<_char*>(&CustomizeUIDesc.fColorTimer_Limit), sizeof(_float));

    inputFileStream.read(reinterpret_cast<_char*>(&CustomizeUIDesc.iEndingType), sizeof(_int));

    inputFileStream.read(reinterpret_cast<_char*>(&CustomizeUIDesc.iTextBoxCount), sizeof(_uint));

    for (_int i = 0; i < CustomizeUIDesc.iTextBoxCount; i++)
    {
        CTextBox::TextBox_DESC TextBoxDesc = {};

        _tchar FontString[MAX_PATH] = L"";

        _char FontType[MAX_PATH] = "";

        inputFileStream.read(reinterpret_cast<_char*>(FontString), sizeof(_tchar) * MAX_PATH);

        inputFileStream.read(reinterpret_cast<_char*>(FontType), sizeof(_char) * MAX_PATH);

        TextBoxDesc.wstrText = FontString;

        TextBoxDesc.wstrFontType = wstring(FontType, FontType + strlen(FontType));

        inputFileStream.read(reinterpret_cast<_char*>(&TextBoxDesc.vFontColor), sizeof(_vector));

        inputFileStream.read(reinterpret_cast<_char*>(&TextBoxDesc.iFontSize), sizeof(_uint));

        inputFileStream.read(reinterpret_cast<_char*>(&TextBoxDesc.vPos), sizeof(_float3));

        inputFileStream.read(reinterpret_cast<_char*>(&TextBoxDesc.vSize), sizeof(_float2));

        inputFileStream.read(reinterpret_cast<_char*>(&TextBoxDesc.isOuterLine), sizeof(_bool));

        inputFileStream.read(reinterpret_cast<_char*>(&TextBoxDesc.vOutLineColor), sizeof(_vector));


        CustomizeUIDesc.vecTextBoxDesc.push_back(TextBoxDesc);
    }

    inputFileStream.read(reinterpret_cast<_char*>(&CustomizeUIDesc.IsChild), sizeof(_bool));
    
    std::string strFullfilePath;
    strFullfilePath.assign(CustomizeUIDesc.strTextureName.begin(), CustomizeUIDesc.strTextureName.end());

    wstring wstrFilePath = UTF8ToUTF16(strFullfilePath);

    _tchar      szDir[MAX_PATH] = TEXT("");
    _tchar      szFileName[MAX_PATH] = TEXT("");
    _tchar		szEXT[MAX_PATH] = TEXT("");
    _tchar      chBase[MAX_PATH] = TEXT("Bin");
    wstring     wstrTexturePath = { TEXT("../") };
    wstring     wstrFileName = TEXT("");

    _wsplitpath_s(wstrFilePath.c_str(), nullptr, 0, szDir, MAX_PATH, szFileName, MAX_PATH, szEXT, MAX_PATH);

    wstrFileName = szFileName;

    string filename;
    filename.assign(wstrFileName.begin(), wstrFileName.end());

    const wchar_t* foundPosition = wcsstr(szDir, chBase);

    if (foundPosition == nullptr)
        return;

    wstrTexturePath += foundPosition;
    wstrTexturePath += szFileName;
    wstrTexturePath += szEXT;

    wstring     wstrPrototype = { TEXT("Prototype_Component_Texture_") };
    wstrPrototype += szFileName;

    /* For.Prototype_Component_Texture_ */
    if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, wstrPrototype, CTexture::Create(m_pDevice, m_pContext, wstrTexturePath)))) {
        int a = 0;
    }
    //ShowMassageBox("텍스쳐 생성에 실패했습니다.");

    CustomizeUIDesc.strModelName = wstrPrototype;

    if (FAILED(m_pGameInstance->Add_Clone(LEVEL_GAMEPLAY, TEXT("Layer_UI"), TEXT("Prototype_GameObject_CCustomize_UI"), &CustomizeUIDesc)))
        MSG_BOX(TEXT("Failed to Add Clone"));

    CGameObject* pGameObj = m_pGameInstance->Get_LayerList(m_pGameInstance->Get_CurrentLevel(), TEXT("Layer_UI"))->back();

    if (false ==  CustomizeUIDesc.IsChild)
    {
        auto iter = m_mapGameObjects.find(filename);
        if (iter != m_mapGameObjects.end())
        {
            _bool IsSameName = true;
            _uint NameNum = 0;

            while (true == IsSameName)
            {
                string FileNameTrashCan = filename + to_string(NameNum);
                iter = m_mapGameObjects.find(FileNameTrashCan);
                if (iter == m_mapGameObjects.end())
                {
                    IsSameName = false;
                    filename = FileNameTrashCan;
                }
                NameNum++;
            }
        }
    }

    else
    {
        filename += ("_Child");
        auto iter = m_mapGameObjects.find(filename);
        if (iter != m_mapGameObjects.end())
        {
            _bool IsSameName = true;
            _uint NameNum = 0;

            while (true == IsSameName)
            {
                string FileNameTrashCan = filename + to_string(NameNum);
                iter = m_mapGameObjects.find(FileNameTrashCan);
                if (iter == m_mapGameObjects.end())
                {
                    IsSameName = false;
                    filename = FileNameTrashCan;
                }
                NameNum++;
            }
        }
    }

    m_mapGameObjects.emplace(filename, pGameObj);
    m_vecCutomizeUI.push_back(dynamic_cast<CCustomize_UI*>(pGameObj));

    if (nullptr != pGameParentsObj)
    {
        dynamic_cast<CCustomize_UI*>(pGameParentsObj)->PushBack_Child(pGameObj);
    }

    /*자식이 있으면 자식 정보 read*/

    inputFileStream.read(reinterpret_cast<_char*>(&CustomizeUIDesc.iChild), sizeof(_int));

    if (true == 0 < CustomizeUIDesc.iChild)
    {
        for (_int i = 0; i < CustomizeUIDesc.iChild; i++)
        {
            CreatFromDat(inputFileStream, filename, pGameObj);
        }
    }

    if (nullptr == pGameParentsObj)
    {
        inputFileStream.close();
    }
    
}

void CImgui_Manager::Save_Scene(string strFileName)
{
    for (auto& pair : m_mapGameObjects)
    {
        _char			szDrive[MAX_PATH] = { "../Bin/Resources/UI_Data/" };
        _char			szFloder[MAX_PATH] = { "" };
        _char			szDataFileName[MAX_PATH] = { "" };
        _char			szEXT[MAX_PATH] = { ".dat" };

        _char			szFullPath[MAX_PATH] = { "" };

        _tchar			szPerfectPath[MAX_PATH] = { L"" };

        WideCharToMultiByte(CP_UTF8, 0, m_wstrLevel.c_str(), -1, szFloder, MAX_PATH, NULL, NULL);
        //WideCharToMultiByte(CP_UTF8, 0, pair.first.c_str(), -1, szDataFileName, MAX_PATH, NULL, NULL);
        strcpy_s(szDataFileName, pair.first.c_str());

        strcat_s(szFullPath, szDrive);
        strcat_s(szFullPath, szFloder);
        strcat_s(szFullPath, szDataFileName);
        strcat_s(szFullPath, szEXT);

        MultiByteToWideChar(CP_ACP, 0, szFullPath, (_int)strlen(szFullPath), szPerfectPath, MAX_PATH);

        ofstream outputFileStream;
        outputFileStream.open(szPerfectPath, ios::out | ios::binary);

        CCustomize_UI::CUSTOM_UI_DESC CutomizeUIDesc = {};

        CGameObject* pCutomizeUI = (pair.second);

        CutomizeUIDesc = dynamic_cast<CCustomize_UI*>(pCutomizeUI)->Get_Cutomize_DESC();

        _char TextureName[MAX_PATH] = "";
        WideCharToMultiByte(CP_UTF8, 0, CutomizeUIDesc.strTextureName.c_str(), -1, TextureName, MAX_PATH, NULL, NULL);

        outputFileStream.write(reinterpret_cast<_char*>(TextureName), sizeof(_char) * MAX_PATH);

        outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.fWorldMatrix), sizeof(_float4x4));

        outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.iColorMaxNum), sizeof(_uint));

        for (_int i = 0; i < (_int)CutomizeUIDesc.iColorMaxNum + 1; i++)
        {
            outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.vColor[i]), sizeof(CCustomize_UI::Value_Color));
            outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.SavePos[i]), sizeof(_float4x4));
        }

        outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.isPlay), sizeof(_bool));
        outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.fColorTimer_Limit), sizeof(_float));
        outputFileStream.write(reinterpret_cast<_char*>(&CutomizeUIDesc.iEndingType), sizeof(_int));

        outputFileStream.close();
    }
}

void CImgui_Manager::DrawFullScreenGrid(_float gridSize)
{
    ImVec2 screenSize = ImGui::GetIO().DisplaySize; // 화면 크기 얻기
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();

    ImU32 gridColor = IM_COL32(68, 37, 117, 255);
    _float lineThickness = 1.0f;

    /* Mouse */
    POINT mouse;
    GetCursorPos(&mouse);
    ScreenToClient(g_hWnd, &mouse);

    RECT rect;
    GetClientRect(g_hWnd, &rect);
    _float WinSizeX = (_float)rect.right;
    _float WinSizeY = (_float)rect.bottom;

    m_isMouseX = false;
    m_isMouseY = false;

    // 수직 선 
    for (_float x = fmodf(gridSize, screenSize.x); x < screenSize.x; x += gridSize)
    {
        // 현재 그리드 선에서 마우스 위치까지의 거리 계산
        _float distanceToGridLine = abs(mouse.x - x);

        // 마우스 위치가 그리드 선에 가까운지 확인 (±10 픽셀 범위)
        if (distanceToGridLine <= 10 && distanceToGridLine >= -10)
        {
            m_isMouseX = true;
            m_vMousePos.x = x; // 마우스 위치를 그리드 선에 맞춤
            m_vMousePos.x -= (WinSizeX * 0.5f);

        }

        drawList->AddLine(ImVec2(x, 0), ImVec2(x, screenSize.y), gridColor, lineThickness);
    }

    /* 그림 */
    if (m_isMouseX)
    {
        _float fReadX = m_vMousePos.x + (WinSizeX * 0.5f);
        drawList->AddLine(ImVec2(fReadX, 0), ImVec2(fReadX, screenSize.y), IM_COL32(242, 129, 229, 255), lineThickness);
    }


    // 수평 선 
    for (_float y = fmodf(gridSize, screenSize.y); y < screenSize.y; y += gridSize)
    {
        // 현재 그리드 선에서 마우스 위치까지의 거리 계산
        _float distanceToGridLine = abs(mouse.y - y);

        // 마우스 위치가 그리드 선에 가까운지 확인 (±10 픽셀 범위)
        if (distanceToGridLine <= 10 && distanceToGridLine >= -10)
        {
            m_isMouseY = true;
            m_vMousePos.y = -y; // 마우스 위치를 그리드 선에 맞춤
            m_vMousePos.y += (WinSizeY * 0.5f);
        }
        drawList->AddLine(ImVec2(0, y), ImVec2(screenSize.x, y), gridColor, lineThickness);
    }

    /* 그림 */
    if (m_isMouseY)
    {
        _float fReadY = m_vMousePos.y - (WinSizeY * 0.5f);
        drawList->AddLine(ImVec2(0, fReadY), ImVec2(screenSize.x, fReadY), IM_COL32(242, 129, 229, 255), lineThickness);
    }
}

void CImgui_Manager::ShowMassageBox(string strMassage, bool* IsOpen, bool* bNeverSayAgain)
{
    if (true == *bNeverSayAgain)
        return;

    ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);
    if (ImGui::BeginPopupModal("Masage Box", IsOpen, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Masage Box");
        ImGui::Separator();

        // 메시지 내용
        ImGui::Text(strMassage.c_str());

        // 닫기 버튼
        if (ImGui::Button("Close", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
            *IsOpen = false;
        }

        // 닫기 버튼
        if (ImGui::Button("Naver Say Again!", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
            *IsOpen = false;
            *bNeverSayAgain = true;
        }

        ImGui::EndPopup();
    }
}

_bool CImgui_Manager::IsCanClick() const
{
    if (true == m_bTextureFileDialogWindow)
        return false;

    else if (true == m_bDatDialogWindow)
        return false;

    else if (true == m_bDirectoryChooserWindow)
        return false;

    else if (true == m_IsMouseHover)
        return false;

    return true;
}

void CImgui_Manager::ReleaseClick()
{
    if (nullptr == m_pSelectCustom)
        return;

    m_pGizmoTransform = nullptr;
    m_isUse_UIGizmo = false;
    m_mapTextBoxes.clear();
    Reset_ShaderValue();
    m_iUI_Selected = -1;
    m_strSelectedTextBox = TEXT("");

    m_pSelectCustom->Follow_Edge(false);
    Set_MapTextBox(m_pSelectCustom);
    for (auto& iter : *(m_pSelectCustom->Get_EdgeVec()))
        dynamic_cast<CEdge_UI*>(iter)->Follow_Rect(true);

    m_pSelectCustom = nullptr;
    m_pSelectObject = nullptr;
}

void CImgui_Manager::Reset_ShaderValue()
{
    m_isColorChange = false;
    m_isAlpaChange = false;
    m_isWave = false;
    m_isPush = false;
    m_isPlayControl = false;
    m_fWaveSpeed = 0.f;
    m_fPushX_Speed = 0.f;
    m_fPushY_Speed = 0.f;
    m_fUVSplit = 1.f;
    m_fUVRotation = 0.f;
}

void CImgui_Manager::Set_ShaderValue(CGameObject* pGameObject)
{
    if (nullptr == pGameObject)
        return;

    CCustomize_UI::CUSTOM_UI_DESC CutomizeUIDesc = dynamic_cast<CCustomize_UI*>(pGameObject)->Get_Cutomize_DESC();
    
    if (true == CutomizeUIDesc.iColorMaxNum < 1)
    {

    }
    



}

void CImgui_Manager::Set_MapTextBox(CCustomize_UI* pSelectCustomize)
{
    if (nullptr == pSelectCustomize)
        return;

    vector<CTextBox*>* vecTextBox = pSelectCustomize->Get_vecTextBoxes();

    for (auto& iter : *vecTextBox)
    {
        wstring wstrTag = iter->Get_Text();
        m_mapTextBoxes.emplace(wstrTag, iter);
    }
}

CGameObject* CImgui_Manager::Find_GameObject(string strTag)
{
    if (m_mapGameObjects.empty())
        return nullptr;

    auto	iter = m_mapGameObjects.find(strTag);
    if (iter == m_mapGameObjects.end())
        return nullptr;

    return iter->second;
}

string CImgui_Manager::Find_ObjTag(CGameObject* pGameObject)
{
    if (nullptr == pGameObject)
        return string();

    _int iFound = 0;

    for (const auto& pair : m_mapGameObjects) {
        if (pair.second == pGameObject)
        {
            m_iUI_Selected = iFound;
            return pair.first;
        }
        iFound++;
    }

    return string();
}

void CImgui_Manager::Delete_GameObject(string strTag)
{
    if (m_mapGameObjects.empty())
        return;

    auto	iter = m_mapGameObjects.find(strTag);
    if (iter == m_mapGameObjects.end())
        return;

    CGameObject* pDelete = iter->second;

    for (auto& pair : m_mapGameObjects)
    {
        if (true == dynamic_cast<CCustomize_UI*>(pair.second)->IsMyChild(pDelete))
        {
            dynamic_cast<CCustomize_UI*>(pair.second)->Release_Child(pDelete);
        }
    }

    auto iterCustom = find(m_vecCutomizeUI.begin(), m_vecCutomizeUI.end(), pDelete);

    if (iterCustom != m_vecCutomizeUI.end())
    {
        m_vecCutomizeUI.erase(iterCustom);
    }
    
    dynamic_cast<CCustomize_UI*>(pDelete)->Release_Children();

    m_pGameInstance->Delete_Object(m_pGameInstance->Get_CurrentLevel(), TEXT("Layer_UI"), pDelete);

    m_mapGameObjects.erase(iter);

    m_isUse_UIGizmo = false;
    m_pGizmoTransform = nullptr;
    m_pSelectObject = NULL;
}

CTextBox* CImgui_Manager::Find_TextBox(wstring wstrTag)
{
    if (m_mapTextBoxes.empty())
        return nullptr;

    auto	iter = m_mapTextBoxes.find(wstrTag);
    if (iter == m_mapTextBoxes.end())
        return nullptr;

    return iter->second;
}

void CImgui_Manager::Free()
{
    Safe_Release(m_pDevice);
    Safe_Release(m_pContext);
    Safe_Release(m_pGameInstance);


    //for (auto& Pair : m_mapGameObjects)
    //    Safe_Release(Pair.second);
    //m_mapGameObjects.clear();


    //Safe_Release(m_pGizmoTransform);
    Safe_Release(m_pCameraFree);

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    __super::Free();
}