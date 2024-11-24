#pragma once

#include "Client_Defines.h"
#include "Base.h"
#include "ImGuizmo.h"
#include "Camera_Free.h"
#include "ImGuiFileDialog.h"

BEGIN(Client)

class CImgui_Manager  final : public CBase
{
	DECLARE_SINGLETON(CImgui_Manager)

public:
	enum EDIT_STATE {STATE_NUN, STATE_EDIT, STATE_CREATE, STATE_END };
	enum EDIT_ID { UI_POINT, UI_RECT, _END };
	enum MyItemColumnID
	{
		MyItemColumnID_ID,
		MyItemColumnID_Name,
		MyItemColumnID_Action,
		MyItemColumnID_Quantity,
		MyItemColumnID_Description
	};

	enum Mode
	{
		Mode_Copy,
		Mode_Move,
		Mode_Swap
	};

public:
	CImgui_Manager();
	virtual ~CImgui_Manager() = default;
	void Set_GraphicDevice(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

public:
	HRESULT			Initialize();
	void			ResetVariable();
	void			Tick();
	void			ObjectPicking();
	void			Render();


public:// for.GIZMO
	void			EditTransform(class CTransform* pTransformCom);
	void			UI_Gizmo(_float4x4& matrix);
	void			Gizmo(CTransform* pTransform);
	void			Set_isUsingGizmo(_bool _isUsingGizmo) { m_isUsingGizmo = _isUsingGizmo; }
	_bool			Get_isUsingGizmo() const { return m_isUsingGizmo; }

private:
	HRESULT			Tab_Create_UI(ImVec4& ref_color_v);
	HRESULT			ShaderEditor(ImVec4& ref_color_v);
	HRESULT			Status_Box();
	HRESULT			TextBoxEditor();
	HRESULT			UI_ListEditor();
	HRESULT			DAT_ListEditor();
	HRESULT			FontColor_Editor();

	HRESULT			CreateChild();
	HRESULT			CreateCanvas(string strDatFileName);

private://for.FileDialog
	void			InitFileDialog();
	void			WindowTextureFileDialog();
	void			WindowDatDialog();
	void			WindowDirectoryDialog();

private:
	wstring			UTF8ToUTF16(const string& utf8Str);
	string			wstring_to_utf8(const std::wstring& wstr);


private:
	void			Save_UI(CGameObject* SelectedObj, ofstream& outputFileStream, _bool isFirst = true);
	void			Save_Scene(string strFileName);
	void			CreatFromDat(ifstream& inputFileStream, string strListName, CGameObject* pGameParentsObj);

public:
	void			DrawFullScreenGrid(_float gridSize);

private:
	void			ShowMassageBox(string strMassage, bool* IsOpen, bool* bNeverSayAgain);
	_bool			IsCanClick() const;
	void			ReleaseClick();

private:
	void			Reset_ShaderValue();
	void			Set_ShaderValue(CGameObject* pGameObject);
	void			Set_MapTextBox(class CCustomize_UI* pSelectCustomize);

private: 
	CGameObject*	Find_GameObject(string strTag); // Find Object
	string			Find_ObjTag(CGameObject* pGameObject);
	void			Delete_GameObject(string strTag);

private:
	class CTextBox*		Find_TextBox(wstring wstrTag);



private: //for.IMGUI
	ImGuiIO								m_ImGuiIO;
	ID3D11Device*						m_pDevice		= { nullptr };
	ID3D11DeviceContext*				m_pContext		= { nullptr };
	ImVec4								clear_color		= ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	CGameInstance*						m_pGameInstance = { nullptr };

private: // for.Camera
	CCamera_Free*						m_pCameraFree	= { nullptr };
	_float								m_fCameraSpeed	= { 10.f };

private: // for.Window
	_bool								m_bToolWindow				= { true };
	_bool								m_bGIZMOWindow				= { true };
	_bool								m_bPosAplly					= { false };
	_bool								m_bTextureFileDialogWindow	= { false };
	_bool								m_bDatDialogWindow			= { false };
	_bool								m_bDirectoryChooserWindow	= { false };
	_bool								m_IsMouseHover				= { false };

	EDIT_STATE							m_eEditState = { STATE_NUN };


private: //for.GIZMO
	ImGuizmo::OPERATION					m_eGizmoState		= { ImGuizmo::ROTATE };
	CGameObject*						m_pGameObject		= { nullptr };
	CTransform*							m_pGizmoTransform	= { nullptr };
	class CCustomize_UI*				m_pSelectCustom		= { nullptr };
	class CCustomize_UI*				m_pPrevCustom		= { nullptr };
	
	_bool								m_isUsingGizmo		= { false };
	_bool								m_isUse_UIGizmo		= { false };

#pragma region 기능
private : 
	EDIT_ID								m_eEdit_UIID		= { };
	EDIT_ID								m_eEditPrev_UIID	= { };
	UI_ID								m_eUI_ID			= { UI_ID::UI_END };

private : 
	CGameObject*						m_pSelectObject = { nullptr };

private : /* for.Function */
	_bool								m_isLook_StoreState = { false };
	_bool								m_isColorChange		= { false };
	_bool								m_isAlpaChange		= { false };
	_bool								m_isWave			= { false };
	_bool								m_isPush			= { false };
	_bool								m_isPlayControl		= { false };  /* 배열 안에 들어간 상태 Play하는 동안 Edit 상태는 중단시키기 */
	
	_float								m_fWaveSpeed		= { };
	_float								m_fPushX_Speed		= {};
	_float								m_fPushY_Speed		= {};
	_float								m_fUVSplit			= { 1.f };
	_float								m_fUVRotation		= { 0.f };

private:
	_matrix								m_SelectedTransformMatrix = {};

private:
	POINT								m_ptMouse = {};
	ImVec4								m_fCamPos = {};

	_int								m_iLevel = { -1 };
	wstring								m_wstrLevel = { L"" };
	
private: /* for.ObjectList */
	ImGuiFileDialog						m_pFDFM_OBJList;
	map<string, CGameObject*>			m_mapGameObjects;
	vector<class CCustomize_UI*>		m_vecCutomizeUI;
	string								m_strSelected_UI_inList = { "" };
	_int								m_iUI_Selected = -1;

private: // for.DatFileList
	ImGuiFileDialog						m_pFDFM_DatList;
	map<string, wstring>				m_mapDatFailes;
	string								strSelected_Data_inList		= { "" };
	_int								m_iSelectNumInDatList		= { -1 };

private: // for.TextBox
	_int								m_iSelectedNumInTextBox		= { -1 };
	map<wstring, class CTextBox*>		m_mapTextBoxes;
	wstring								m_strSelectedTextBox = {TEXT("")};


private: // for.Dialog
	ImGuiFileDialog						m_pFDFM_DirectoryChooser;

private: // for. Grid Select
	_bool								m_isMouseX		= { false };
	_bool								m_isMouseY		= { false };
	_bool								m_isGridGizmo	= { false };
	_float2								m_vMousePos		= { 0, 0 };

#pragma endregion

private: 
	virtual void Free() override;
};

END