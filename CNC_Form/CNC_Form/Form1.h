#pragma once
//#include "stdafx.h"
//#include "stdio.h"
//#include "string.h"
#include "io.h"
#include "vcclr.h"
#include "stdlib.h"
#include "..\..\DEF\cpSwitch.h"
#include "..\..\DRV\INC\DRV.h"
#include "..\..\MMI\INC\MMI.h"
#include "..\..\SYS_LINK\INC\sysLink.h"
#include "..\..\SYS\INC\sys.h"
#include "..\..\INTP\INC\intp.h"
#include "..\..\DEC\INC\dec.h"

/*****************************************************************************************************
typedef struct
{
	double	mSetValue;			// setting value in mm	(or degree)
	double	mActValue;			// actual value in mm	(or degree)
	double	resolution;			// resolution, mm/inc	(or degree/inc)
	int		relInc;				// (set - oldSet) / resolution

} AXIS_DATA;

AXIS_DATA	axisData[3];
int			xyzButton[3];	//  1 : + mouse down
							// -1 : - mouse down
							//  0 : mouse up

double axisInitValue[3] = {0, 0, 100.0};

int realKnl(void)
{
	//******************************************
	// position control
	//******************************************
	int i;
	for( i = 0 ; i<3 ; ++i)
	{
		// relInc = (set - oldSet) / resolution
		double relDistance = axisData[i].mSetValue - axisData[i].mActValue;

		if (relDistance != 0)
		{
		   axisData[i].relInc = (int)(relDistance / axisData[i].resolution);		

		// Safty Check
		   if (axisData[i].relInc < -200)
		  	  axisData[i].relInc = -200;
		   else if (axisData[i].relInc > 200)
			  axisData[i].relInc = 200;
		}
		else axisData[i].relInc = 0;

	}

	// output
	for (i = 0 ; i < 3 ; ++i)
	{
		//putAxisValue(i, axisData[i].relInc);
		axisData[i].mActValue += axisData[i].relInc * axisData[i].resolution;
        axisData[i].mSetValue = axisData[i].mActValue;

	}
	return 0;
}
*/

SYS_LINK_DATA	sysLinkData;
SYS_LINK_DATA	*sysLinkDataPtr;
SYS_DATA		sysData;
SYS_DATA		*sysDataPtr;
DEC_DATA		decData;
DEC_DATA		*decDataPtr;
INTP_DATA		intpData;
INTP_DATA		*intpDataPtr;
MMI_DATA		mmiData;
MMI_DATA		*mmiDataPtr;

//**********************************************
// Real timer function
//**********************************************
#if HD_TIMER
void _stdcall Timer_ISR_Function(LIOINT *pstINTSource)
{
	realKnl();
}
#endif

namespace CNC_Form {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 的摘要
	///
	/// 警告: 如果您變更這個類別的名稱，就必須變更與這個類別所依據之所有 .resx 檔案關聯的
	///          Managed 資源編譯器工具的 'Resource File Name' 屬性。
	///          否則，這些設計工具
	///          將無法與這個表單關聯的當地語系化資源
	///          正確互動。
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Label^  label_m00;
	private: System::Windows::Forms::Label^  label_pgm;
	private: System::Windows::Forms::Label^  label_counter;

	protected: 



	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label_hX;
	private: System::Windows::Forms::Label^  label_hY;
	private: System::Windows::Forms::Label^  label_hZ;
	private: System::Windows::Forms::Label^  label_pX;
	private: System::Windows::Forms::Label^  label_pY;
	private: System::Windows::Forms::Label^  label_pZ;






	private: System::Windows::Forms::Label^  label_m30;
	private: System::Windows::Forms::Label^  label_err;



	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label_inX;
	private: System::Windows::Forms::Label^  label_inY;
	private: System::Windows::Forms::Label^  label_inZ;
	private: System::Windows::Forms::Label^  label_nX;
	private: System::Windows::Forms::Label^  label_nY;
	private: System::Windows::Forms::Label^  label_nZ;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::RichTextBox^  richTextBox_ncFile;
	private: System::Windows::Forms::TextBox^  textBox_ncPath;


	private: System::Windows::Forms::Button^  button_file;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label_targetX;
	private: System::Windows::Forms::Label^  label_targetZ;


	private: System::Windows::Forms::Label^  label_targetY;
	private: System::Windows::Forms::Label^  label_realZ;


	private: System::Windows::Forms::Label^  label_realY;

	private: System::Windows::Forms::Label^  label_realX;


	private: System::Windows::Forms::Button^  button_record;

	private: System::Windows::Forms::Button^  button_teachIn;
	private: System::Windows::Forms::Button^  button_zMin;


	private: System::Windows::Forms::Button^  button_zPlus;
	private: System::Windows::Forms::Button^  button_yMin;


	private: System::Windows::Forms::Button^  button_yPlus;
	private: System::Windows::Forms::Button^  button_xMin;


	private: System::Windows::Forms::Button^  button_xPlus;
private: System::Windows::Forms::Button^  button_bkl;


private: System::Windows::Forms::Button^  button_x1;
private: System::Windows::Forms::Button^  button_x100;
private: System::Windows::Forms::Button^  button_coordiChange;

private: System::Windows::Forms::Button^  button_fh;




private: System::Windows::Forms::Button^  button_x10;
private: System::Windows::Forms::Label^  label_overridePercent;


	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TrackBar^  trackBar_override;
private: System::Windows::Forms::Button^  button_cycleStart;

private: System::Windows::Forms::Button^  button_reset;

private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
private: System::Windows::Forms::Button^  button_mem;

private: System::Windows::Forms::Button^  button_mdi;

private: System::Windows::Forms::Button^  button_jog;

private: System::Windows::Forms::Button^  button_home;

private: System::Windows::Forms::Button^  button_wheel;



private: System::Windows::Forms::Button^  button_emergencyStop;
private: System::Windows::Forms::OpenFileDialog^  openFileDialog_openNc;
private: System::Windows::Forms::Timer^  timer_real;


private: System::Windows::Forms::Timer^  timer_nonreal;
private: System::Windows::Forms::Button^  button_teachEnd;
private: System::Windows::Forms::SaveFileDialog^  saveFileDialog_saveNc;
private: System::Windows::Forms::PictureBox^  pictureBox1;

private: System::ComponentModel::IContainer^  components;










	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改這個方法的內容。
		///
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label_m00 = (gcnew System::Windows::Forms::Label());
			this->label_pgm = (gcnew System::Windows::Forms::Label());
			this->label_counter = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label_hX = (gcnew System::Windows::Forms::Label());
			this->label_hY = (gcnew System::Windows::Forms::Label());
			this->label_hZ = (gcnew System::Windows::Forms::Label());
			this->label_pX = (gcnew System::Windows::Forms::Label());
			this->label_pY = (gcnew System::Windows::Forms::Label());
			this->label_pZ = (gcnew System::Windows::Forms::Label());
			this->label_m30 = (gcnew System::Windows::Forms::Label());
			this->label_err = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label_inX = (gcnew System::Windows::Forms::Label());
			this->label_inY = (gcnew System::Windows::Forms::Label());
			this->label_inZ = (gcnew System::Windows::Forms::Label());
			this->label_nX = (gcnew System::Windows::Forms::Label());
			this->label_nY = (gcnew System::Windows::Forms::Label());
			this->label_nZ = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label_targetZ = (gcnew System::Windows::Forms::Label());
			this->label_targetY = (gcnew System::Windows::Forms::Label());
			this->label_targetX = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label_realZ = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label_realY = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label_realX = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->button_teachEnd = (gcnew System::Windows::Forms::Button());
			this->button_record = (gcnew System::Windows::Forms::Button());
			this->button_teachIn = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->button_zMin = (gcnew System::Windows::Forms::Button());
			this->button_zPlus = (gcnew System::Windows::Forms::Button());
			this->button_yMin = (gcnew System::Windows::Forms::Button());
			this->button_yPlus = (gcnew System::Windows::Forms::Button());
			this->button_xMin = (gcnew System::Windows::Forms::Button());
			this->button_xPlus = (gcnew System::Windows::Forms::Button());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->button_bkl = (gcnew System::Windows::Forms::Button());
			this->button_x1 = (gcnew System::Windows::Forms::Button());
			this->button_x100 = (gcnew System::Windows::Forms::Button());
			this->button_coordiChange = (gcnew System::Windows::Forms::Button());
			this->button_fh = (gcnew System::Windows::Forms::Button());
			this->button_x10 = (gcnew System::Windows::Forms::Button());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->button_cycleStart = (gcnew System::Windows::Forms::Button());
			this->button_reset = (gcnew System::Windows::Forms::Button());
			this->trackBar_override = (gcnew System::Windows::Forms::TrackBar());
			this->label_overridePercent = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->richTextBox_ncFile = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox_ncPath = (gcnew System::Windows::Forms::TextBox());
			this->button_file = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button_mem = (gcnew System::Windows::Forms::Button());
			this->button_mdi = (gcnew System::Windows::Forms::Button());
			this->button_jog = (gcnew System::Windows::Forms::Button());
			this->button_home = (gcnew System::Windows::Forms::Button());
			this->button_wheel = (gcnew System::Windows::Forms::Button());
			this->button_emergencyStop = (gcnew System::Windows::Forms::Button());
			this->openFileDialog_openNc = (gcnew System::Windows::Forms::OpenFileDialog());
			this->timer_real = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer_nonreal = (gcnew System::Windows::Forms::Timer(this->components));
			this->saveFileDialog_saveNc = (gcnew System::Windows::Forms::SaveFileDialog());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->tableLayoutPanel1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_override))->BeginInit();
			this->tableLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 11;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.090909F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.090909F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.090909F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.090909F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.090909F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.090909F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.090909F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.090909F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.090909F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.090909F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.090909F)));
			this->tableLayoutPanel1->Controls->Add(this->label_m00, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->label_pgm, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->label_counter, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->label4, 3, 0);
			this->tableLayoutPanel1->Controls->Add(this->label5, 4, 0);
			this->tableLayoutPanel1->Controls->Add(this->label_hX, 5, 0);
			this->tableLayoutPanel1->Controls->Add(this->label_hY, 6, 0);
			this->tableLayoutPanel1->Controls->Add(this->label_hZ, 7, 0);
			this->tableLayoutPanel1->Controls->Add(this->label_pX, 8, 0);
			this->tableLayoutPanel1->Controls->Add(this->label_pY, 9, 0);
			this->tableLayoutPanel1->Controls->Add(this->label_pZ, 10, 0);
			this->tableLayoutPanel1->Controls->Add(this->label_m30, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->label_err, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->label14, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->label15, 3, 1);
			this->tableLayoutPanel1->Controls->Add(this->label16, 4, 1);
			this->tableLayoutPanel1->Controls->Add(this->label_inX, 5, 1);
			this->tableLayoutPanel1->Controls->Add(this->label_inY, 6, 1);
			this->tableLayoutPanel1->Controls->Add(this->label_inZ, 7, 1);
			this->tableLayoutPanel1->Controls->Add(this->label_nX, 8, 1);
			this->tableLayoutPanel1->Controls->Add(this->label_nY, 9, 1);
			this->tableLayoutPanel1->Controls->Add(this->label_nZ, 10, 1);
			this->tableLayoutPanel1->Location = System::Drawing::Point(136, 12);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(642, 85);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// label_m00
			// 
			this->label_m00->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_m00->AutoSize = true;
			this->label_m00->BackColor = System::Drawing::Color::Teal;
			this->label_m00->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_m00->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_m00->Location = System::Drawing::Point(0, 0);
			this->label_m00->Margin = System::Windows::Forms::Padding(0);
			this->label_m00->Name = L"label_m00";
			this->label_m00->Size = System::Drawing::Size(58, 42);
			this->label_m00->TabIndex = 0;
			this->label_m00->Text = L"M00";
			this->label_m00->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_pgm
			// 
			this->label_pgm->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_pgm->AutoSize = true;
			this->label_pgm->BackColor = System::Drawing::Color::Teal;
			this->label_pgm->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_pgm->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_pgm->Location = System::Drawing::Point(58, 0);
			this->label_pgm->Margin = System::Windows::Forms::Padding(0);
			this->label_pgm->Name = L"label_pgm";
			this->label_pgm->Size = System::Drawing::Size(58, 42);
			this->label_pgm->TabIndex = 0;
			this->label_pgm->Text = L"PGM";
			this->label_pgm->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_counter
			// 
			this->label_counter->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_counter->AutoSize = true;
			this->label_counter->BackColor = System::Drawing::Color::Teal;
			this->label_counter->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_counter->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_counter->Location = System::Drawing::Point(116, 0);
			this->label_counter->Margin = System::Windows::Forms::Padding(0);
			this->label_counter->Name = L"label_counter";
			this->label_counter->Size = System::Drawing::Size(58, 42);
			this->label_counter->TabIndex = 0;
			this->label_counter->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Teal;
			this->label4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label4->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label4->Location = System::Drawing::Point(174, 0);
			this->label4->Margin = System::Windows::Forms::Padding(0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(58, 42);
			this->label4->TabIndex = 0;
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Teal;
			this->label5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label5->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label5->Location = System::Drawing::Point(232, 0);
			this->label5->Margin = System::Windows::Forms::Padding(0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(58, 42);
			this->label5->TabIndex = 0;
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_hX
			// 
			this->label_hX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_hX->AutoSize = true;
			this->label_hX->BackColor = System::Drawing::Color::Teal;
			this->label_hX->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_hX->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_hX->Location = System::Drawing::Point(290, 0);
			this->label_hX->Margin = System::Windows::Forms::Padding(0);
			this->label_hX->Name = L"label_hX";
			this->label_hX->Size = System::Drawing::Size(58, 42);
			this->label_hX->TabIndex = 0;
			this->label_hX->Text = L"HX";
			this->label_hX->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_hY
			// 
			this->label_hY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_hY->AutoSize = true;
			this->label_hY->BackColor = System::Drawing::Color::Teal;
			this->label_hY->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_hY->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_hY->Location = System::Drawing::Point(348, 0);
			this->label_hY->Margin = System::Windows::Forms::Padding(0);
			this->label_hY->Name = L"label_hY";
			this->label_hY->Size = System::Drawing::Size(58, 42);
			this->label_hY->TabIndex = 0;
			this->label_hY->Text = L"HY";
			this->label_hY->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_hZ
			// 
			this->label_hZ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_hZ->AutoSize = true;
			this->label_hZ->BackColor = System::Drawing::Color::Teal;
			this->label_hZ->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_hZ->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_hZ->Location = System::Drawing::Point(406, 0);
			this->label_hZ->Margin = System::Windows::Forms::Padding(0);
			this->label_hZ->Name = L"label_hZ";
			this->label_hZ->Size = System::Drawing::Size(58, 42);
			this->label_hZ->TabIndex = 0;
			this->label_hZ->Text = L"HZ";
			this->label_hZ->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_pX
			// 
			this->label_pX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_pX->AutoSize = true;
			this->label_pX->BackColor = System::Drawing::Color::Teal;
			this->label_pX->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_pX->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_pX->Location = System::Drawing::Point(464, 0);
			this->label_pX->Margin = System::Windows::Forms::Padding(0);
			this->label_pX->Name = L"label_pX";
			this->label_pX->Size = System::Drawing::Size(58, 42);
			this->label_pX->TabIndex = 0;
			this->label_pX->Text = L"PX";
			this->label_pX->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_pY
			// 
			this->label_pY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_pY->AutoSize = true;
			this->label_pY->BackColor = System::Drawing::Color::Teal;
			this->label_pY->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_pY->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_pY->Location = System::Drawing::Point(522, 0);
			this->label_pY->Margin = System::Windows::Forms::Padding(0);
			this->label_pY->Name = L"label_pY";
			this->label_pY->Size = System::Drawing::Size(58, 42);
			this->label_pY->TabIndex = 0;
			this->label_pY->Text = L"PY";
			this->label_pY->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_pZ
			// 
			this->label_pZ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_pZ->AutoSize = true;
			this->label_pZ->BackColor = System::Drawing::Color::Teal;
			this->label_pZ->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_pZ->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_pZ->Location = System::Drawing::Point(580, 0);
			this->label_pZ->Margin = System::Windows::Forms::Padding(0);
			this->label_pZ->Name = L"label_pZ";
			this->label_pZ->Size = System::Drawing::Size(62, 42);
			this->label_pZ->TabIndex = 0;
			this->label_pZ->Text = L"PZ";
			this->label_pZ->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_m30
			// 
			this->label_m30->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_m30->AutoSize = true;
			this->label_m30->BackColor = System::Drawing::Color::Teal;
			this->label_m30->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_m30->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_m30->Location = System::Drawing::Point(0, 42);
			this->label_m30->Margin = System::Windows::Forms::Padding(0);
			this->label_m30->Name = L"label_m30";
			this->label_m30->Size = System::Drawing::Size(58, 43);
			this->label_m30->TabIndex = 0;
			this->label_m30->Text = L"M30";
			this->label_m30->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_err
			// 
			this->label_err->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_err->AutoSize = true;
			this->label_err->BackColor = System::Drawing::Color::Teal;
			this->label_err->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_err->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_err->Location = System::Drawing::Point(58, 42);
			this->label_err->Margin = System::Windows::Forms::Padding(0);
			this->label_err->Name = L"label_err";
			this->label_err->Size = System::Drawing::Size(58, 43);
			this->label_err->TabIndex = 0;
			this->label_err->Text = L"ERR";
			this->label_err->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label14
			// 
			this->label14->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label14->AutoSize = true;
			this->label14->BackColor = System::Drawing::Color::Teal;
			this->label14->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label14->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label14->Location = System::Drawing::Point(116, 42);
			this->label14->Margin = System::Windows::Forms::Padding(0);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(58, 43);
			this->label14->TabIndex = 0;
			this->label14->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label15
			// 
			this->label15->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label15->AutoSize = true;
			this->label15->BackColor = System::Drawing::Color::Teal;
			this->label15->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label15->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label15->Location = System::Drawing::Point(174, 42);
			this->label15->Margin = System::Windows::Forms::Padding(0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(58, 43);
			this->label15->TabIndex = 0;
			this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label16
			// 
			this->label16->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label16->AutoSize = true;
			this->label16->BackColor = System::Drawing::Color::Teal;
			this->label16->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label16->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label16->Location = System::Drawing::Point(232, 42);
			this->label16->Margin = System::Windows::Forms::Padding(0);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(58, 43);
			this->label16->TabIndex = 0;
			this->label16->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_inX
			// 
			this->label_inX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_inX->AutoSize = true;
			this->label_inX->BackColor = System::Drawing::Color::Teal;
			this->label_inX->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_inX->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_inX->Location = System::Drawing::Point(290, 42);
			this->label_inX->Margin = System::Windows::Forms::Padding(0);
			this->label_inX->Name = L"label_inX";
			this->label_inX->Size = System::Drawing::Size(58, 43);
			this->label_inX->TabIndex = 0;
			this->label_inX->Text = L"INX";
			this->label_inX->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_inY
			// 
			this->label_inY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_inY->AutoSize = true;
			this->label_inY->BackColor = System::Drawing::Color::Teal;
			this->label_inY->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_inY->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_inY->Location = System::Drawing::Point(348, 42);
			this->label_inY->Margin = System::Windows::Forms::Padding(0);
			this->label_inY->Name = L"label_inY";
			this->label_inY->Size = System::Drawing::Size(58, 43);
			this->label_inY->TabIndex = 0;
			this->label_inY->Text = L"INY";
			this->label_inY->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_inZ
			// 
			this->label_inZ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_inZ->AutoSize = true;
			this->label_inZ->BackColor = System::Drawing::Color::Teal;
			this->label_inZ->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_inZ->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_inZ->Location = System::Drawing::Point(406, 42);
			this->label_inZ->Margin = System::Windows::Forms::Padding(0);
			this->label_inZ->Name = L"label_inZ";
			this->label_inZ->Size = System::Drawing::Size(58, 43);
			this->label_inZ->TabIndex = 0;
			this->label_inZ->Text = L"INZ";
			this->label_inZ->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_nX
			// 
			this->label_nX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_nX->AutoSize = true;
			this->label_nX->BackColor = System::Drawing::Color::Teal;
			this->label_nX->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_nX->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_nX->Location = System::Drawing::Point(464, 42);
			this->label_nX->Margin = System::Windows::Forms::Padding(0);
			this->label_nX->Name = L"label_nX";
			this->label_nX->Size = System::Drawing::Size(58, 43);
			this->label_nX->TabIndex = 0;
			this->label_nX->Text = L"NX";
			this->label_nX->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_nY
			// 
			this->label_nY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_nY->AutoSize = true;
			this->label_nY->BackColor = System::Drawing::Color::Teal;
			this->label_nY->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_nY->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_nY->Location = System::Drawing::Point(522, 42);
			this->label_nY->Margin = System::Windows::Forms::Padding(0);
			this->label_nY->Name = L"label_nY";
			this->label_nY->Size = System::Drawing::Size(58, 43);
			this->label_nY->TabIndex = 0;
			this->label_nY->Text = L"NY";
			this->label_nY->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_nZ
			// 
			this->label_nZ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_nZ->AutoSize = true;
			this->label_nZ->BackColor = System::Drawing::Color::Teal;
			this->label_nZ->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_nZ->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_nZ->Location = System::Drawing::Point(580, 42);
			this->label_nZ->Margin = System::Windows::Forms::Padding(0);
			this->label_nZ->Name = L"label_nZ";
			this->label_nZ->Size = System::Drawing::Size(62, 43);
			this->label_nZ->TabIndex = 0;
			this->label_nZ->Text = L"NZ";
			this->label_nZ->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::Transparent;
			this->groupBox1->Controls->Add(this->label_targetZ);
			this->groupBox1->Controls->Add(this->label_targetY);
			this->groupBox1->Controls->Add(this->label_targetX);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->groupBox1->ForeColor = System::Drawing::Color::Maroon;
			this->groupBox1->Location = System::Drawing::Point(13, 97);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(306, 215);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"直角坐標";
			// 
			// label_targetZ
			// 
			this->label_targetZ->BackColor = System::Drawing::Color::Transparent;
			this->label_targetZ->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_targetZ->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->label_targetZ->Location = System::Drawing::Point(78, 155);
			this->label_targetZ->Name = L"label_targetZ";
			this->label_targetZ->Size = System::Drawing::Size(206, 38);
			this->label_targetZ->TabIndex = 1;
			this->label_targetZ->Text = L"0.000";
			this->label_targetZ->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_targetY
			// 
			this->label_targetY->BackColor = System::Drawing::Color::Transparent;
			this->label_targetY->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_targetY->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->label_targetY->Location = System::Drawing::Point(78, 98);
			this->label_targetY->Name = L"label_targetY";
			this->label_targetY->Size = System::Drawing::Size(206, 38);
			this->label_targetY->TabIndex = 1;
			this->label_targetY->Text = L"0.000";
			this->label_targetY->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_targetX
			// 
			this->label_targetX->BackColor = System::Drawing::Color::Transparent;
			this->label_targetX->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_targetX->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->label_targetX->Location = System::Drawing::Point(78, 41);
			this->label_targetX->Name = L"label_targetX";
			this->label_targetX->Size = System::Drawing::Size(206, 38);
			this->label_targetX->TabIndex = 1;
			this->label_targetX->Text = L"0.000";
			this->label_targetX->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->ForeColor = System::Drawing::Color::Maroon;
			this->label6->Location = System::Drawing::Point(24, 155);
			this->label6->Name = L"label6";
			this->label6->Padding = System::Windows::Forms::Padding(5);
			this->label6->Size = System::Drawing::Size(35, 36);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Z";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->ForeColor = System::Drawing::Color::Maroon;
			this->label2->Location = System::Drawing::Point(24, 98);
			this->label2->Name = L"label2";
			this->label2->Padding = System::Windows::Forms::Padding(5);
			this->label2->Size = System::Drawing::Size(35, 36);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Y";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->ForeColor = System::Drawing::Color::Maroon;
			this->label1->Location = System::Drawing::Point(24, 41);
			this->label1->Name = L"label1";
			this->label1->Padding = System::Windows::Forms::Padding(5);
			this->label1->Size = System::Drawing::Size(36, 36);
			this->label1->TabIndex = 0;
			this->label1->Text = L"X";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::Color::Transparent;
			this->groupBox2->Controls->Add(this->label_realZ);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->label_realY);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->label_realX);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->groupBox2->ForeColor = System::Drawing::Color::Maroon;
			this->groupBox2->Location = System::Drawing::Point(13, 318);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(196, 153);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"機械座標";
			// 
			// label_realZ
			// 
			this->label_realZ->BackColor = System::Drawing::Color::Transparent;
			this->label_realZ->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_realZ->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->label_realZ->Location = System::Drawing::Point(54, 111);
			this->label_realZ->Name = L"label_realZ";
			this->label_realZ->Size = System::Drawing::Size(130, 33);
			this->label_realZ->TabIndex = 1;
			this->label_realZ->Text = L"0.000";
			this->label_realZ->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->ForeColor = System::Drawing::Color::Maroon;
			this->label9->Location = System::Drawing::Point(12, 111);
			this->label9->Name = L"label9";
			this->label9->Padding = System::Windows::Forms::Padding(5);
			this->label9->Size = System::Drawing::Size(37, 31);
			this->label9->TabIndex = 0;
			this->label9->Text = L"W";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_realY
			// 
			this->label_realY->BackColor = System::Drawing::Color::Transparent;
			this->label_realY->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_realY->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->label_realY->Location = System::Drawing::Point(54, 70);
			this->label_realY->Name = L"label_realY";
			this->label_realY->Size = System::Drawing::Size(130, 33);
			this->label_realY->TabIndex = 1;
			this->label_realY->Text = L"-180.000";
			this->label_realY->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->ForeColor = System::Drawing::Color::Maroon;
			this->label7->Location = System::Drawing::Point(12, 29);
			this->label7->Name = L"label7";
			this->label7->Padding = System::Windows::Forms::Padding(5);
			this->label7->Size = System::Drawing::Size(32, 31);
			this->label7->TabIndex = 0;
			this->label7->Text = L"U";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_realX
			// 
			this->label_realX->BackColor = System::Drawing::Color::Transparent;
			this->label_realX->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_realX->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->label_realX->Location = System::Drawing::Point(54, 29);
			this->label_realX->Name = L"label_realX";
			this->label_realX->Size = System::Drawing::Size(130, 33);
			this->label_realX->TabIndex = 1;
			this->label_realX->Text = L"90.000";
			this->label_realX->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->ForeColor = System::Drawing::Color::Maroon;
			this->label8->Location = System::Drawing::Point(12, 70);
			this->label8->Name = L"label8";
			this->label8->Padding = System::Windows::Forms::Padding(5);
			this->label8->Size = System::Drawing::Size(31, 31);
			this->label8->TabIndex = 0;
			this->label8->Text = L"V";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::Color::Transparent;
			this->groupBox3->Controls->Add(this->button_teachEnd);
			this->groupBox3->Controls->Add(this->button_record);
			this->groupBox3->Controls->Add(this->button_teachIn);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->groupBox3->ForeColor = System::Drawing::Color::Maroon;
			this->groupBox3->Location = System::Drawing::Point(215, 318);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(104, 153);
			this->groupBox3->TabIndex = 1;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Teach";
			// 
			// button_teachEnd
			// 
			this->button_teachEnd->AutoSize = true;
			this->button_teachEnd->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_teachEnd->ForeColor = System::Drawing::Color::Black;
			this->button_teachEnd->Location = System::Drawing::Point(7, 108);
			this->button_teachEnd->Name = L"button_teachEnd";
			this->button_teachEnd->Size = System::Drawing::Size(88, 34);
			this->button_teachEnd->TabIndex = 0;
			this->button_teachEnd->Text = L"Trace";
			this->button_teachEnd->UseVisualStyleBackColor = true;
			// 
			// button_record
			// 
			this->button_record->AutoSize = true;
			this->button_record->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_record->ForeColor = System::Drawing::Color::Black;
			this->button_record->Location = System::Drawing::Point(7, 68);
			this->button_record->Name = L"button_record";
			this->button_record->Size = System::Drawing::Size(88, 34);
			this->button_record->TabIndex = 0;
			this->button_record->Text = L"Record";
			this->button_record->UseVisualStyleBackColor = true;
			this->button_record->Click += gcnew System::EventHandler(this, &Form1::button_record_Click);
			// 
			// button_teachIn
			// 
			this->button_teachIn->AutoSize = true;
			this->button_teachIn->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_teachIn->ForeColor = System::Drawing::Color::Black;
			this->button_teachIn->Location = System::Drawing::Point(7, 28);
			this->button_teachIn->Name = L"button_teachIn";
			this->button_teachIn->Size = System::Drawing::Size(88, 34);
			this->button_teachIn->TabIndex = 0;
			this->button_teachIn->Text = L"Teach In";
			this->button_teachIn->UseVisualStyleBackColor = true;
			this->button_teachIn->Click += gcnew System::EventHandler(this, &Form1::button_teachIn_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->BackColor = System::Drawing::Color::Transparent;
			this->groupBox4->Controls->Add(this->button_zMin);
			this->groupBox4->Controls->Add(this->button_zPlus);
			this->groupBox4->Controls->Add(this->button_yMin);
			this->groupBox4->Controls->Add(this->button_yPlus);
			this->groupBox4->Controls->Add(this->button_xMin);
			this->groupBox4->Controls->Add(this->button_xPlus);
			this->groupBox4->Location = System::Drawing::Point(325, 339);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(104, 132);
			this->groupBox4->TabIndex = 1;
			this->groupBox4->TabStop = false;
			// 
			// button_zMin
			// 
			this->button_zMin->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_zMin->Location = System::Drawing::Point(52, 90);
			this->button_zMin->Name = L"button_zMin";
			this->button_zMin->Size = System::Drawing::Size(42, 35);
			this->button_zMin->TabIndex = 0;
			this->button_zMin->Text = L"Z-";
			this->button_zMin->UseVisualStyleBackColor = true;
			this->button_zMin->Click += gcnew System::EventHandler(this, &Form1::button_zMin_Click);
			this->button_zMin->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_zMin_MouseDown);
			this->button_zMin->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_zMin_MouseUp);
			// 
			// button_zPlus
			// 
			this->button_zPlus->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_zPlus->Location = System::Drawing::Point(8, 90);
			this->button_zPlus->Name = L"button_zPlus";
			this->button_zPlus->Size = System::Drawing::Size(42, 35);
			this->button_zPlus->TabIndex = 0;
			this->button_zPlus->Text = L"Z+";
			this->button_zPlus->UseVisualStyleBackColor = true;
			this->button_zPlus->Click += gcnew System::EventHandler(this, &Form1::button_zPlus_Click);
			this->button_zPlus->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_zPlus_MouseDown);
			this->button_zPlus->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_zPlus_MouseUp);
			// 
			// button_yMin
			// 
			this->button_yMin->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_yMin->Location = System::Drawing::Point(52, 52);
			this->button_yMin->Name = L"button_yMin";
			this->button_yMin->Size = System::Drawing::Size(42, 35);
			this->button_yMin->TabIndex = 0;
			this->button_yMin->Text = L"Y-";
			this->button_yMin->UseVisualStyleBackColor = true;
			this->button_yMin->Click += gcnew System::EventHandler(this, &Form1::button_yMin_Click);
			this->button_yMin->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_yMin_MouseDown);
			this->button_yMin->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_yMin_MouseUp);
			// 
			// button_yPlus
			// 
			this->button_yPlus->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_yPlus->Location = System::Drawing::Point(8, 52);
			this->button_yPlus->Name = L"button_yPlus";
			this->button_yPlus->Size = System::Drawing::Size(42, 35);
			this->button_yPlus->TabIndex = 0;
			this->button_yPlus->Text = L"Y+";
			this->button_yPlus->UseVisualStyleBackColor = true;
			this->button_yPlus->Click += gcnew System::EventHandler(this, &Form1::button_yPlus_Click);
			this->button_yPlus->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_yPlus_MouseDown);
			this->button_yPlus->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_yPlus_MouseUp);
			// 
			// button_xMin
			// 
			this->button_xMin->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_xMin->Location = System::Drawing::Point(52, 14);
			this->button_xMin->Name = L"button_xMin";
			this->button_xMin->Size = System::Drawing::Size(42, 35);
			this->button_xMin->TabIndex = 0;
			this->button_xMin->Text = L"X-";
			this->button_xMin->UseVisualStyleBackColor = true;
			this->button_xMin->Click += gcnew System::EventHandler(this, &Form1::button_xMin_Click);
			this->button_xMin->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_xMin_MouseDown);
			this->button_xMin->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_xMin_MouseUp);
			// 
			// button_xPlus
			// 
			this->button_xPlus->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_xPlus->Location = System::Drawing::Point(8, 14);
			this->button_xPlus->Name = L"button_xPlus";
			this->button_xPlus->Size = System::Drawing::Size(42, 35);
			this->button_xPlus->TabIndex = 0;
			this->button_xPlus->Text = L"X+";
			this->button_xPlus->UseVisualStyleBackColor = true;
			this->button_xPlus->Click += gcnew System::EventHandler(this, &Form1::button_xPlus_Click);
			this->button_xPlus->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_xPlus_MouseDown);
			this->button_xPlus->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_xPlus_MouseUp);
			// 
			// groupBox5
			// 
			this->groupBox5->BackColor = System::Drawing::Color::Transparent;
			this->groupBox5->Controls->Add(this->button_bkl);
			this->groupBox5->Controls->Add(this->button_x1);
			this->groupBox5->Controls->Add(this->button_x100);
			this->groupBox5->Controls->Add(this->button_coordiChange);
			this->groupBox5->Controls->Add(this->button_fh);
			this->groupBox5->Controls->Add(this->button_x10);
			this->groupBox5->Location = System::Drawing::Point(435, 339);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(128, 132);
			this->groupBox5->TabIndex = 1;
			this->groupBox5->TabStop = false;
			// 
			// button_bkl
			// 
			this->button_bkl->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_bkl->Location = System::Drawing::Point(69, 90);
			this->button_bkl->Name = L"button_bkl";
			this->button_bkl->Size = System::Drawing::Size(44, 35);
			this->button_bkl->TabIndex = 0;
			this->button_bkl->Text = L"BKL";
			this->button_bkl->UseVisualStyleBackColor = true;
			// 
			// button_x1
			// 
			this->button_x1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_x1->Location = System::Drawing::Point(12, 14);
			this->button_x1->Name = L"button_x1";
			this->button_x1->Size = System::Drawing::Size(46, 35);
			this->button_x1->TabIndex = 0;
			this->button_x1->Text = L"X1";
			this->button_x1->UseVisualStyleBackColor = true;
			this->button_x1->Click += gcnew System::EventHandler(this, &Form1::button_x1_Click);
			// 
			// button_x100
			// 
			this->button_x100->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_x100->Location = System::Drawing::Point(12, 90);
			this->button_x100->Name = L"button_x100";
			this->button_x100->Size = System::Drawing::Size(46, 35);
			this->button_x100->TabIndex = 0;
			this->button_x100->Text = L"X100";
			this->button_x100->UseVisualStyleBackColor = true;
			this->button_x100->Click += gcnew System::EventHandler(this, &Form1::button_x100_Click);
			// 
			// button_coordiChange
			// 
			this->button_coordiChange->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_coordiChange->Location = System::Drawing::Point(69, 14);
			this->button_coordiChange->Name = L"button_coordiChange";
			this->button_coordiChange->Size = System::Drawing::Size(44, 35);
			this->button_coordiChange->TabIndex = 0;
			this->button_coordiChange->Text = L"UVW";
			this->button_coordiChange->UseVisualStyleBackColor = true;
			this->button_coordiChange->Click += gcnew System::EventHandler(this, &Form1::button_coordiChange_Click);
			// 
			// button_fh
			// 
			this->button_fh->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_fh->Location = System::Drawing::Point(69, 52);
			this->button_fh->Name = L"button_fh";
			this->button_fh->Size = System::Drawing::Size(44, 35);
			this->button_fh->TabIndex = 0;
			this->button_fh->Text = L"FH";
			this->button_fh->UseVisualStyleBackColor = true;
			this->button_fh->Click += gcnew System::EventHandler(this, &Form1::button_fh_Click);
			// 
			// button_x10
			// 
			this->button_x10->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_x10->Location = System::Drawing::Point(12, 52);
			this->button_x10->Name = L"button_x10";
			this->button_x10->Size = System::Drawing::Size(46, 35);
			this->button_x10->TabIndex = 0;
			this->button_x10->Text = L"X10";
			this->button_x10->UseVisualStyleBackColor = true;
			this->button_x10->Click += gcnew System::EventHandler(this, &Form1::button_x10_Click);
			// 
			// groupBox6
			// 
			this->groupBox6->BackColor = System::Drawing::Color::Transparent;
			this->groupBox6->Controls->Add(this->button_cycleStart);
			this->groupBox6->Controls->Add(this->button_reset);
			this->groupBox6->Controls->Add(this->trackBar_override);
			this->groupBox6->Controls->Add(this->label_overridePercent);
			this->groupBox6->Controls->Add(this->label10);
			this->groupBox6->Location = System::Drawing::Point(569, 339);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(209, 132);
			this->groupBox6->TabIndex = 1;
			this->groupBox6->TabStop = false;
			// 
			// button_cycleStart
			// 
			this->button_cycleStart->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_cycleStart->Location = System::Drawing::Point(113, 78);
			this->button_cycleStart->Name = L"button_cycleStart";
			this->button_cycleStart->Size = System::Drawing::Size(75, 44);
			this->button_cycleStart->TabIndex = 3;
			this->button_cycleStart->Text = L"Cycle\r\nStart\r\n";
			this->button_cycleStart->UseVisualStyleBackColor = true;
			this->button_cycleStart->Click += gcnew System::EventHandler(this, &Form1::button_cycleStart_Click);
			// 
			// button_reset
			// 
			this->button_reset->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_reset->Location = System::Drawing::Point(20, 79);
			this->button_reset->Name = L"button_reset";
			this->button_reset->Size = System::Drawing::Size(75, 44);
			this->button_reset->TabIndex = 3;
			this->button_reset->Text = L"Reset";
			this->button_reset->UseVisualStyleBackColor = true;
			this->button_reset->Click += gcnew System::EventHandler(this, &Form1::button_reset_Click);
			// 
			// trackBar_override
			// 
			this->trackBar_override->BackColor = System::Drawing::Color::DimGray;
			this->trackBar_override->LargeChange = 10;
			this->trackBar_override->Location = System::Drawing::Point(14, 38);
			this->trackBar_override->Name = L"trackBar_override";
			this->trackBar_override->Size = System::Drawing::Size(178, 45);
			this->trackBar_override->SmallChange = 10;
			this->trackBar_override->TabIndex = 2;
			this->trackBar_override->TickFrequency = 10;
			this->trackBar_override->Scroll += gcnew System::EventHandler(this, &Form1::trackBar_override_Scroll);
			this->trackBar_override->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::trackBar_override_MouseUp);
			// 
			// label_overridePercent
			// 
			this->label_overridePercent->AutoSize = true;
			this->label_overridePercent->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_overridePercent->ForeColor = System::Drawing::Color::Maroon;
			this->label_overridePercent->Location = System::Drawing::Point(119, 14);
			this->label_overridePercent->Name = L"label_overridePercent";
			this->label_overridePercent->Size = System::Drawing::Size(44, 17);
			this->label_overridePercent->TabIndex = 0;
			this->label_overridePercent->Text = L"100%";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label10->ForeColor = System::Drawing::Color::Maroon;
			this->label10->Location = System::Drawing::Point(19, 14);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(94, 17);
			this->label10->TabIndex = 0;
			this->label10->Text = L"Feed Override";
			// 
			// richTextBox_ncFile
			// 
			this->richTextBox_ncFile->EnableAutoDragDrop = true;
			this->richTextBox_ncFile->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->richTextBox_ncFile->Location = System::Drawing::Point(325, 103);
			this->richTextBox_ncFile->Name = L"richTextBox_ncFile";
			this->richTextBox_ncFile->ReadOnly = true;
			this->richTextBox_ncFile->Size = System::Drawing::Size(453, 209);
			this->richTextBox_ncFile->TabIndex = 2;
			this->richTextBox_ncFile->Text = L"NC file";
			this->richTextBox_ncFile->WordWrap = false;
			// 
			// textBox_ncPath
			// 
			this->textBox_ncPath->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->textBox_ncPath->Location = System::Drawing::Point(391, 318);
			this->textBox_ncPath->Name = L"textBox_ncPath";
			this->textBox_ncPath->Size = System::Drawing::Size(387, 23);
			this->textBox_ncPath->TabIndex = 3;
			this->textBox_ncPath->Text = L"NC path";
			// 
			// button_file
			// 
			this->button_file->FlatAppearance->BorderSize = 2;
			this->button_file->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_file->Location = System::Drawing::Point(325, 318);
			this->button_file->Name = L"button_file";
			this->button_file->Size = System::Drawing::Size(60, 23);
			this->button_file->TabIndex = 4;
			this->button_file->Text = L"File";
			this->button_file->UseVisualStyleBackColor = true;
			this->button_file->Click += gcnew System::EventHandler(this, &Form1::button_file_Click);
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 5;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				16.66667F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				16.66667F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				16.66667F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				16.66667F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				16.66667F)));
			this->tableLayoutPanel2->Controls->Add(this->button_mem, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->button_mdi, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->button_jog, 2, 0);
			this->tableLayoutPanel2->Controls->Add(this->button_home, 3, 0);
			this->tableLayoutPanel2->Controls->Add(this->button_wheel, 4, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(13, 478);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(551, 78);
			this->tableLayoutPanel2->TabIndex = 5;
			// 
			// button_mem
			// 
			this->button_mem->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->button_mem->BackColor = System::Drawing::Color::Turquoise;
			this->button_mem->FlatAppearance->BorderColor = System::Drawing::Color::Maroon;
			this->button_mem->FlatAppearance->BorderSize = 5;
			this->button_mem->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_mem->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_mem->ForeColor = System::Drawing::Color::Maroon;
			this->button_mem->Location = System::Drawing::Point(1, 1);
			this->button_mem->Margin = System::Windows::Forms::Padding(1);
			this->button_mem->Name = L"button_mem";
			this->button_mem->Size = System::Drawing::Size(108, 76);
			this->button_mem->TabIndex = 0;
			this->button_mem->Text = L"MEM";
			this->button_mem->UseVisualStyleBackColor = false;
			this->button_mem->Click += gcnew System::EventHandler(this, &Form1::button_mem_Click);
			// 
			// button_mdi
			// 
			this->button_mdi->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->button_mdi->BackColor = System::Drawing::Color::Teal;
			this->button_mdi->FlatAppearance->BorderColor = System::Drawing::Color::Maroon;
			this->button_mdi->FlatAppearance->BorderSize = 5;
			this->button_mdi->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_mdi->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_mdi->Location = System::Drawing::Point(111, 1);
			this->button_mdi->Margin = System::Windows::Forms::Padding(1);
			this->button_mdi->Name = L"button_mdi";
			this->button_mdi->Size = System::Drawing::Size(108, 76);
			this->button_mdi->TabIndex = 0;
			this->button_mdi->Text = L"MDI";
			this->button_mdi->UseVisualStyleBackColor = false;
			this->button_mdi->Click += gcnew System::EventHandler(this, &Form1::button_mdi_Click);
			// 
			// button_jog
			// 
			this->button_jog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->button_jog->BackColor = System::Drawing::Color::Teal;
			this->button_jog->FlatAppearance->BorderColor = System::Drawing::Color::Maroon;
			this->button_jog->FlatAppearance->BorderSize = 5;
			this->button_jog->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_jog->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_jog->Location = System::Drawing::Point(221, 1);
			this->button_jog->Margin = System::Windows::Forms::Padding(1);
			this->button_jog->Name = L"button_jog";
			this->button_jog->Size = System::Drawing::Size(108, 76);
			this->button_jog->TabIndex = 0;
			this->button_jog->Text = L"JOG";
			this->button_jog->UseVisualStyleBackColor = false;
			this->button_jog->Click += gcnew System::EventHandler(this, &Form1::button_jog_Click);
			// 
			// button_home
			// 
			this->button_home->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->button_home->BackColor = System::Drawing::Color::Teal;
			this->button_home->FlatAppearance->BorderColor = System::Drawing::Color::Maroon;
			this->button_home->FlatAppearance->BorderSize = 5;
			this->button_home->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_home->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_home->Location = System::Drawing::Point(331, 1);
			this->button_home->Margin = System::Windows::Forms::Padding(1);
			this->button_home->Name = L"button_home";
			this->button_home->Size = System::Drawing::Size(108, 76);
			this->button_home->TabIndex = 0;
			this->button_home->Text = L"HOME";
			this->button_home->UseVisualStyleBackColor = false;
			this->button_home->Click += gcnew System::EventHandler(this, &Form1::button_home_Click);
			// 
			// button_wheel
			// 
			this->button_wheel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->button_wheel->BackColor = System::Drawing::Color::Teal;
			this->button_wheel->FlatAppearance->BorderColor = System::Drawing::Color::Maroon;
			this->button_wheel->FlatAppearance->BorderSize = 5;
			this->button_wheel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_wheel->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_wheel->Location = System::Drawing::Point(441, 1);
			this->button_wheel->Margin = System::Windows::Forms::Padding(1);
			this->button_wheel->Name = L"button_wheel";
			this->button_wheel->Size = System::Drawing::Size(109, 76);
			this->button_wheel->TabIndex = 0;
			this->button_wheel->Text = L"WHEEL";
			this->button_wheel->UseVisualStyleBackColor = false;
			this->button_wheel->Click += gcnew System::EventHandler(this, &Form1::button_wheel_Click);
			// 
			// button_emergencyStop
			// 
			this->button_emergencyStop->BackColor = System::Drawing::Color::Red;
			this->button_emergencyStop->FlatAppearance->BorderColor = System::Drawing::Color::Maroon;
			this->button_emergencyStop->FlatAppearance->BorderSize = 5;
			this->button_emergencyStop->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button_emergencyStop->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 17.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_emergencyStop->Location = System::Drawing::Point(570, 479);
			this->button_emergencyStop->Name = L"button_emergencyStop";
			this->button_emergencyStop->Size = System::Drawing::Size(208, 76);
			this->button_emergencyStop->TabIndex = 6;
			this->button_emergencyStop->Text = L"Emergency\r\nStop\r\n";
			this->button_emergencyStop->UseVisualStyleBackColor = false;
			this->button_emergencyStop->Click += gcnew System::EventHandler(this, &Form1::button_emergencyStop_Click);
			// 
			// openFileDialog_openNc
			// 
			this->openFileDialog_openNc->FileName = L"openFileDialog_openNc";
			// 
			// timer_real
			// 
			this->timer_real->Tick += gcnew System::EventHandler(this, &Form1::timer_real_Tick);
			// 
			// timer_nonreal
			// 
			this->timer_nonreal->Tick += gcnew System::EventHandler(this, &Form1::timer_nonreal_Tick);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(118, 85);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 7;
			this->pictureBox1->TabStop = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::DimGray;
			this->ClientSize = System::Drawing::Size(790, 568);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button_emergencyStop);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->button_file);
			this->Controls->Add(this->textBox_ncPath);
			this->Controls->Add(this->richTextBox_ncFile);
			this->Controls->Add(this->groupBox6);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->tableLayoutPanel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"Form1";
			this->Text = L"CNC";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Form1::Form1_FormClosed);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_override))->EndInit();
			this->tableLayoutPanel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

//**********************************************

//**********************************************
void formReset( void )
{
	
	label_m30->BackColor = Color::Teal;
	label_pgm->BackColor = Color::Teal;
	textBox_ncPath->Clear();
	richTextBox_ncFile->Clear();
	button_xPlus->BackColor = Color::Transparent;
	button_yPlus->BackColor = Color::Transparent;
	button_zPlus->BackColor = Color::Transparent;
	button_xMin->BackColor = Color::Transparent;
	button_yMin->BackColor = Color::Transparent;
	button_zMin->BackColor = Color::Transparent;
	button_xPlus->Text = "X+";
	button_yPlus->Text = "Y+";
	button_zPlus->Text = "Z+";
	button_xMin->Text = "X-";
	button_yMin->Text = "Y-";
	button_zMin->Text = "Z-";
	button_coordiChange->Text = "UVW";
	button_fh->BackColor = Color::Transparent;
	trackBar_override->Value = 100;
	label_overridePercent->Text  = "100%";


}

private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
		 {

			 sysLinkDataPtr = &sysLinkData;
			 sysDataPtr = &sysData;
			 decDataPtr = &decData;
			 intpDataPtr = &intpData;
			 mmiDataPtr = &mmiData;

			 mmiInit( mmiDataPtr );
			 sysLinkInit( sysLinkDataPtr );
			 decInit( decDataPtr );
			 intpInit( intpDataPtr);
			 sysInit( sysDataPtr );

			 trackBar_override->SetRange( 0, 200 );
			 trackBar_override->Value = 100;

#if HD_TIMER
			 // init motion card
			 initMotionCard(axisInitValue[0], axisInitValue[1], 
				                           axisInitValue[2], Timer_ISR_Function);
			 // enable timer
			 enableHDTimer(REAL_SAMPLING_TIME);	
			 realTimer->Enabled		= false;
			 nonRealTimer->Enabled	= true;
#else
			 // init motion card
			 //initMotionCard( sysDataPtr->axisInitValue[0], sysDataPtr->axisInitValue[1], sysDataPtr->axisInitValue[2], NULL);
			 timer_real->Interval     = 1;
			 timer_nonreal->Interval  = 50;
			 timer_real->Enabled      = true;
			 timer_nonreal->Enabled   = true;
#endif
		 }

private: System::Void timer_real_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
#ifdef DBG
			 
			 SYS_LINK_DATA	*sysLinkPtr = sysLinkDataPtr;
			 SYS_DATA		*sysPtr = sysDataPtr;
			 DEC_DATA		*decPtr = decDataPtr;
			 INTP_DATA		*intpPtr = intpDataPtr;
			 MMI_DATA		*mmiPtr = mmiDataPtr;
#endif		
			 mmiDataPtr->counter++;
			 if ( mmiDataPtr->counter >1000 )
				 mmiDataPtr->counter = 0;
			 intpMain( intpDataPtr );

			 realKnl( sysDataPtr );

		 }

private: System::Void button_cycleStart_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
#ifdef DBG
			 
			 SYS_LINK_DATA	*sysLinkPtr = sysLinkDataPtr;
			 SYS_DATA		*sysPtr = sysDataPtr;
			 DEC_DATA		*decPtr = decDataPtr;
			 INTP_DATA		*intpPtr = intpDataPtr;
			 MMI_DATA		*mmiPtr = mmiDataPtr;
#endif	
			 if( sysDataPtr->fileValid == true || mmiDataPtr->opMode == HOME_MODE )
			 {
				 sysLinkDataPtr->pannelOutput.m30 = false;
				 mmiDataPtr->cycleStart = true;
				 button_cycleStart->BackColor = Color::Red;
				 label_m30->BackColor = Color::Teal;
				 label_pgm->BackColor = Color::Red;
			 }
			 else if( mmiDataPtr->opMode == MDI_MODE )
			 {
				 pin_ptr<const wchar_t> wch = PtrToStringChars( richTextBox_ncFile->Text );
				 size_t  sizeInBytes = ( ( openFileDialog_openNc->FileName->Length ) * 2 );
				 size_t  convertedChars = 0;
				 wcstombs_s( &convertedChars, sysDataPtr->ncBuffer, sizeInBytes, wch, sizeInBytes );						 
				 sysDataPtr->fileValid = true;

				 sysLinkDataPtr->pannelOutput.m30 = false;
				 mmiDataPtr->cycleStart = true;
				 button_cycleStart->BackColor = Color::Red;
				 label_m30->BackColor = Color::Teal;
				 label_pgm->BackColor = Color::Red;
			 }
		}

private: System::Void timer_nonreal_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
			 label_counter->Text = mmiDataPtr->counter.ToString();

			 mmiMain( mmiDataPtr );
			 sysMain( sysDataPtr );
			 decMain( decDataPtr );

			 label_targetX->Text = sysLinkDataPtr->intpToSysData.newSettingValue[0].ToString("F3");

			 label_targetY->Text = sysLinkDataPtr->intpToSysData.newSettingValue[1].ToString("F3");

			 label_targetZ->Text = sysLinkDataPtr->intpToSysData.newSettingValue[2].ToString("F3");

			 label_realX->Text = sysLinkDataPtr->intpToSysData.newSettingValueUVW[0].ToString("F3");

			 label_realY->Text = sysLinkDataPtr->intpToSysData.newSettingValueUVW[1].ToString("F3");

			 label_realZ->Text = sysLinkDataPtr->intpToSysData.newSettingValueUVW[2].ToString("F3");

			 if( mmiDataPtr->cycleStart == false )
			 {
				 button_cycleStart->BackColor = Color::Transparent;

				 if( sysLinkDataPtr->pannelOutput.m30 == true )
				 {
					label_m30->BackColor = Color::Red;
					label_pgm->BackColor = Color::Teal;
				 }
				 else
				 {
					 label_m30->BackColor = Color::Teal;
				 }
			 }

		 }

private: System::Void button_x1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ( mmiDataPtr->opMode == WHEEL_MODE )
			 {
				 mmiDataPtr->handWheelGain = 1;
			 }
		 }
private: System::Void button_x10_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ( mmiDataPtr->opMode == WHEEL_MODE )
			 {
				 mmiDataPtr->handWheelGain = 10;
			 }
		 }

private: System::Void button_x100_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ( mmiDataPtr->opMode == WHEEL_MODE )
			 {
				 mmiDataPtr->handWheelGain = 100;
			 }
		 }

private: System::Void trackBar_override_Scroll(System::Object^  sender, System::EventArgs^  e) 
		 {
			 mmiDataPtr->feedOverride = trackBar_override->Value;
			 label_overridePercent->Text  = mmiDataPtr->feedOverride.ToString() + "%";
		 }

private: System::Void button_file_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ( mmiDataPtr->opMode == MEM_MODE )
			 {
				 openFileDialog_openNc->InitialDirectory = ".\\";//檔案開啟的預設路徑
				 openFileDialog_openNc->Filter = "文字檔(*.txt)|*.txt|所有檔案(*.*)|*.*";
				 openFileDialog_openNc->FilterIndex = 1;//取得Filter第1個篩選條件
				 openFileDialog_openNc->DefaultExt = "*.txt";//預設為文字檔
				 openFileDialog_openNc->FileName = "";//清除檔案名稱的字串
				 openFileDialog_openNc->RestoreDirectory = true;//指定上一次開啟的路徑

				/* openFileDialog_openNc->InitialDirectory = "";
				 openFileDialog_openNc->Filter = "文字檔(*txt)|*.txt|所有檔案(*.*)|*.*";
				 openFileDialog_openNc->FilterIndex = 1;
				 openFileDialog_openNc->DefaultExt = "*.txt";
				 openFileDialog_openNc->FileName = "";
				 openFileDialog_openNc->RestoreDirectory = true;*/

				 if ( openFileDialog_openNc->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				 {
					 textBox_ncPath->Text = openFileDialog_openNc->FileName;
					 richTextBox_ncFile->LoadFile ( openFileDialog_openNc->FileName, RichTextBoxStreamType::PlainText );

					 //copy file name
					 pin_ptr<const wchar_t> wch = PtrToStringChars(openFileDialog_openNc->FileName);
					 size_t  sizeInBytes = ((openFileDialog_openNc->FileName->Length) * 2);
					 size_t  convertedChars = 0;
					 wcstombs_s(&convertedChars, sysDataPtr->fileName, sizeInBytes, wch, sizeInBytes);						 
					 sysDataPtr->fileValid = true;
				 }
			 }
		 }
private: System::Void button_mem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ( mmiDataPtr->opMode != MEM_MODE && mmiDataPtr->cycleStart == false )
			 {
				 formReset();
				 mmiDataPtr->reset = true;
				 mmiDataPtr->opMode = MEM_MODE;
				 button_mem->ForeColor = Color::Maroon;
				 button_mdi->ForeColor = Color::Black;
				 button_jog->ForeColor = Color::Black;
				 button_home->ForeColor = Color::Black;
				 button_wheel->ForeColor = Color::Black;
				 button_mem->BackColor = Color::Turquoise;
				 button_mdi->BackColor = Color::Teal;
				 button_jog->BackColor = Color::Teal;
				 button_home->BackColor = Color::Teal;
				 button_wheel->BackColor = Color::Teal;
			 }
		 }
private: System::Void button_mdi_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ( mmiDataPtr->opMode != MDI_MODE && mmiDataPtr->cycleStart == false )
			 {
				 formReset();
				 mmiDataPtr->reset = true;
				 mmiDataPtr->opMode = MDI_MODE;
				 button_mem->ForeColor = Color::Black;
				 button_mdi->ForeColor = Color::Maroon;
				 button_jog->ForeColor = Color::Black;
				 button_home->ForeColor = Color::Black;
				 button_wheel->ForeColor = Color::Black;
				 button_mem->BackColor = Color::Teal;
				 button_mdi->BackColor = Color::Turquoise;
				 button_jog->BackColor = Color::Teal;
				 button_home->BackColor = Color::Teal;
				 button_wheel->BackColor = Color::Teal;
			 }
		 }
private: System::Void button_jog_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ( mmiDataPtr->opMode != JOG_MODE && mmiDataPtr->cycleStart == false )
			 {
				 formReset();
				 mmiDataPtr->reset = true;
				 mmiDataPtr->opMode = JOG_MODE;
				 button_mem->ForeColor = Color::Black;
				 button_mdi->ForeColor = Color::Black;
				 button_jog->ForeColor = Color::Maroon;
				 button_home->ForeColor = Color::Black;
				 button_wheel->ForeColor = Color::Black;
				 button_mem->BackColor = Color::Teal;
				 button_mdi->BackColor = Color::Teal;
				 button_jog->BackColor = Color::Turquoise;
				 button_home->BackColor = Color::Teal;
				 button_wheel->BackColor = Color::Teal;
			 }
		 }
private: System::Void button_home_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ( mmiDataPtr->opMode != HOME_MODE && mmiDataPtr->cycleStart == false )
			 {
				 formReset();
				 mmiDataPtr->reset = true;
				 mmiDataPtr->opMode = HOME_MODE;
				 button_mem->ForeColor = Color::Black;
				 button_mdi->ForeColor = Color::Black;
				 button_jog->ForeColor = Color::Black;
				 button_home->ForeColor = Color::Maroon;
				 button_wheel->ForeColor = Color::Black;
				 button_mem->BackColor = Color::Teal;
				 button_mdi->BackColor = Color::Teal;
				 button_jog->BackColor = Color::Teal;
				 button_home->BackColor = Color::Turquoise;
				 button_wheel->BackColor = Color::Teal;
			 }
		 }
private: System::Void button_wheel_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ( mmiDataPtr->opMode != WHEEL_MODE && mmiDataPtr->cycleStart == false )
			 {
				 formReset();
				 mmiDataPtr->reset = true;
				 mmiDataPtr->opMode = WHEEL_MODE;
				 button_mem->ForeColor = Color::Black;
				 button_mdi->ForeColor = Color::Black;
				 button_jog->ForeColor = Color::Black;
				 button_home->ForeColor = Color::Black;
				 button_wheel->ForeColor = Color::Maroon;
				 button_mem->BackColor = Color::Teal;
				 button_mdi->BackColor = Color::Teal;
				 button_jog->BackColor = Color::Teal;
				 button_home->BackColor = Color::Teal;
				 button_wheel->BackColor = Color::Turquoise;
			 }
		 }
private: System::Void button_xPlus_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE )
			 {
				 mmiDataPtr->feedHold = false;
				 mmiDataPtr->coordiPlus[0] = true;
				 mmiDataPtr->coordiPlus[1] = false;
				 mmiDataPtr->coordiPlus[2] = false;
				 mmiDataPtr->coordiMinu[0] = false;
				 mmiDataPtr->coordiMinu[1] = false;
				 mmiDataPtr->coordiMinu[2] = false;
			 }
		 }
private: System::Void button_yPlus_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE )
			 {
				 mmiDataPtr->feedHold = false;
				 mmiDataPtr->coordiPlus[0] = false;
				 mmiDataPtr->coordiPlus[1] = true;
				 mmiDataPtr->coordiPlus[2] = false;
				 mmiDataPtr->coordiMinu[0] = false;
				 mmiDataPtr->coordiMinu[1] = false;
				 mmiDataPtr->coordiMinu[2] = false;
			 }
		 }
private: System::Void button_zPlus_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE )
			 {
				 mmiDataPtr->feedHold = false;
				 mmiDataPtr->coordiPlus[0] = false;
				 mmiDataPtr->coordiPlus[1] = false;
				 mmiDataPtr->coordiPlus[2] = true;
				 mmiDataPtr->coordiMinu[0] = false;
				 mmiDataPtr->coordiMinu[1] = false;
				 mmiDataPtr->coordiMinu[2] = false;
			 }
		 }
private: System::Void button_xMin_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE )
			 {
				 mmiDataPtr->feedHold = false;
				 mmiDataPtr->coordiPlus[0] = false;
				 mmiDataPtr->coordiPlus[1] = false;
				 mmiDataPtr->coordiPlus[2] = false;
				 mmiDataPtr->coordiMinu[0] = true;
				 mmiDataPtr->coordiMinu[1] = false;
				 mmiDataPtr->coordiMinu[2] = false;
			 }
		 }
private: System::Void button_yMin_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE )
			 {
				 mmiDataPtr->feedHold = false;
				 mmiDataPtr->coordiPlus[0] = false;
				 mmiDataPtr->coordiPlus[1] = false;
				 mmiDataPtr->coordiPlus[2] = false;
				 mmiDataPtr->coordiMinu[0] = false;
				 mmiDataPtr->coordiMinu[1] = true;
				 mmiDataPtr->coordiMinu[2] = false;
			 }
		 }
private: System::Void button_zMin_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE )
			 {
				 mmiDataPtr->feedHold = false;
				 mmiDataPtr->coordiPlus[0] = false;
				 mmiDataPtr->coordiPlus[1] = false;
				 mmiDataPtr->coordiPlus[2] = false;
				 mmiDataPtr->coordiMinu[0] = false;
				 mmiDataPtr->coordiMinu[1] = false;
				 mmiDataPtr->coordiMinu[2] = true;
			 }
		 }
private: System::Void button_xPlus_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE )
			 {
				 mmiDataPtr->coordiPlus[0] = false;
				 mmiDataPtr->feedHold = true;
			 }
		 }
private: System::Void button_yPlus_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE )
			 {
				 mmiDataPtr->coordiPlus[1] = false;
				 mmiDataPtr->feedHold = true;
			 }
		 }
private: System::Void button_zPlus_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE )
			 {
				 mmiDataPtr->coordiPlus[2] = false;
				 mmiDataPtr->feedHold = true;
			 }
		 }
private: System::Void button_xMin_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE )
			 {
				 mmiDataPtr->coordiMinu[0] = false;
				 mmiDataPtr->feedHold = true;
			 }
		 }
private: System::Void button_yMin_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE )
			 {
				 mmiDataPtr->coordiMinu[1] = false;
				 mmiDataPtr->feedHold = true;
			 }
		 }
private: System::Void button_zMin_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE )
			 {
				 mmiDataPtr->coordiMinu[2] = false;
				 mmiDataPtr->feedHold = true;
			 }
		 }

private: System::Void button_fh_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if( mmiDataPtr->feedHold == false )
			 {
				 mmiDataPtr->feedHold = true;
				 button_fh->BackColor = Color::Red;
			 }
			 else
			 {
				 mmiDataPtr->feedHold = false;
				 button_fh->BackColor = Color::Transparent;
			 }
		 }
private: System::Void button_reset_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 mmiDataPtr->reset = true;
			 mmiDataPtr->teachIn = false;
			 sysDataPtr->recordCounter = 0;
			 formReset();
			 button_teachIn->BackColor = Color::Transparent;
		 }
private: System::Void button_coordiChange_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if( mmiDataPtr->opMode == JOG_MODE || mmiDataPtr->opMode == WHEEL_MODE || mmiDataPtr->opMode == HOME_MODE )
			 {
				 if( mmiDataPtr->xyzMode == true )
				 {
					 button_xPlus->Text = "U+";
					 button_yPlus->Text = "V+";
					 button_zPlus->Text = "W+";
					 button_xMin->Text = "U-";
					 button_yMin->Text = "V-";
					 button_zMin->Text = "W-";
					 button_coordiChange->Text = "XYZ";
					 mmiDataPtr->xyzMode = false;
				 }
				 else
				 {
					 button_xPlus->Text = "X+";
					 button_yPlus->Text = "Y+";
					 button_zPlus->Text = "Z+";
					 button_xMin->Text = "X-";
					 button_yMin->Text = "Y-";
					 button_zMin->Text = "Z-";
					 button_coordiChange->Text = "UVW";
					 mmiDataPtr->xyzMode = true;
				 }
			 }
		 }
private: System::Void Form1_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) 
		 {

#if HD_TIMER
			 disableHDTimer();
#endif
			 //closeMotionCard();

		 }
private: System::Void button_teachIn_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if( mmiDataPtr->teachIn == false )
			 {
				 mmiDataPtr->teachIn = true;
				 button_teachIn->BackColor = Color::Red;
			 }
			 else
			 {
				 if( sysDataPtr->recordCounter != 0 )
				 {
					 saveFileDialog_saveNc->InitialDirectory = ".\\";//檔案開啟的預設路徑
					 saveFileDialog_saveNc->Filter = "文字檔(*.txt)|*.txt|所有檔案(*.*)|*.*";
					 saveFileDialog_saveNc->FilterIndex = 1;//取得Filter第2個篩選條件
					 saveFileDialog_saveNc->DefaultExt = "*.txt";//預設為文字檔
					 saveFileDialog_saveNc->FileName = "";//清除檔案名稱的字串
					 saveFileDialog_saveNc->RestoreDirectory = true;//指定上一次開啟的路徑

					 if ( saveFileDialog_saveNc->ShowDialog() == System::Windows::Forms::DialogResult::OK )
					 {
						 if( saveFileDialog_saveNc->FileName != System::String::Empty ) 
                         {
                             //copy file name
							 pin_ptr<const wchar_t> wch = PtrToStringChars(saveFileDialog_saveNc->FileName);
							 size_t  sizeInBytes = ((openFileDialog_openNc->FileName->Length) * 2);
							 size_t  convertedChars = 0;
							 wcstombs_s(&convertedChars, sysDataPtr->savefileName, sizeInBytes, wch, sizeInBytes);						 
							 teachEnd( sysDataPtr );
                         }
					 }
				 }
				 mmiDataPtr->teachIn = false;
				 button_teachIn->BackColor = Color::Transparent;
			 }
		 }
private: System::Void button_record_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if( mmiDataPtr->teachIn == true )
				 record( sysDataPtr );
		 }
private: System::Void button_xPlus_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 mmiDataPtr->handWheelGain = 0;
			 if( mmiDataPtr->opMode == WHEEL_MODE )
			 {
				 if( mmiDataPtr->coordiPlus[0] == false )
				 {
					 mmiDataPtr->coordiPlus[0] = true;
					 mmiDataPtr->coordiPlus[1] = false;
					 mmiDataPtr->coordiPlus[2] = false;
					 mmiDataPtr->coordiMinu[0] = false;
					 mmiDataPtr->coordiMinu[1] = false;
					 mmiDataPtr->coordiMinu[2] = false;
					 button_xPlus->BackColor = Color::Red;
					 button_yPlus->BackColor = Color::Transparent;
					 button_zPlus->BackColor = Color::Transparent;
					 button_xMin->BackColor = Color::Transparent;
					 button_yMin->BackColor = Color::Transparent;
					 button_zMin->BackColor = Color::Transparent;
				 }
				 else
				 {
					 mmiDataPtr->coordiPlus[0] = false;
					 button_xPlus->BackColor = Color::Transparent;
				 }
			 }
		 }
private: System::Void button_yPlus_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 mmiDataPtr->handWheelGain = 0;
			 if( mmiDataPtr->opMode == WHEEL_MODE )
			 {
				 if( mmiDataPtr->coordiPlus[1] == false )
				 {
					 mmiDataPtr->coordiPlus[1] = true;
					 mmiDataPtr->coordiPlus[0] = false;
					 mmiDataPtr->coordiPlus[2] = false;
					 mmiDataPtr->coordiMinu[0] = false;
					 mmiDataPtr->coordiMinu[1] = false;
					 mmiDataPtr->coordiMinu[2] = false;
					 button_yPlus->BackColor = Color::Red;
					 button_xPlus->BackColor = Color::Transparent;
					 button_zPlus->BackColor = Color::Transparent;
					 button_xMin->BackColor = Color::Transparent;
					 button_yMin->BackColor = Color::Transparent;
					 button_zMin->BackColor = Color::Transparent;
				 }
				 else
				 {
					 mmiDataPtr->coordiPlus[1] = false;
					 button_yPlus->BackColor = Color::Transparent;
				 }
			 }
		 }
private: System::Void button_zPlus_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 mmiDataPtr->handWheelGain = 0;
			 if( mmiDataPtr->opMode == WHEEL_MODE )
			 {
				 if( mmiDataPtr->coordiPlus[2] == false )
				 {
					 mmiDataPtr->coordiPlus[2] = true;
					 mmiDataPtr->coordiPlus[1] = false;
					 mmiDataPtr->coordiPlus[0] = false;
					 mmiDataPtr->coordiMinu[0] = false;
					 mmiDataPtr->coordiMinu[1] = false;
					 mmiDataPtr->coordiMinu[2] = false;
					 button_zPlus->BackColor = Color::Red;
					 button_yPlus->BackColor = Color::Transparent;
					 button_xPlus->BackColor = Color::Transparent;
					 button_xMin->BackColor = Color::Transparent;
					 button_yMin->BackColor = Color::Transparent;
					 button_zMin->BackColor = Color::Transparent;
				 }
				 else
				 {
					 mmiDataPtr->coordiPlus[2] = false;
					 button_zPlus->BackColor = Color::Transparent;
				 }
			 }
		 }
private: System::Void button_xMin_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 mmiDataPtr->handWheelGain = 0;
			 if( mmiDataPtr->opMode == WHEEL_MODE )
			 {
				 if( mmiDataPtr->coordiMinu[0] == false )
				 {
					 mmiDataPtr->coordiPlus[0] = false;
					 mmiDataPtr->coordiPlus[1] = false;
					 mmiDataPtr->coordiPlus[2] = false;
					 mmiDataPtr->coordiMinu[0] = true;
					 mmiDataPtr->coordiMinu[1] = false;
					 mmiDataPtr->coordiMinu[2] = false;
					 button_xMin->BackColor = Color::Red;
					 button_yPlus->BackColor = Color::Transparent;
					 button_zPlus->BackColor = Color::Transparent;
					 button_xPlus->BackColor = Color::Transparent;
					 button_yMin->BackColor = Color::Transparent;
					 button_zMin->BackColor = Color::Transparent;
				 }
				 else
				 {
					 mmiDataPtr->coordiMinu[0] = false;
					 button_xMin->BackColor = Color::Transparent;
				 }
			 }
		 }
private: System::Void button_yMin_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 mmiDataPtr->handWheelGain = 0;
			 if( mmiDataPtr->opMode == WHEEL_MODE )
			 {
				 if( mmiDataPtr->coordiMinu[1] == false )
				 {
					 mmiDataPtr->coordiPlus[0] = false;
					 mmiDataPtr->coordiPlus[1] = false;
					 mmiDataPtr->coordiPlus[2] = false;
					 mmiDataPtr->coordiMinu[0] = false;
					 mmiDataPtr->coordiMinu[1] = true;
					 mmiDataPtr->coordiMinu[2] = false;
					 button_yMin->BackColor = Color::Red;
					 button_yPlus->BackColor = Color::Transparent;
					 button_zPlus->BackColor = Color::Transparent;
					 button_xMin->BackColor = Color::Transparent;
					 button_xPlus->BackColor = Color::Transparent;
					 button_zMin->BackColor = Color::Transparent;
				 }
				 else
				 {
					 mmiDataPtr->coordiMinu[1] = false;
					 button_yMin->BackColor = Color::Transparent;
				 }
			 }
		 }
private: System::Void button_zMin_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 mmiDataPtr->handWheelGain = 0;
			 if( mmiDataPtr->opMode == WHEEL_MODE )
			 {
				 if( mmiDataPtr->coordiMinu[2] == false )
				 {
					 mmiDataPtr->coordiPlus[0] = false;
					 mmiDataPtr->coordiPlus[1] = false;
					 mmiDataPtr->coordiPlus[2] = false;
					 mmiDataPtr->coordiMinu[0] = false;
					 mmiDataPtr->coordiMinu[1] = false;
					 mmiDataPtr->coordiMinu[2] = true;
					 button_zMin->BackColor = Color::Red;
					 button_yPlus->BackColor = Color::Transparent;
					 button_zPlus->BackColor = Color::Transparent;
					 button_xMin->BackColor = Color::Transparent;
					 button_yMin->BackColor = Color::Transparent;
					 button_xPlus->BackColor = Color::Transparent;
				 }
				 else
				 {
					 mmiDataPtr->coordiMinu[2] = false;
					 button_zMin->BackColor = Color::Transparent;
				 }
			 }
		 }
private: System::Void trackBar_override_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			 mmiDataPtr->feedChange = true;
			 mmiDataPtr->feedOverride = trackBar_override->Value;
		 }
private: System::Void button_emergencyStop_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 sysLinkDataPtr->emStop = true;
		 }
};
}

