#pragma once

#include "..\MMI\INC\MMI.h"
#include "..\SYS\INC\SYS.h"
#include "..\SYS_LINK\INC\sys_link.h"
#include "..\INTP\INC\INTP.h"
#include "..\DEC\INC\dec.h"
#include "..\CNC\INC\CNC.h"
#include "..\DEF\cpSwitch.h"
#include "..\Drivers\INC\stepMotorDRV.h"
#include "vcclr.h"
#include "io.h"
#include "stdlib.h"
#include "string.h"

extern MMI_DATA *mmiDataPtr;
CNC_DATA        cncData;  
CNC_DATA        *cncDataPtr;
INTP_DATA       *intpDataPtr; 
SYS_LINK_DATA   *sysLinkDataPtr;
DEC_DATA		*decDataPtr;
SYS_DATA        *sysDataPtr;

typedef struct
{
	double	mSetValue;			// setting value in mm	(or degree)
	double	mActValue;			// actual value in mm	(or degree)
	double	resolution;			// resolution, mm/inc	(or degree/inc)
	int		relInc;				// Relative Increment, 
	// relInc = (set - oldSet) / resolution 

	double  remainValue;        // Remainder, in mm (or degree) 

} AXIS_DATA;

AXIS_DATA	axisData[3];

double axisInitValue[3] = {0, 0, 100.0};

int realKnl(void)
{
	//在這裡把INTP的值丟進來
	//******************************************
	// position control 
	//******************************************
	int i;

	for( i = 0 ; i<3 ; ++i)
	{
		// relInc = (set - oldSet) / resolution
		axisData[i].mActValue = intpDataPtr -> xyzOriginToPCL[i] ;
		axisData[i].mSetValue = intpDataPtr -> uvwNew[i];
		axisData[0].resolution = 0.0018; // 度數/脈衝
		axisData[1].resolution = 0.0018;
		axisData[2].resolution = 0.0025;

		double relDistance = axisData[i].mSetValue - axisData[i].mActValue;

		// 	calculate relative increment
		if (relDistance != 0)
		{

			axisData[i].relInc = (int)(relDistance / axisData[i].resolution);

			// ================== remain value ================== //
			axisData[i].remainValue += ( relDistance - axisData[i].relInc * axisData[i].resolution);
			// remainValue > 0 && resolution <= remainValue
			if( !( axisData[i].resolution > axisData[i].remainValue ) )
			{
			axisData[i].relInc++;
			axisData[i].remainValue -= axisData[i].resolution;
			}
			// remainValue < 0 && resolution <= (-1)*remainValue
			else if(  !( axisData[i].resolution > (-1)*axisData[i].remainValue ) )
			{
			axisData[i].relInc--;
			axisData[i].remainValue += axisData[i].resolution;
			}
			// ================================================== //

		}
		else 
			axisData[i].relInc = 0;

	}//end for

///////////////////////////////////////////////////////////////////
// realTimer	
	// output
	for (i = 0 ; i < 3 ; ++i)
	{
		// send to motion card when we use HD_TIMER
#if HD_TIMER
		putAxisValue(i,axisData[i].relInc);
#endif
		axisData[i].mActValue = axisData[i].mSetValue; //後一刻位置變成前一刻位置

	}//end for
	//******************************************

		return 0;
}
//**********************************************
// Real timer function
//**********************************************
#if HD_TIMER
void _stdcall Timer_ISR_Function(LIOINT *pstINTSource)
{

		realKnl();
		intpMain( intpDataPtr );


}
#endif





namespace blake {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 的摘要
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
	private: System::Windows::Forms::RichTextBox^  richTextBox_ncFile;
	protected: 
	private: System::Windows::Forms::Button^  button_openFile;
	private: System::Windows::Forms::TextBox^  textBox_filePath;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog_openFile;
	private: System::Windows::Forms::Button^  button_xp;
	private: System::Windows::Forms::Button^  button_xn;
	private: System::Windows::Forms::TrackBar^  trackBar_feedOverride;
	private: System::Windows::Forms::Label^  label_feedOverride;

	private: System::Windows::Forms::Timer^  timer_real;
	private: System::Windows::Forms::Button^  button_yp;
	private: System::Windows::Forms::Button^  button_yn;
	private: System::Windows::Forms::Button^  button_zp;
	private: System::Windows::Forms::Button^  button_zn;
	private: System::Windows::Forms::Button^  button_mem;
	private: System::Windows::Forms::Button^  button_mdi;
	private: System::Windows::Forms::Button^  button_jog;
	private: System::Windows::Forms::Button^  button_home;
	private: System::Windows::Forms::Button^  button_wheel;
	private: System::Windows::Forms::Button^  button_teach;










	private: System::Windows::Forms::Button^  button_emergency;


	private: System::Windows::Forms::Button^  button_reset;
	private: System::Windows::Forms::Button^  button_cyclestart;
	private: System::Windows::Forms::Button^  button_x1;
	private: System::Windows::Forms::Button^  UVW_Transform;






	private: System::Windows::Forms::Button^  button_x10;
	private: System::Windows::Forms::Button^  button_hold;



	private: System::Windows::Forms::Button^  button_x100;
	private: System::Windows::Forms::Button^  button_bhk;


	private: System::Windows::Forms::Button^  button_record;



	private: System::Windows::Forms::Button^  button_teachin;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Label^  label_feed;

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::Panel^  panel5;
	private: System::Windows::Forms::Panel^  panel6;
	private: System::Windows::Forms::Panel^  panel7;
	private: System::Windows::Forms::Panel^  panel8;
	private: System::Windows::Forms::Panel^  panel9;
	private: System::Windows::Forms::Panel^  panel10;
	private: System::Windows::Forms::Panel^  panel11;
	private: System::Windows::Forms::Panel^  panel12;
	private: System::Windows::Forms::Panel^  panel15;

	private: System::Windows::Forms::Panel^  panel14;

	private: System::Windows::Forms::Panel^  panel13;

	private: System::Windows::Forms::Panel^  panel18;

	private: System::Windows::Forms::Panel^  panel17;

	private: System::Windows::Forms::Panel^  panel16;

	private: System::Windows::Forms::Panel^  panel19;
	private: System::Windows::Forms::Label^  label_x;
	private: System::Windows::Forms::Label^  label_y;
	private: System::Windows::Forms::Label^  label_z;
	private: System::Windows::Forms::Label^  label_u;
	private: System::Windows::Forms::Label^  label_v;
	private: System::Windows::Forms::Label^  label_w;
	private: System::Windows::Forms::Timer^  timer_nonReal;
private: System::Windows::Forms::PictureBox^  pictureBox2;
private: System::Windows::Forms::TextBox^  textBox_posZ;
private: System::Windows::Forms::TextBox^  textBox_posY;
private: System::Windows::Forms::TextBox^  textBox_posX;
private: System::Windows::Forms::TextBox^  textBox_posW;
private: System::Windows::Forms::TextBox^  textBox_posV;
private: System::Windows::Forms::TextBox^  textBox_posU;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Label^  labelUp;
private: System::Windows::Forms::Label^  labelUn;
private: System::Windows::Forms::Label^  labelVn;



private: System::Windows::Forms::Label^  labelVp;
private: System::Windows::Forms::Label^  labelWp;
private: System::Windows::Forms::Label^  labelWn;



private: System::Windows::Forms::Label^  labelXn;

private: System::Windows::Forms::Label^  labelXp;
private: System::Windows::Forms::Label^  labelYp;
private: System::Windows::Forms::Label^  labelYn;
private: System::Windows::Forms::Label^  labelZn;




private: System::Windows::Forms::Label^  labelZp;


private: System::Windows::Forms::Label^  M00;
private: System::Windows::Forms::Panel^  panel20;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  label18;
private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Label^  label20;














	protected: 
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->richTextBox_ncFile = (gcnew System::Windows::Forms::RichTextBox());
			this->button_openFile = (gcnew System::Windows::Forms::Button());
			this->textBox_filePath = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog_openFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button_xp = (gcnew System::Windows::Forms::Button());
			this->button_xn = (gcnew System::Windows::Forms::Button());
			this->trackBar_feedOverride = (gcnew System::Windows::Forms::TrackBar());
			this->label_feedOverride = (gcnew System::Windows::Forms::Label());
			this->timer_real = (gcnew System::Windows::Forms::Timer(this->components));
			this->button_yp = (gcnew System::Windows::Forms::Button());
			this->button_yn = (gcnew System::Windows::Forms::Button());
			this->button_zp = (gcnew System::Windows::Forms::Button());
			this->button_zn = (gcnew System::Windows::Forms::Button());
			this->button_mem = (gcnew System::Windows::Forms::Button());
			this->button_mdi = (gcnew System::Windows::Forms::Button());
			this->button_jog = (gcnew System::Windows::Forms::Button());
			this->button_home = (gcnew System::Windows::Forms::Button());
			this->button_wheel = (gcnew System::Windows::Forms::Button());
			this->button_teach = (gcnew System::Windows::Forms::Button());
			this->button_emergency = (gcnew System::Windows::Forms::Button());
			this->button_reset = (gcnew System::Windows::Forms::Button());
			this->button_cyclestart = (gcnew System::Windows::Forms::Button());
			this->button_x1 = (gcnew System::Windows::Forms::Button());
			this->UVW_Transform = (gcnew System::Windows::Forms::Button());
			this->button_x10 = (gcnew System::Windows::Forms::Button());
			this->button_hold = (gcnew System::Windows::Forms::Button());
			this->button_x100 = (gcnew System::Windows::Forms::Button());
			this->button_bhk = (gcnew System::Windows::Forms::Button());
			this->button_record = (gcnew System::Windows::Forms::Button());
			this->button_teachin = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->labelUp = (gcnew System::Windows::Forms::Label());
			this->labelUn = (gcnew System::Windows::Forms::Label());
			this->labelVn = (gcnew System::Windows::Forms::Label());
			this->labelVp = (gcnew System::Windows::Forms::Label());
			this->labelWp = (gcnew System::Windows::Forms::Label());
			this->labelWn = (gcnew System::Windows::Forms::Label());
			this->labelXn = (gcnew System::Windows::Forms::Label());
			this->labelXp = (gcnew System::Windows::Forms::Label());
			this->labelYp = (gcnew System::Windows::Forms::Label());
			this->labelYn = (gcnew System::Windows::Forms::Label());
			this->labelZn = (gcnew System::Windows::Forms::Label());
			this->labelZp = (gcnew System::Windows::Forms::Label());
			this->M00 = (gcnew System::Windows::Forms::Label());
			this->label_feed = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label_x = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label_y = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label_z = (gcnew System::Windows::Forms::Label());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->label_u = (gcnew System::Windows::Forms::Label());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->label_v = (gcnew System::Windows::Forms::Label());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->label_w = (gcnew System::Windows::Forms::Label());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->panel15 = (gcnew System::Windows::Forms::Panel());
			this->textBox_posZ = (gcnew System::Windows::Forms::TextBox());
			this->panel14 = (gcnew System::Windows::Forms::Panel());
			this->textBox_posY = (gcnew System::Windows::Forms::TextBox());
			this->panel13 = (gcnew System::Windows::Forms::Panel());
			this->textBox_posX = (gcnew System::Windows::Forms::TextBox());
			this->panel8 = (gcnew System::Windows::Forms::Panel());
			this->panel18 = (gcnew System::Windows::Forms::Panel());
			this->textBox_posW = (gcnew System::Windows::Forms::TextBox());
			this->panel17 = (gcnew System::Windows::Forms::Panel());
			this->textBox_posV = (gcnew System::Windows::Forms::TextBox());
			this->panel16 = (gcnew System::Windows::Forms::Panel());
			this->textBox_posU = (gcnew System::Windows::Forms::TextBox());
			this->panel9 = (gcnew System::Windows::Forms::Panel());
			this->panel10 = (gcnew System::Windows::Forms::Panel());
			this->panel11 = (gcnew System::Windows::Forms::Panel());
			this->panel12 = (gcnew System::Windows::Forms::Panel());
			this->panel19 = (gcnew System::Windows::Forms::Panel());
			this->timer_nonReal = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->panel20 = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_feedOverride))->BeginInit();
			this->tableLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->panel5->SuspendLayout();
			this->panel6->SuspendLayout();
			this->panel7->SuspendLayout();
			this->panel15->SuspendLayout();
			this->panel14->SuspendLayout();
			this->panel13->SuspendLayout();
			this->panel8->SuspendLayout();
			this->panel18->SuspendLayout();
			this->panel17->SuspendLayout();
			this->panel16->SuspendLayout();
			this->panel9->SuspendLayout();
			this->panel10->SuspendLayout();
			this->panel11->SuspendLayout();
			this->panel12->SuspendLayout();
			this->panel19->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			this->panel20->SuspendLayout();
			this->SuspendLayout();
			// 
			// richTextBox_ncFile
			// 
			this->richTextBox_ncFile->Location = System::Drawing::Point(436, 123);
			this->richTextBox_ncFile->Name = L"richTextBox_ncFile";
			this->richTextBox_ncFile->Size = System::Drawing::Size(385, 150);
			this->richTextBox_ncFile->TabIndex = 0;
			this->richTextBox_ncFile->Text = L"";
			this->richTextBox_ncFile->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox_ncFile_TextChanged);
			// 
			// button_openFile
			// 
			this->button_openFile->BackColor = System::Drawing::Color::OliveDrab;
			this->button_openFile->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_openFile->Location = System::Drawing::Point(441, 283);
			this->button_openFile->Name = L"button_openFile";
			this->button_openFile->Size = System::Drawing::Size(44, 27);
			this->button_openFile->TabIndex = 1;
			this->button_openFile->Text = L"開檔";
			this->button_openFile->UseVisualStyleBackColor = false;
			this->button_openFile->Click += gcnew System::EventHandler(this, &Form1::button_openFile_Click);
			// 
			// textBox_filePath
			// 
			this->textBox_filePath->Location = System::Drawing::Point(494, 287);
			this->textBox_filePath->Name = L"textBox_filePath";
			this->textBox_filePath->Size = System::Drawing::Size(324, 22);
			this->textBox_filePath->TabIndex = 2;
			// 
			// openFileDialog_openFile
			// 
			this->openFileDialog_openFile->FileName = L"openFileDialog1";
			// 
			// button_xp
			// 
			this->button_xp->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_xp->Location = System::Drawing::Point(4, 6);
			this->button_xp->Name = L"button_xp";
			this->button_xp->Size = System::Drawing::Size(53, 36);
			this->button_xp->TabIndex = 3;
			this->button_xp->Text = L"X+";
			this->button_xp->UseVisualStyleBackColor = true;
			this->button_xp->Click += gcnew System::EventHandler(this, &Form1::button_xp_Click);
			// 
			// button_xn
			// 
			this->button_xn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_xn->Location = System::Drawing::Point(60, 6);
			this->button_xn->Name = L"button_xn";
			this->button_xn->Size = System::Drawing::Size(50, 36);
			this->button_xn->TabIndex = 4;
			this->button_xn->Text = L"X-";
			this->button_xn->UseVisualStyleBackColor = true;
			this->button_xn->Click += gcnew System::EventHandler(this, &Form1::button_xn_Click);
			// 
			// trackBar_feedOverride
			// 
			this->trackBar_feedOverride->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->trackBar_feedOverride->Location = System::Drawing::Point(28, 26);
			this->trackBar_feedOverride->Maximum = 200;
			this->trackBar_feedOverride->Name = L"trackBar_feedOverride";
			this->trackBar_feedOverride->Size = System::Drawing::Size(158, 45);
			this->trackBar_feedOverride->TabIndex = 5;
			this->trackBar_feedOverride->TickFrequency = 10;
			this->trackBar_feedOverride->Scroll += gcnew System::EventHandler(this, &Form1::trackBar_feedOverride_Scroll);
			// 
			// label_feedOverride
			// 
			this->label_feedOverride->AutoSize = true;
			this->label_feedOverride->ForeColor = System::Drawing::Color::Purple;
			this->label_feedOverride->Location = System::Drawing::Point(155, 12);
			this->label_feedOverride->Name = L"label_feedOverride";
			this->label_feedOverride->Size = System::Drawing::Size(20, 12);
			this->label_feedOverride->TabIndex = 6;
			this->label_feedOverride->Text = L"0%";
			this->label_feedOverride->Click += gcnew System::EventHandler(this, &Form1::label_feedOverride_Click);
			// 
			// timer_real
			// 
			this->timer_real->Enabled = true;
			this->timer_real->Interval = 1;
			this->timer_real->Tick += gcnew System::EventHandler(this, &Form1::timer_real_Tick);
			// 
			// button_yp
			// 
			this->button_yp->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_yp->Location = System::Drawing::Point(4, 56);
			this->button_yp->Name = L"button_yp";
			this->button_yp->Size = System::Drawing::Size(53, 35);
			this->button_yp->TabIndex = 8;
			this->button_yp->Text = L"Y+";
			this->button_yp->UseVisualStyleBackColor = true;
			this->button_yp->Click += gcnew System::EventHandler(this, &Form1::button_yp_Click);
			// 
			// button_yn
			// 
			this->button_yn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_yn->Location = System::Drawing::Point(60, 56);
			this->button_yn->Name = L"button_yn";
			this->button_yn->Size = System::Drawing::Size(50, 34);
			this->button_yn->TabIndex = 9;
			this->button_yn->Text = L"Y-";
			this->button_yn->UseVisualStyleBackColor = true;
			this->button_yn->Click += gcnew System::EventHandler(this, &Form1::button_yn_Click);
			// 
			// button_zp
			// 
			this->button_zp->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_zp->Location = System::Drawing::Point(4, 99);
			this->button_zp->Name = L"button_zp";
			this->button_zp->Size = System::Drawing::Size(53, 35);
			this->button_zp->TabIndex = 10;
			this->button_zp->Text = L"Z+";
			this->button_zp->UseVisualStyleBackColor = true;
			this->button_zp->Click += gcnew System::EventHandler(this, &Form1::button_zp_Click);
			// 
			// button_zn
			// 
			this->button_zn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_zn->Location = System::Drawing::Point(60, 101);
			this->button_zn->Name = L"button_zn";
			this->button_zn->Size = System::Drawing::Size(50, 33);
			this->button_zn->TabIndex = 11;
			this->button_zn->Text = L"Z-";
			this->button_zn->UseVisualStyleBackColor = true;
			this->button_zn->Click += gcnew System::EventHandler(this, &Form1::button_zn_Click);
			// 
			// button_mem
			// 
			this->button_mem->BackColor = System::Drawing::Color::SteelBlue;
			this->button_mem->CausesValidation = false;
			this->button_mem->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_mem->ForeColor = System::Drawing::Color::Purple;
			this->button_mem->ImageKey = L"(無)";
			this->button_mem->Location = System::Drawing::Point(8, 5);
			this->button_mem->Name = L"button_mem";
			this->button_mem->Size = System::Drawing::Size(68, 63);
			this->button_mem->TabIndex = 12;
			this->button_mem->Text = L"MEM";
			this->button_mem->UseVisualStyleBackColor = false;
			this->button_mem->Click += gcnew System::EventHandler(this, &Form1::button_mem_Click);
			// 
			// button_mdi
			// 
			this->button_mdi->BackColor = System::Drawing::Color::SteelBlue;
			this->button_mdi->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_mdi->ForeColor = System::Drawing::Color::Purple;
			this->button_mdi->Location = System::Drawing::Point(82, 5);
			this->button_mdi->Name = L"button_mdi";
			this->button_mdi->Size = System::Drawing::Size(69, 63);
			this->button_mdi->TabIndex = 13;
			this->button_mdi->Text = L"MDI";
			this->button_mdi->UseVisualStyleBackColor = false;
			this->button_mdi->Click += gcnew System::EventHandler(this, &Form1::button_mdi_Click);
			// 
			// button_jog
			// 
			this->button_jog->BackColor = System::Drawing::Color::SteelBlue;
			this->button_jog->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_jog->ForeColor = System::Drawing::Color::Purple;
			this->button_jog->Location = System::Drawing::Point(157, 5);
			this->button_jog->Name = L"button_jog";
			this->button_jog->Size = System::Drawing::Size(70, 63);
			this->button_jog->TabIndex = 14;
			this->button_jog->Text = L"JOG";
			this->button_jog->UseVisualStyleBackColor = false;
			this->button_jog->Click += gcnew System::EventHandler(this, &Form1::button_jog_Click);
			// 
			// button_home
			// 
			this->button_home->BackColor = System::Drawing::Color::SteelBlue;
			this->button_home->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_home->ForeColor = System::Drawing::Color::Purple;
			this->button_home->Location = System::Drawing::Point(233, 5);
			this->button_home->Name = L"button_home";
			this->button_home->Size = System::Drawing::Size(64, 63);
			this->button_home->TabIndex = 15;
			this->button_home->Text = L"HOME";
			this->button_home->UseVisualStyleBackColor = false;
			this->button_home->Click += gcnew System::EventHandler(this, &Form1::button_home_Click);
			// 
			// button_wheel
			// 
			this->button_wheel->BackColor = System::Drawing::Color::SteelBlue;
			this->button_wheel->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_wheel->ForeColor = System::Drawing::Color::Purple;
			this->button_wheel->Location = System::Drawing::Point(303, 5);
			this->button_wheel->Name = L"button_wheel";
			this->button_wheel->Size = System::Drawing::Size(66, 63);
			this->button_wheel->TabIndex = 16;
			this->button_wheel->Text = L"Wheel";
			this->button_wheel->UseVisualStyleBackColor = false;
			this->button_wheel->Click += gcnew System::EventHandler(this, &Form1::button_wheel_Click);
			// 
			// button_teach
			// 
			this->button_teach->BackColor = System::Drawing::Color::SteelBlue;
			this->button_teach->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_teach->ForeColor = System::Drawing::Color::Purple;
			this->button_teach->Location = System::Drawing::Point(375, 5);
			this->button_teach->Name = L"button_teach";
			this->button_teach->Size = System::Drawing::Size(65, 63);
			this->button_teach->TabIndex = 17;
			this->button_teach->Text = L"Teach";
			this->button_teach->UseVisualStyleBackColor = false;
			this->button_teach->Click += gcnew System::EventHandler(this, &Form1::button_teach_Click);
			// 
			// button_emergency
			// 
			this->button_emergency->BackColor = System::Drawing::Color::Red;
			this->button_emergency->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_emergency->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->button_emergency->Location = System::Drawing::Point(3, 12);
			this->button_emergency->Name = L"button_emergency";
			this->button_emergency->Size = System::Drawing::Size(155, 88);
			this->button_emergency->TabIndex = 18;
			this->button_emergency->Text = L"Emergency Stop";
			this->button_emergency->UseVisualStyleBackColor = false;
			this->button_emergency->Click += gcnew System::EventHandler(this, &Form1::button_emergency_Click);
			// 
			// button_reset
			// 
			this->button_reset->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button_reset->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_reset->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_reset->Location = System::Drawing::Point(19, 76);
			this->button_reset->Name = L"button_reset";
			this->button_reset->Size = System::Drawing::Size(75, 58);
			this->button_reset->TabIndex = 19;
			this->button_reset->Text = L"Reset";
			this->button_reset->UseVisualStyleBackColor = false;
			this->button_reset->Click += gcnew System::EventHandler(this, &Form1::button_reset_Click);
			// 
			// button_cyclestart
			// 
			this->button_cyclestart->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button_cyclestart->Font = (gcnew System::Drawing::Font(L"Dutch801 XBd BT", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_cyclestart->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_cyclestart->Location = System::Drawing::Point(100, 76);
			this->button_cyclestart->Name = L"button_cyclestart";
			this->button_cyclestart->Size = System::Drawing::Size(79, 59);
			this->button_cyclestart->TabIndex = 20;
			this->button_cyclestart->Text = L"Cycle Start";
			this->button_cyclestart->UseVisualStyleBackColor = false;
			this->button_cyclestart->Click += gcnew System::EventHandler(this, &Form1::button_cyclestart_Click);
			// 
			// button_x1
			// 
			this->button_x1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_x1->Location = System::Drawing::Point(12, 6);
			this->button_x1->Name = L"button_x1";
			this->button_x1->Size = System::Drawing::Size(54, 35);
			this->button_x1->TabIndex = 21;
			this->button_x1->Text = L"X1";
			this->button_x1->UseVisualStyleBackColor = true;
			this->button_x1->Click += gcnew System::EventHandler(this, &Form1::button_x1_Click);
			// 
			// UVW_Transform
			// 
			this->UVW_Transform->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->UVW_Transform->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->UVW_Transform->Location = System::Drawing::Point(73, 5);
			this->UVW_Transform->Name = L"UVW_Transform";
			this->UVW_Transform->Size = System::Drawing::Size(54, 36);
			this->UVW_Transform->TabIndex = 22;
			this->UVW_Transform->Text = L"UVW";
			this->UVW_Transform->UseVisualStyleBackColor = false;
			this->UVW_Transform->Click += gcnew System::EventHandler(this, &Form1::UVW_Transform_Click);
			// 
			// button_x10
			// 
			this->button_x10->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_x10->Location = System::Drawing::Point(13, 51);
			this->button_x10->Name = L"button_x10";
			this->button_x10->Size = System::Drawing::Size(54, 35);
			this->button_x10->TabIndex = 23;
			this->button_x10->Text = L"X10";
			this->button_x10->UseVisualStyleBackColor = true;
			this->button_x10->Click += gcnew System::EventHandler(this, &Form1::button_x10_Click);
			// 
			// button_hold
			// 
			this->button_hold->BackColor = System::Drawing::Color::Transparent;
			this->button_hold->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_hold->Location = System::Drawing::Point(73, 51);
			this->button_hold->Name = L"button_hold";
			this->button_hold->Size = System::Drawing::Size(54, 35);
			this->button_hold->TabIndex = 24;
			this->button_hold->Text = L"FH";
			this->button_hold->UseVisualStyleBackColor = false;
			this->button_hold->Click += gcnew System::EventHandler(this, &Form1::button_fh_Click);
			// 
			// button_x100
			// 
			this->button_x100->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_x100->Location = System::Drawing::Point(13, 100);
			this->button_x100->Name = L"button_x100";
			this->button_x100->Size = System::Drawing::Size(54, 34);
			this->button_x100->TabIndex = 25;
			this->button_x100->Text = L"X100";
			this->button_x100->UseVisualStyleBackColor = true;
			this->button_x100->Click += gcnew System::EventHandler(this, &Form1::button_x100_Click);
			// 
			// button_bhk
			// 
			this->button_bhk->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button_bhk->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_bhk->Location = System::Drawing::Point(73, 99);
			this->button_bhk->Name = L"button_bhk";
			this->button_bhk->Size = System::Drawing::Size(54, 34);
			this->button_bhk->TabIndex = 26;
			this->button_bhk->Text = L"BLK";
			this->button_bhk->UseVisualStyleBackColor = false;
			// 
			// button_record
			// 
			this->button_record->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->button_record->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button_record->Location = System::Drawing::Point(5, 12);
			this->button_record->Name = L"button_record";
			this->button_record->Size = System::Drawing::Size(59, 53);
			this->button_record->TabIndex = 27;
			this->button_record->Text = L"Record";
			this->button_record->UseVisualStyleBackColor = false;
			this->button_record->Click += gcnew System::EventHandler(this, &Form1::button21_Click);
			// 
			// button_teachin
			// 
			this->button_teachin->BackColor = System::Drawing::Color::Goldenrod;
			this->button_teachin->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button_teachin->Location = System::Drawing::Point(5, 78);
			this->button_teachin->Name = L"button_teachin";
			this->button_teachin->Size = System::Drawing::Size(59, 50);
			this->button_teachin->TabIndex = 27;
			this->button_teachin->Text = L"Teach in";
			this->button_teachin->UseVisualStyleBackColor = false;
			this->button_teachin->Click += gcnew System::EventHandler(this, &Form1::button20_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->BackColor = System::Drawing::Color::MediumAquamarine;
			this->tableLayoutPanel1->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::InsetDouble;
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
				9.408195F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.104704F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				8.952959F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				10.01517F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				9.559939F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				8.952959F)));
			this->tableLayoutPanel1->Controls->Add(this->label2, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->label3, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->label4, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->label5, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->labelUp, 5, 0);
			this->tableLayoutPanel1->Controls->Add(this->labelUn, 5, 1);
			this->tableLayoutPanel1->Controls->Add(this->labelVn, 6, 1);
			this->tableLayoutPanel1->Controls->Add(this->labelVp, 6, 0);
			this->tableLayoutPanel1->Controls->Add(this->labelWp, 7, 0);
			this->tableLayoutPanel1->Controls->Add(this->labelWn, 7, 1);
			this->tableLayoutPanel1->Controls->Add(this->labelXn, 8, 1);
			this->tableLayoutPanel1->Controls->Add(this->labelXp, 8, 0);
			this->tableLayoutPanel1->Controls->Add(this->labelYp, 9, 0);
			this->tableLayoutPanel1->Controls->Add(this->labelYn, 9, 1);
			this->tableLayoutPanel1->Controls->Add(this->labelZn, 10, 1);
			this->tableLayoutPanel1->Controls->Add(this->labelZp, 10, 0);
			this->tableLayoutPanel1->Controls->Add(this->M00, 0, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(159, 11);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(662, 100);
			this->tableLayoutPanel1->TabIndex = 28;
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label2->ForeColor = System::Drawing::Color::Purple;
			this->label2->Location = System::Drawing::Point(11, 66);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(40, 16);
			this->label2->TabIndex = 1;
			this->label2->Text = L"M30";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label3
			// 
			this->label3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label3->ForeColor = System::Drawing::Color::Purple;
			this->label3->Location = System::Drawing::Point(68, 17);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(43, 16);
			this->label3->TabIndex = 0;
			this->label3->Text = L"PGM";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label4
			// 
			this->label4->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label4->ForeColor = System::Drawing::Color::Purple;
			this->label4->Location = System::Drawing::Point(70, 66);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(40, 16);
			this->label4->TabIndex = 0;
			this->label4->Text = L"ERR";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label5
			// 
			this->label5->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label5->ForeColor = System::Drawing::Color::Purple;
			this->label5->Location = System::Drawing::Point(149, 17);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(0, 16);
			this->label5->TabIndex = 0;
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelUp
			// 
			this->labelUp->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelUp->AutoSize = true;
			this->labelUp->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->labelUp->ForeColor = System::Drawing::Color::Purple;
			this->labelUp->Location = System::Drawing::Point(312, 17);
			this->labelUp->Name = L"labelUp";
			this->labelUp->Size = System::Drawing::Size(29, 16);
			this->labelUp->TabIndex = 0;
			this->labelUp->Text = L"PU";
			this->labelUp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->labelUp->Click += gcnew System::EventHandler(this, &Form1::label6_Click);
			// 
			// labelUn
			// 
			this->labelUn->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelUn->AutoSize = true;
			this->labelUn->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->labelUn->ForeColor = System::Drawing::Color::Purple;
			this->labelUn->Location = System::Drawing::Point(311, 66);
			this->labelUn->Name = L"labelUn";
			this->labelUn->Size = System::Drawing::Size(32, 16);
			this->labelUn->TabIndex = 0;
			this->labelUn->Text = L"NU";
			this->labelUn->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelVn
			// 
			this->labelVn->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelVn->AutoSize = true;
			this->labelVn->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->labelVn->ForeColor = System::Drawing::Color::Purple;
			this->labelVn->Location = System::Drawing::Point(371, 66);
			this->labelVn->Name = L"labelVn";
			this->labelVn->Size = System::Drawing::Size(32, 16);
			this->labelVn->TabIndex = 0;
			this->labelVn->Text = L"NV";
			this->labelVn->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelVp
			// 
			this->labelVp->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelVp->AutoSize = true;
			this->labelVp->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->labelVp->ForeColor = System::Drawing::Color::Purple;
			this->labelVp->Location = System::Drawing::Point(372, 17);
			this->labelVp->Name = L"labelVp";
			this->labelVp->Size = System::Drawing::Size(29, 16);
			this->labelVp->TabIndex = 0;
			this->labelVp->Text = L"PV";
			this->labelVp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->labelVp->Click += gcnew System::EventHandler(this, &Form1::label9_Click);
			// 
			// labelWp
			// 
			this->labelWp->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelWp->AutoSize = true;
			this->labelWp->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->labelWp->ForeColor = System::Drawing::Color::Purple;
			this->labelWp->Location = System::Drawing::Point(429, 17);
			this->labelWp->Name = L"labelWp";
			this->labelWp->Size = System::Drawing::Size(32, 16);
			this->labelWp->TabIndex = 0;
			this->labelWp->Text = L"PW";
			this->labelWp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelWn
			// 
			this->labelWn->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelWn->AutoSize = true;
			this->labelWn->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->labelWn->ForeColor = System::Drawing::Color::Purple;
			this->labelWn->Location = System::Drawing::Point(428, 66);
			this->labelWn->Name = L"labelWn";
			this->labelWn->Size = System::Drawing::Size(35, 16);
			this->labelWn->TabIndex = 0;
			this->labelWn->Text = L"NW";
			this->labelWn->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelXn
			// 
			this->labelXn->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelXn->AutoSize = true;
			this->labelXn->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->labelXn->ForeColor = System::Drawing::Color::Purple;
			this->labelXn->Location = System::Drawing::Point(490, 66);
			this->labelXn->Name = L"labelXn";
			this->labelXn->Size = System::Drawing::Size(32, 16);
			this->labelXn->TabIndex = 0;
			this->labelXn->Text = L"NX";
			this->labelXn->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelXp
			// 
			this->labelXp->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelXp->AutoSize = true;
			this->labelXp->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->labelXp->ForeColor = System::Drawing::Color::Purple;
			this->labelXp->Location = System::Drawing::Point(492, 17);
			this->labelXp->Name = L"labelXp";
			this->labelXp->Size = System::Drawing::Size(29, 16);
			this->labelXp->TabIndex = 0;
			this->labelXp->Text = L"PX";
			this->labelXp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelYp
			// 
			this->labelYp->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelYp->AutoSize = true;
			this->labelYp->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->labelYp->Location = System::Drawing::Point(554, 17);
			this->labelYp->Name = L"labelYp";
			this->labelYp->Size = System::Drawing::Size(29, 16);
			this->labelYp->TabIndex = 0;
			this->labelYp->Text = L"PY";
			this->labelYp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelYn
			// 
			this->labelYn->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelYn->AutoSize = true;
			this->labelYn->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->labelYn->Location = System::Drawing::Point(553, 66);
			this->labelYn->Name = L"labelYn";
			this->labelYn->Size = System::Drawing::Size(32, 16);
			this->labelYn->TabIndex = 0;
			this->labelYn->Text = L"NY";
			this->labelYn->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelZn
			// 
			this->labelZn->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelZn->AutoSize = true;
			this->labelZn->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->labelZn->Location = System::Drawing::Point(615, 66);
			this->labelZn->Name = L"labelZn";
			this->labelZn->Size = System::Drawing::Size(30, 16);
			this->labelZn->TabIndex = 0;
			this->labelZn->Text = L"NZ";
			this->labelZn->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->labelZn->Click += gcnew System::EventHandler(this, &Form1::labelZn_Click);
			// 
			// labelZp
			// 
			this->labelZp->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelZp->AutoSize = true;
			this->labelZp->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->labelZp->Location = System::Drawing::Point(616, 17);
			this->labelZp->Name = L"labelZp";
			this->labelZp->Size = System::Drawing::Size(27, 16);
			this->labelZp->TabIndex = 0;
			this->labelZp->Text = L"PZ";
			this->labelZp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// M00
			// 
			this->M00->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->M00->AutoSize = true;
			this->M00->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->M00->ForeColor = System::Drawing::Color::Purple;
			this->M00->Location = System::Drawing::Point(12, 17);
			this->M00->Name = L"M00";
			this->M00->Size = System::Drawing::Size(38, 16);
			this->M00->TabIndex = 0;
			this->M00->Text = L"G04";
			this->M00->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_feed
			// 
			this->label_feed->AutoSize = true;
			this->label_feed->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_feed->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label_feed->Location = System::Drawing::Point(34, 7);
			this->label_feed->Name = L"label_feed";
			this->label_feed->Size = System::Drawing::Size(101, 19);
			this->label_feed->TabIndex = 29;
			this->label_feed->Text = L"FeedOverride";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox1->ErrorImage = nullptr;
			this->pictureBox1->ImageLocation = L"middle";
			this->pictureBox1->InitialImage = nullptr;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(141, 93);
			this->pictureBox1->TabIndex = 30;
			this->pictureBox1->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel1->Controls->Add(this->label_x);
			this->panel1->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->panel1->Location = System::Drawing::Point(18, 15);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(52, 47);
			this->panel1->TabIndex = 31;
			// 
			// label_x
			// 
			this->label_x->AutoSize = true;
			this->label_x->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_x->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label_x->Location = System::Drawing::Point(15, 13);
			this->label_x->Name = L"label_x";
			this->label_x->Size = System::Drawing::Size(20, 16);
			this->label_x->TabIndex = 0;
			this->label_x->Text = L"X";
			// 
			// panel2
			// 
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel2->Controls->Add(this->label_y);
			this->panel2->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->panel2->Location = System::Drawing::Point(18, 68);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(52, 47);
			this->panel2->TabIndex = 31;
			// 
			// label_y
			// 
			this->label_y->AutoSize = true;
			this->label_y->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_y->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label_y->Location = System::Drawing::Point(15, 12);
			this->label_y->Name = L"label_y";
			this->label_y->Size = System::Drawing::Size(20, 16);
			this->label_y->TabIndex = 0;
			this->label_y->Text = L"Y";
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel3->Controls->Add(this->label_z);
			this->panel3->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->panel3->Location = System::Drawing::Point(18, 121);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(52, 47);
			this->panel3->TabIndex = 31;
			// 
			// label_z
			// 
			this->label_z->AutoSize = true;
			this->label_z->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_z->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label_z->Location = System::Drawing::Point(17, 12);
			this->label_z->Name = L"label_z";
			this->label_z->Size = System::Drawing::Size(18, 16);
			this->label_z->TabIndex = 0;
			this->label_z->Text = L"Z";
			// 
			// panel4
			// 
			this->panel4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel4->Controls->Add(this->label_u);
			this->panel4->Location = System::Drawing::Point(14, 13);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(37, 36);
			this->panel4->TabIndex = 32;
			// 
			// label_u
			// 
			this->label_u->AutoSize = true;
			this->label_u->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_u->ForeColor = System::Drawing::Color::Crimson;
			this->label_u->Location = System::Drawing::Point(3, 8);
			this->label_u->Name = L"label_u";
			this->label_u->Size = System::Drawing::Size(23, 19);
			this->label_u->TabIndex = 0;
			this->label_u->Text = L"U";
			this->label_u->Click += gcnew System::EventHandler(this, &Form1::label_u_Click);
			// 
			// panel5
			// 
			this->panel5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel5->Controls->Add(this->label_v);
			this->panel5->Location = System::Drawing::Point(14, 57);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(37, 36);
			this->panel5->TabIndex = 32;
			// 
			// label_v
			// 
			this->label_v->AutoSize = true;
			this->label_v->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_v->ForeColor = System::Drawing::Color::Crimson;
			this->label_v->Location = System::Drawing::Point(3, 8);
			this->label_v->Name = L"label_v";
			this->label_v->Size = System::Drawing::Size(23, 19);
			this->label_v->TabIndex = 0;
			this->label_v->Text = L"V";
			// 
			// panel6
			// 
			this->panel6->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel6->Controls->Add(this->label_w);
			this->panel6->Location = System::Drawing::Point(14, 100);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(37, 36);
			this->panel6->TabIndex = 32;
			// 
			// label_w
			// 
			this->label_w->AutoSize = true;
			this->label_w->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label_w->ForeColor = System::Drawing::Color::Crimson;
			this->label_w->Location = System::Drawing::Point(3, 8);
			this->label_w->Name = L"label_w";
			this->label_w->Size = System::Drawing::Size(27, 19);
			this->label_w->TabIndex = 0;
			this->label_w->Text = L"W";
			// 
			// panel7
			// 
			this->panel7->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel7->Controls->Add(this->panel15);
			this->panel7->Controls->Add(this->panel14);
			this->panel7->Controls->Add(this->panel13);
			this->panel7->Controls->Add(this->panel1);
			this->panel7->Controls->Add(this->panel2);
			this->panel7->Controls->Add(this->panel3);
			this->panel7->Location = System::Drawing::Point(19, 135);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(372, 186);
			this->panel7->TabIndex = 33;
			this->panel7->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel7_Paint);
			// 
			// panel15
			// 
			this->panel15->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->panel15->Controls->Add(this->textBox_posZ);
			this->panel15->Location = System::Drawing::Point(118, 121);
			this->panel15->Name = L"panel15";
			this->panel15->Size = System::Drawing::Size(224, 47);
			this->panel15->TabIndex = 35;
			// 
			// textBox_posZ
			// 
			this->textBox_posZ->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox_posZ->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->textBox_posZ->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->textBox_posZ->Location = System::Drawing::Point(65, 8);
			this->textBox_posZ->Name = L"textBox_posZ";
			this->textBox_posZ->Size = System::Drawing::Size(100, 30);
			this->textBox_posZ->TabIndex = 0;
			this->textBox_posZ->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// panel14
			// 
			this->panel14->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->panel14->Controls->Add(this->textBox_posY);
			this->panel14->Location = System::Drawing::Point(118, 68);
			this->panel14->Name = L"panel14";
			this->panel14->Size = System::Drawing::Size(224, 47);
			this->panel14->TabIndex = 35;
			// 
			// textBox_posY
			// 
			this->textBox_posY->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox_posY->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->textBox_posY->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->textBox_posY->Location = System::Drawing::Point(65, 9);
			this->textBox_posY->Name = L"textBox_posY";
			this->textBox_posY->Size = System::Drawing::Size(100, 30);
			this->textBox_posY->TabIndex = 0;
			this->textBox_posY->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// panel13
			// 
			this->panel13->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->panel13->Controls->Add(this->textBox_posX);
			this->panel13->Location = System::Drawing::Point(118, 15);
			this->panel13->Name = L"panel13";
			this->panel13->Size = System::Drawing::Size(224, 47);
			this->panel13->TabIndex = 35;
			// 
			// textBox_posX
			// 
			this->textBox_posX->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox_posX->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->textBox_posX->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->textBox_posX->Location = System::Drawing::Point(65, 8);
			this->textBox_posX->Name = L"textBox_posX";
			this->textBox_posX->Size = System::Drawing::Size(100, 30);
			this->textBox_posX->TabIndex = 0;
			this->textBox_posX->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// panel8
			// 
			this->panel8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel8->Controls->Add(this->panel18);
			this->panel8->Controls->Add(this->panel17);
			this->panel8->Controls->Add(this->panel16);
			this->panel8->Controls->Add(this->panel4);
			this->panel8->Controls->Add(this->panel5);
			this->panel8->Controls->Add(this->panel6);
			this->panel8->Location = System::Drawing::Point(19, 351);
			this->panel8->Name = L"panel8";
			this->panel8->Size = System::Drawing::Size(211, 146);
			this->panel8->TabIndex = 34;
			this->panel8->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel8_Paint);
			// 
			// panel18
			// 
			this->panel18->BackColor = System::Drawing::Color::Coral;
			this->panel18->Controls->Add(this->textBox_posW);
			this->panel18->Location = System::Drawing::Point(57, 100);
			this->panel18->Name = L"panel18";
			this->panel18->Size = System::Drawing::Size(128, 39);
			this->panel18->TabIndex = 33;
			// 
			// textBox_posW
			// 
			this->textBox_posW->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox_posW->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->textBox_posW->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->textBox_posW->Location = System::Drawing::Point(12, 6);
			this->textBox_posW->Name = L"textBox_posW";
			this->textBox_posW->Size = System::Drawing::Size(100, 30);
			this->textBox_posW->TabIndex = 0;
			this->textBox_posW->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// panel17
			// 
			this->panel17->BackColor = System::Drawing::Color::Coral;
			this->panel17->Controls->Add(this->textBox_posV);
			this->panel17->Location = System::Drawing::Point(58, 57);
			this->panel17->Name = L"panel17";
			this->panel17->Size = System::Drawing::Size(127, 37);
			this->panel17->TabIndex = 33;
			// 
			// textBox_posV
			// 
			this->textBox_posV->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox_posV->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->textBox_posV->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->textBox_posV->Location = System::Drawing::Point(11, 3);
			this->textBox_posV->Name = L"textBox_posV";
			this->textBox_posV->Size = System::Drawing::Size(100, 30);
			this->textBox_posV->TabIndex = 0;
			this->textBox_posV->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// panel16
			// 
			this->panel16->BackColor = System::Drawing::Color::Coral;
			this->panel16->Controls->Add(this->textBox_posU);
			this->panel16->Location = System::Drawing::Point(58, 5);
			this->panel16->Name = L"panel16";
			this->panel16->Size = System::Drawing::Size(127, 46);
			this->panel16->TabIndex = 33;
			// 
			// textBox_posU
			// 
			this->textBox_posU->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox_posU->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->textBox_posU->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->textBox_posU->Location = System::Drawing::Point(12, 8);
			this->textBox_posU->Name = L"textBox_posU";
			this->textBox_posU->Size = System::Drawing::Size(100, 30);
			this->textBox_posU->TabIndex = 0;
			this->textBox_posU->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// panel9
			// 
			this->panel9->BackColor = System::Drawing::Color::LightGreen;
			this->panel9->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel9->Controls->Add(this->button_x1);
			this->panel9->Controls->Add(this->UVW_Transform);
			this->panel9->Controls->Add(this->button_x10);
			this->panel9->Controls->Add(this->button_hold);
			this->panel9->Controls->Add(this->button_x100);
			this->panel9->Controls->Add(this->button_bhk);
			this->panel9->Location = System::Drawing::Point(441, 351);
			this->panel9->Name = L"panel9";
			this->panel9->Size = System::Drawing::Size(142, 147);
			this->panel9->TabIndex = 32;
			// 
			// panel10
			// 
			this->panel10->BackColor = System::Drawing::Color::LightGreen;
			this->panel10->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel10->Controls->Add(this->button_zn);
			this->panel10->Controls->Add(this->button_zp);
			this->panel10->Controls->Add(this->button_yn);
			this->panel10->Controls->Add(this->button_yp);
			this->panel10->Controls->Add(this->button_xn);
			this->panel10->Controls->Add(this->button_xp);
			this->panel10->Location = System::Drawing::Point(322, 351);
			this->panel10->Name = L"panel10";
			this->panel10->Size = System::Drawing::Size(113, 147);
			this->panel10->TabIndex = 35;
			// 
			// panel11
			// 
			this->panel11->BackColor = System::Drawing::Color::LightGreen;
			this->panel11->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel11->Controls->Add(this->button_teachin);
			this->panel11->Controls->Add(this->button_record);
			this->panel11->Location = System::Drawing::Point(247, 351);
			this->panel11->Name = L"panel11";
			this->panel11->Size = System::Drawing::Size(69, 147);
			this->panel11->TabIndex = 32;
			// 
			// panel12
			// 
			this->panel12->BackColor = System::Drawing::Color::CadetBlue;
			this->panel12->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->panel12->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel12->Controls->Add(this->label_feed);
			this->panel12->Controls->Add(this->button_cyclestart);
			this->panel12->Controls->Add(this->button_reset);
			this->panel12->Controls->Add(this->label_feedOverride);
			this->panel12->Controls->Add(this->trackBar_feedOverride);
			this->panel12->Location = System::Drawing::Point(616, 323);
			this->panel12->Name = L"panel12";
			this->panel12->Size = System::Drawing::Size(202, 157);
			this->panel12->TabIndex = 36;
			// 
			// panel19
			// 
			this->panel19->BackColor = System::Drawing::Color::DodgerBlue;
			this->panel19->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel19->Controls->Add(this->button_emergency);
			this->panel19->Location = System::Drawing::Point(637, 486);
			this->panel19->Name = L"panel19";
			this->panel19->Size = System::Drawing::Size(167, 115);
			this->panel19->TabIndex = 37;
			// 
			// timer_nonReal
			// 
			this->timer_nonReal->Enabled = true;
			this->timer_nonReal->Interval = 20;
			this->timer_nonReal->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox2->ErrorImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.ErrorImage")));
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->InitialImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.InitialImage")));
			this->pictureBox2->Location = System::Drawing::Point(12, 11);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(140, 94);
			this->pictureBox2->TabIndex = 38;
			this->pictureBox2->TabStop = false;
			// 
			// panel20
			// 
			this->panel20->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel20->Controls->Add(this->button_mem);
			this->panel20->Controls->Add(this->button_mdi);
			this->panel20->Controls->Add(this->button_jog);
			this->panel20->Controls->Add(this->button_home);
			this->panel20->Controls->Add(this->button_wheel);
			this->panel20->Controls->Add(this->button_teach);
			this->panel20->Location = System::Drawing::Point(106, 509);
			this->panel20->Name = L"panel20";
			this->panel20->Size = System::Drawing::Size(451, 81);
			this->panel20->TabIndex = 39;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label1->Font = (gcnew System::Drawing::Font(L"標楷體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(141, 114);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(118, 18);
			this->label1->TabIndex = 40;
			this->label1->Text = L"XYZ Position";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label18->Font = (gcnew System::Drawing::Font(L"標楷體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label18->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label18->Location = System::Drawing::Point(61, 329);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(118, 18);
			this->label18->TabIndex = 40;
			this->label18->Text = L"UVW Position";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label19->Font = (gcnew System::Drawing::Font(L"標楷體", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label19->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label19->Location = System::Drawing::Point(341, 323);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(96, 23);
			this->label19->TabIndex = 40;
			this->label19->Text = L"Buttons";
			this->label19->Click += gcnew System::EventHandler(this, &Form1::label19_Click);
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label20->Font = (gcnew System::Drawing::Font(L"Cataneo BT", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label20->ForeColor = System::Drawing::Color::Green;
			this->label20->Location = System::Drawing::Point(7, 538);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(95, 34);
			this->label20->TabIndex = 41;
			this->label20->Text = L"MODE:";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(838, 610);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel20);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->panel19);
			this->Controls->Add(this->panel12);
			this->Controls->Add(this->panel11);
			this->Controls->Add(this->panel10);
			this->Controls->Add(this->panel9);
			this->Controls->Add(this->panel8);
			this->Controls->Add(this->panel7);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->textBox_filePath);
			this->Controls->Add(this->button_openFile);
			this->Controls->Add(this->richTextBox_ncFile);
			this->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->ForeColor = System::Drawing::Color::Purple;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Form1::Form1_FormClosed);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_feedOverride))->EndInit();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->panel6->ResumeLayout(false);
			this->panel6->PerformLayout();
			this->panel7->ResumeLayout(false);
			this->panel15->ResumeLayout(false);
			this->panel15->PerformLayout();
			this->panel14->ResumeLayout(false);
			this->panel14->PerformLayout();
			this->panel13->ResumeLayout(false);
			this->panel13->PerformLayout();
			this->panel8->ResumeLayout(false);
			this->panel18->ResumeLayout(false);
			this->panel18->PerformLayout();
			this->panel17->ResumeLayout(false);
			this->panel17->PerformLayout();
			this->panel16->ResumeLayout(false);
			this->panel16->PerformLayout();
			this->panel9->ResumeLayout(false);
			this->panel10->ResumeLayout(false);
			this->panel11->ResumeLayout(false);
			this->panel12->ResumeLayout(false);
			this->panel12->PerformLayout();
			this->panel19->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			this->panel20->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void notifyIcon1_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 }

/*********************************** 開檔 **************************************/
	private: System::Void button_openFile_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (mmiDataPtr->opMode == MEM_MODE)
				 {

					 openFileDialog_openFile->InitialDirectory = "";    //檔案開啟的預設路徑 "
					 openFileDialog_openFile->Filter = "文字檔(*.txt)|*.txt|所有檔案(*.*)|*.*";

					 openFileDialog_openFile->FilterIndex = 2;		    //預設Filter的篩選條件
					 openFileDialog_openFile->DefaultExt = ".txt";	    //預設為文字檔
					 openFileDialog_openFile->FileName = "";		    //清除檔案路徑的字串
					 openFileDialog_openFile->RestoreDirectory = true;  //指定上一次開啟的路徑

					 if (openFileDialog_openFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
					 {
						 //把openFileDialog取得的檔案路徑，傳到螢幕上textBox顯示
						 textBox_filePath->Text = openFileDialog_openFile->FileName; 
						 //把openFileDialog取得的檔案內容，傳到螢幕上richTextBox顯示
						 richTextBox_ncFile->LoadFile(openFileDialog_openFile->FileName,RichTextBoxStreamType::PlainText);

						 pin_ptr<const wchar_t> wch = PtrToStringChars(openFileDialog_openFile->FileName);
						 size_t convertedChars = 0;
						 size_t sizeInBytes = ((openFileDialog_openFile->FileName->Length + 1)*2);
						 errno_t err = 0;
						 err = wcstombs_s(&convertedChars,mmiDataPtr->filename,sizeInBytes,wch,sizeInBytes);


						  strcpy( sysDataPtr->filename, mmiDataPtr->filename );		//將路徑檔名複製至資料交換區
						  mmiDataPtr->fileValid = true;											//檔案已打開
					 }
				 }
				 else
				 {
					 MessageBox::Show("請選擇MEM MODE","模式錯誤",MessageBoxButtons::OK, MessageBoxIcon::Warning);
				 }
			 }
/**********************************************************************************************/

/****************************** Form Load*****************************************/
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 
				 cncDataPtr = &cncData;
				 mmiDataPtr = &cncData.mmiData;
				 intpDataPtr = &cncData.intpData;
				 sysLinkDataPtr = &cncData.sysLinkData;
				 decDataPtr = &cncData.decData; //initial pointer
			     sysDataPtr = &cncData.sysData;

				 button_mem-> Enabled = true;	//初始mode為MEM mode

				 initFifo( (FIFO_HEAD*) &sysLinkDataPtr->decToIntpLinkData ,F_DEC_TO_INTP_FIFO , 10);
				 intpInit(intpDataPtr);
				 decInit(decDataPtr);
				 sysInit(sysDataPtr);
				 mmiInit(mmiDataPtr);// initilize intp/dec/mmi

				 button_xp->Enabled  = false;
				 button_xn->Enabled  = false;
				 button_yp->Enabled  = false;
				 button_yn->Enabled  = false;
				 button_zp->Enabled  = false;
				 button_zn->Enabled  = false;

				 button_x1->Enabled  = false;	
				 button_x10->Enabled  = false;	
				 button_x100->Enabled  = false;

				 button_record->Enabled = false;

				 // init motion card and card timer
#if HD_TIMER
				 // init motion card
				 initMotionCard( 0.0, 0.0, 0.0, REAL_SAMPLING_TIME,Timer_ISR_Function);
				 // enable timer
				 enableHDTimer(REAL_SAMPLING_TIME);	
				 timer_real->Enabled		= false;
				 timer_nonReal->Enabled	= true;
#else
				 timer_real->Interval = REAL_SAMPLING_TIME;
				 timer_real->Enabled		= true;
				 timer_nonReal->Enabled	= true;
#endif

			 }
/**********************************************************************************/

/************************************** X+ ****************************************/

	private: System::Void button_xp_Click(System::Object^  sender, System::EventArgs^  e) {

				 //for if JOG-mode in nonreal timer

				 if( mmiDataPtr->axisButton[0] != 1 )
				 {
					 mmiDataPtr->axisButton[0] = 1;
					 mmiDataPtr->cycleStart    = true;
					 sysLinkDataPtr->mmitointp.cycleStart = true;
					 button_xp->BackColor = Color::Purple;
					 button_xn->BackColor = Color::Transparent;
					
					 if (mmiDataPtr->xyz_mode != true)
					 {
						  labelXp->BackColor = Color::Red;
					 }
					 else
					 {
						  labelUp->BackColor = Color::Red;					 
					 }
				 }
				 else
				 {
					 mmiDataPtr->axisButton[0] = 0;
					 mmiDataPtr->cycleStart    = false;
					 sysLinkDataPtr->mmitointp.cycleStart = false;
					 button_xp->BackColor = Color::Transparent;
					 if (mmiDataPtr->xyz_mode != true)
					 {
						 labelXp->BackColor = Color::Transparent;
					 }
					 else
					 {
						 labelUp->BackColor = Color::Transparent;					 
					 }
				 }
			 }
/***************************************************************************************/

/************************************** X- ****************************************/
	private: System::Void button_xn_Click(System::Object^  sender, System::EventArgs^  e) {


				 if( mmiDataPtr->axisButton[0] != -1 )
				 {
					 mmiDataPtr->axisButton[0] = -1;
					 mmiDataPtr->cycleStart    = true;
					 sysLinkDataPtr->mmitointp.cycleStart = true;
					 button_xn->BackColor = Color::Purple;
					 button_xp->BackColor = Color::Transparent;
					 if (mmiDataPtr->xyz_mode != true)
					 {
						 labelXn->BackColor = Color::Red;
					 }
					 else
					 {
						 labelUn->BackColor = Color::Red;					 
					 }
				 }
				 else
				 {
					 mmiDataPtr->axisButton[0] = 0;
					 mmiDataPtr->cycleStart    = false;
					 sysLinkDataPtr->mmitointp.cycleStart = false;
					 button_xn->BackColor = Color::Transparent;
					 if (mmiDataPtr->xyz_mode != true)
					 {
						 labelXn->BackColor = Color::Transparent;
					 }
					 else
					 {
						 labelUn->BackColor = Color::Transparent;					 
					 }
				 }
			 }
/********************************************************************************/

/************************************** Y+ ****************************************/
private: System::Void button_yp_Click(System::Object^  sender, System::EventArgs^  e) {


			 if( mmiDataPtr->axisButton[1] != 1 )
			 {
				 mmiDataPtr->axisButton[1] = 1;
				 mmiDataPtr->cycleStart    = true;
				 sysLinkDataPtr->mmitointp.cycleStart = true;
				 button_yp->BackColor = Color::Purple;
				 button_yn->BackColor = Color::Transparent;
				 if (mmiDataPtr->xyz_mode != true)
				 {
					 labelYp->BackColor = Color::Red;
				 }
				 else
				 {
					 labelVp->BackColor = Color::Red;					 
				 }
			 }
			 else
			 {
				 mmiDataPtr->axisButton[1] = 0;
				 mmiDataPtr->cycleStart    = false;
				 sysLinkDataPtr->mmitointp.cycleStart = false;
				 button_yp->BackColor = Color::Transparent;
				 if (mmiDataPtr->xyz_mode != true)
				 {
					 labelYp->BackColor = Color::Transparent;
				 }
				 else
				 {
					 labelVp->BackColor = Color::Transparent;				 
				 }
			 }
		 }
/**********************************************************************************/

/************************************** Y- ****************************************/
private: System::Void button_yn_Click(System::Object^  sender, System::EventArgs^  e) {


			 if( mmiDataPtr->axisButton[1] != -1 )
			 {
				 mmiDataPtr->axisButton[1] = -1;
				 mmiDataPtr->cycleStart    = true;
				 sysLinkDataPtr->mmitointp.cycleStart = true;
				 button_yn->BackColor = Color::Purple;
				 button_yp->BackColor = Color::Transparent;
				 if (mmiDataPtr->xyz_mode != true)
				 {
					 labelYn->BackColor = Color::Red;
				 }
				 else
				 {
					 labelVn->BackColor = Color::Red;					 
				 }
			 }
			 else
			 {
				 mmiDataPtr->axisButton[1] = 0;
				 mmiDataPtr->cycleStart    = false;
				 sysLinkDataPtr->mmitointp.cycleStart = false;
				 button_yn->BackColor = Color::Transparent;
				 if (mmiDataPtr->xyz_mode != true)
				 {
					 labelYn->BackColor = Color::Transparent;
				 }
				 else
				 {
					 labelVn->BackColor = Color::Transparent;					 
				 }
			 }
		 }
/************************************************************************************/

/************************************** Z+ ****************************************/
private: System::Void button_zp_Click(System::Object^  sender, System::EventArgs^  e) {


			 if( mmiDataPtr->axisButton[2] != 1 )
			 {
				 mmiDataPtr->axisButton[2] = 1;
				 mmiDataPtr->cycleStart    = true;
				 sysLinkDataPtr->mmitointp.cycleStart = true;
				 button_zp->BackColor = Color::Purple;
				 button_zn->BackColor = Color::Transparent;
				 if (mmiDataPtr->xyz_mode != true)
				 {
					 labelZp->BackColor = Color::Red;
				 }
				 else
				 {
					 labelWp->BackColor = Color::Red;					 
				 }
			 }
			 else
			 {
				 mmiDataPtr->axisButton[2] = 0;
				 mmiDataPtr->cycleStart    = false;
				 sysLinkDataPtr->mmitointp.cycleStart = false;
				 button_zp->BackColor = Color::Transparent;
				 if (mmiDataPtr->xyz_mode != true)
				 {
					 labelZp->BackColor = Color::Transparent;
				 }
				 else
				 {
					 labelWp->BackColor = Color::Transparent;					 
				 }
			 }
		 }
/***********************************************************************************/

/************************************** Z- ****************************************/
private: System::Void button_zn_Click(System::Object^  sender, System::EventArgs^  e) {


			 if( mmiDataPtr->axisButton[2] != -1 )
			 {
				 mmiDataPtr->axisButton[2] = -1;
				 mmiDataPtr->cycleStart    = true;
				 sysLinkDataPtr->mmitointp.cycleStart = true;
				 button_zn->BackColor = Color::Purple;
				 button_zp->BackColor = Color::Transparent;
				 if (mmiDataPtr->xyz_mode != true)
				 {
					 labelZn->BackColor = Color::Red;
				 }
				 else
				 {
					 labelWn->BackColor = Color::Red;					 
				 }
			 }
			 else
			 {
				 mmiDataPtr->axisButton[2] = 0;
				 mmiDataPtr->cycleStart    = false;
				 sysLinkDataPtr->mmitointp.cycleStart = false;
				 button_zn->BackColor = Color::Transparent;
				 if (mmiDataPtr->xyz_mode != true)
				 {
					 labelZn->BackColor = Color::Transparent;
				 }
				 else
				 {
					 labelWn->BackColor = Color::Transparent;					 
				 }
			 }
		 }
/************************************************************************************/

/****************************************** Form Close ************************************/
private: System::Void Form1_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {

				 intpClose( intpDataPtr );
				 decClose( decDataPtr );// close intp/dec
				 timer_real->Enabled = false;
				 timer_nonReal->Enabled = false;//close time

				 // close motion card and card timer
#if HD_TIMER
				 disableHDTimer();
				 closeMotionCard();
#endif
		 }
/*****************************************************************************************/

/****************************************** Time Real ************************************/
	private: System::Void timer_real_Tick(System::Object^  sender, System::EventArgs^  e) {
				 if (intpDataPtr->error != 1000 && intpDataPtr->first_error != true)
				 {
					 realKnl();
					 intpMain( intpDataPtr );
				 }
				 else if ( intpDataPtr->error == 1000 && intpDataPtr->first_error != true)

				 {
					 if (intpDataPtr->error == 1000 && intpDataPtr->error_counter> 0)
					 {
						intpDataPtr->error_counter--;
						 MessageBox::Show( "運動超出工作範圍", "運動錯誤", MessageBoxButtons::OK, MessageBoxIcon::Error );
						 //訊息				標頭			按鈕					圖示
					 }
					
					 intpDataPtr->first_error = true;
					 intpDataPtr->error = 0;
				 }

			 }
/*******************************************************************************************/

/****************************************** Time nonReal ***************************************/

	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				
				 mmiMain( mmiDataPtr );
				 sysMain( sysDataPtr );
				 decMain( decDataPtr );

				 //XYZ position
				 textBox_posX->Text		= mmiDataPtr->xyzNew[0].ToString("0.000");
				 textBox_posY->Text		= mmiDataPtr->xyzNew[1].ToString("0.000");
				 textBox_posZ->Text		= mmiDataPtr->xyzNew[2].ToString("0.000");

				 //UVW position
				 textBox_posU->Text		= mmiDataPtr->uvwNew[0].ToString("0.000");
				 textBox_posV->Text		= mmiDataPtr->uvwNew[1].ToString("0.000");
				 textBox_posW->Text		= mmiDataPtr->uvwNew[2].ToString("0.000");
			
				 switch ( mmiDataPtr->opMode )
				 {
					 //check MEM mode
				 case MEM_MODE:		
					 if ( (mmiDataPtr->cycleStart == true) && (mmiDataPtr->feedHold != true) )
					 {
						 sysLinkDataPtr->mmitosys.fileValid = mmiDataPtr->fileValid;				//按start鈕後且當hold鈕不作用時，檔案才生效
						
					 }
					 break;

				 }
				mmiDataPtr->cycleStart = false;
 }

/*******************************************************************************************/


/************************************ cycle Start *********************************************/
	
	 private: System::Void button_cyclestart_Click(System::Object^  sender, System::EventArgs^  e) {

				  if ( (mmiDataPtr->cycleStart == false)   )                     
				  {
					  mmiDataPtr->cycleStart = true;
				  }	

				 switch ( mmiDataPtr->opMode ){
				  case MDI_MODE:	
					 if ( mmiDataPtr->cycleStart == true )
					 {
						 pin_ptr<const wchar_t> wch = PtrToStringChars(richTextBox_ncFile->Text);
						 size_t convertedChars = 0;
						 size_t  sizeInBytes = ((richTextBox_ncFile->Text->Length + 1) * 2);
						 errno_t err = 0;
						 err = wcstombs_s(&convertedChars,mmiDataPtr->ncBuffer,sizeInBytes,wch,sizeInBytes);
					 }
					 }
				  
}

/**********************************************************************************************/
/*************************** Emergency ******************************/
private: System::Void button_emergency_Click(System::Object^  sender, System::EventArgs^  e) {
if ( mmiDataPtr->feedHold == false )						//當hold鈕未被點時，點下會使cycle停止，feed暫停，hold鈕變紅
{
		mmiDataPtr->feedHold = true;
}
else														//當hold鈕已點過時，點下會使cycle啟動，feed繼續，hold鈕顏色恢復
{
		mmiDataPtr->feedHold = false;
}
	}
/***************************************************************************/

private: System::Void trackBar_feedOverride_Scroll(System::Object^  sender, System::EventArgs^  e) {
				if ( trackBar_feedOverride->Value < 40)
				{
					trackBar_feedOverride->Value = 40;
				}
				 mmiDataPtr->feedOverride = trackBar_feedOverride->Value;
				 label_feedOverride->Text = trackBar_feedOverride->Value.ToString() + "%" ;
			 }
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }

private: System::Void richTextBox_ncFile_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 }

private: System::Void tableLayoutPanel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 }

private: System::Void button22_Click(System::Object^  sender, System::EventArgs^  e) {
			 }

	private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void label_u_Click(System::Object^  sender, System::EventArgs^  e) {
			 }

private: System::Void panel7_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }

private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void panel8_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }

private: System::Void label_feedOverride_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void UVW_Transform_Click(System::Object^  sender, System::EventArgs^  e) {

			  if( mmiDataPtr->opMode == JOG_MODE || mmiDataPtr->opMode == WHEEL_MODE || mmiDataPtr->opMode == HOME_MODE || mmiDataPtr->opMode == TEACH_MODE )
			  {

				  if( mmiDataPtr->xyz_mode == false )
				  {
					  button_xp->Text = "U+";
					  button_yp->Text = "V+";
					  button_zp->Text = "W+";
					  button_xn->Text = "U-";
					  button_yn->Text = "V-";
					  button_zn->Text = "W-";
					  UVW_Transform->Text = "XYZ";
					  mmiDataPtr->xyz_mode = true;
					  mmiDataPtr->uvwSystem = true;
					  mmiDataPtr->xyzSystem = false;
				  }
				  else
				  {
					  button_xp->Text = "X+";
					  button_yp->Text = "Y+";
					  button_zp->Text = "Z+";
					  button_xn->Text = "X-";
					  button_yn->Text = "Y-";
					  button_zn->Text = "Z-";
					  UVW_Transform ->Text = "UVW";
					  mmiDataPtr->xyz_mode = false;
					  mmiDataPtr->uvwSystem = false;
					  mmiDataPtr->xyzSystem = true;
				  }
			  }

		 }
/**************************op mode***************************/

/*************************************** MEM MODE ******************************************/

private: System::Void button_mem_Click(System::Object^  sender, System::EventArgs^  e) {

			 decReset( decDataPtr );					//Reset
			 intpReset( intpDataPtr );
			 mmiReset( mmiDataPtr );

			 //fileData
			 richTextBox_ncFile->Clear();
			 textBox_filePath->Clear();
			 if ( mmiDataPtr->opMode != MEM_MODE && mmiDataPtr->cycleStart == false )
			 {
				 button_xp->BackColor = Color::Transparent;
				 button_xn->BackColor = Color::Transparent;
				 button_yp->BackColor = Color::Transparent;
				 button_yn->BackColor = Color::Transparent;
				 button_zp->BackColor = Color::Transparent;
				 button_zn->BackColor = Color::Transparent;	
				 button_mem->BackColor = Color::Green;
				 button_mdi->BackColor = Color::SteelBlue;
				 button_jog->BackColor = Color::SteelBlue;
				 button_home->BackColor = Color::SteelBlue;
				 button_wheel->BackColor = Color::SteelBlue;
				 button_teach->BackColor = Color::SteelBlue;

				 mmiDataPtr->opMode = MEM_MODE;
				 button_cyclestart ->Enabled = true;
				 button_record     ->Enabled = false;
				 button_teachin->Enabled = false;

				 button_xp->Enabled  = false;
				 button_xn->Enabled  = false;
				 button_yp->Enabled  = false;
				 button_yn->Enabled  = false;
				 button_zp->Enabled  = false;
				 button_zn->Enabled  = false;

				 button_x1->Enabled  = false;
				 button_x10->Enabled  = false;
				 button_x100->Enabled  = false;

				 button_x1->BackColor = Color::Transparent;	
				 button_x10->BackColor = Color::Transparent;	
				 button_x100->BackColor = Color::Transparent;	
			 }
		 }
/*********************************************************************************************/
/*************************************** MDI MODE ******************************************/
private: System::Void button_mdi_Click(System::Object^  sender, System::EventArgs^  e) {

				 decReset( decDataPtr );					//Reset
				 intpReset( intpDataPtr );
				 mmiReset( mmiDataPtr );
				 richTextBox_ncFile->Clear();
				 textBox_filePath->Clear();
			 if ( mmiDataPtr->opMode != MDI_MODE && mmiDataPtr->cycleStart == false )
			 {

				 mmiDataPtr->opMode = MDI_MODE;
				 button_mem->BackColor = Color::SteelBlue;
				 button_mdi->BackColor = Color::Green;
				 button_jog->BackColor = Color::SteelBlue;
				 button_home->BackColor = Color::SteelBlue;
				 button_wheel->BackColor = Color::SteelBlue;
				 button_teach->BackColor = Color::SteelBlue;
				 button_xp->BackColor = Color::Transparent;
				 button_xn->BackColor = Color::Transparent;
				 button_yp->BackColor = Color::Transparent;
				 button_yn->BackColor = Color::Transparent;
				 button_zp->BackColor = Color::Transparent;
				 button_zn->BackColor = Color::Transparent;	
				 button_record ->Enabled = false;
				 button_teachin->Enabled = false;
				 button_xp->Enabled  = false;
				 button_xn->Enabled  = false;
				 button_yp->Enabled  = false;
				 button_yn->Enabled  = false;
				 button_zp->Enabled  = false;
				 button_zn->Enabled  = false;

				 button_x1->Enabled  = false;
				 button_x10->Enabled  = false;
				 button_x100->Enabled  = false;

				 button_x1->BackColor = Color::Transparent;	
				 button_x10->BackColor = Color::Transparent;	
				 button_x100->BackColor = Color::Transparent;	
			 }
		 }
/*************************************** JOG MODE ********************************************/
private: System::Void button_jog_Click(System::Object^  sender, System::EventArgs^  e) {

			 decReset( decDataPtr );
			 intpReset( intpDataPtr );
			 mmiReset( mmiDataPtr );

			 //fileData
			 richTextBox_ncFile->Clear();
			 textBox_filePath->Clear();

			 if ( mmiDataPtr->opMode != JOG_MODE && mmiDataPtr->cycleStart == false )
			 {

				 mmiDataPtr->reset = true;
				 mmiDataPtr->opMode = JOG_MODE;
				 sysLinkDataPtr->mmitointp.opMode = JOG_MODE;

				 button_mem->BackColor = Color::SteelBlue;
				 button_mdi->BackColor = Color::SteelBlue;
				 button_jog->BackColor = Color::Green;
				 button_home->BackColor = Color::SteelBlue;
				 button_wheel->BackColor = Color::SteelBlue;
				 button_teach->BackColor = Color::SteelBlue;

				 button_record->Enabled = false;
				 button_teachin->Enabled = false;
				 button_xp->Enabled  = true;
				 button_xn->Enabled  = true;
				 button_yp->Enabled  = true;
				 button_yn->Enabled  = true;
				 button_zp->Enabled  = true;
				 button_zn->Enabled  = true;

				 button_x1->Enabled  = false;
				 button_x10->Enabled  = false;
				 button_x100->Enabled  = false;

				 button_x1->BackColor = Color::Transparent;	
				 button_x10->BackColor = Color::Transparent;	
				 button_x100->BackColor = Color::Transparent;	
			 }
		 }
/**************************** HOME MODE **********************************/
private: System::Void button_home_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ( mmiDataPtr->opMode != HOME_MODE && mmiDataPtr->cycleStart == false )
			 {

				 //fileData
				 richTextBox_ncFile->Clear();
				 textBox_filePath->Clear();

				 button_xp->BackColor = Color::Transparent;
				 button_xn->BackColor = Color::Transparent;
				 button_yp->BackColor = Color::Transparent;
				 button_yn->BackColor = Color::Transparent;
				 button_zp->BackColor = Color::Transparent;
				 button_zn->BackColor = Color::Transparent;	
				 button_mem->BackColor = Color::SteelBlue;
				 button_mdi->BackColor = Color::SteelBlue;
				 button_jog->BackColor = Color::SteelBlue;
				 button_home->BackColor = Color::Green;
				 button_wheel->BackColor = Color::SteelBlue;
				 button_teach->BackColor = Color::SteelBlue;

				 mmiDataPtr->opMode = HOME_MODE;
				 button_xp->Enabled  = false;
				 button_xn->Enabled  = false;
				 button_yp->Enabled  = false;
				 button_yn->Enabled  = false;
				 button_zp->Enabled  = false;
				 button_zn->Enabled  = false;
				 button_record     ->Enabled = false;
				 button_teachin->Enabled = false;

				 button_x1->Enabled  = false;
				 button_x10->Enabled  = false;
				 button_x100->Enabled  = false;

				 button_x1->BackColor = Color::Transparent;	
				 button_x10->BackColor = Color::Transparent;	
				 button_x100->BackColor = Color::Transparent;	
			 }
		 }
/*****************************Wheel MODE*******************************/
private: System::Void button_wheel_Click(System::Object^  sender, System::EventArgs^  e) {



			 //fileData
			 richTextBox_ncFile->Clear();
			 textBox_filePath->Clear();

			 if ( mmiDataPtr->opMode != WHEEL_MODE && mmiDataPtr->cycleStart == false )
			 {
				 decReset( decDataPtr );
				 intpReset( intpDataPtr );
				 mmiReset( mmiDataPtr );
				 mmiDataPtr->reset = true;
				 mmiDataPtr->opMode = WHEEL_MODE;
				 sysLinkDataPtr->mmitointp.opMode = WHEEL_MODE;

				 button_mem->BackColor = Color::SteelBlue;
				 button_mdi->BackColor = Color::SteelBlue;
				 button_jog->BackColor = Color::SteelBlue;
				 button_home->BackColor = Color::SteelBlue;
				 button_wheel->BackColor = Color::Green;
				 button_teach->BackColor = Color::SteelBlue;

				 button_xp->Enabled  = true;
				 button_xn->Enabled  = true;
				 button_yp->Enabled  = true;
				 button_yn->Enabled  = true;
				 button_zp->Enabled  = true;
				 button_zn->Enabled  = true;
				 button_record     ->Enabled = false;
				 button_teachin->Enabled = false;

				 button_x1->Enabled  = true;
				 button_x10->Enabled  = true;
				 button_x100->Enabled  = true;
			 }
		 }
/************************* Teach MODE **********************************/
private: System::Void button_teach_Click(System::Object^  sender, System::EventArgs^  e) {



			 //fileData
			 richTextBox_ncFile->Clear();
			 textBox_filePath->Clear();

			 if ( mmiDataPtr->opMode != TEACH_MODE && mmiDataPtr->cycleStart == false )
			 {
				 decReset( decDataPtr );
				 intpReset( intpDataPtr );
				 mmiReset( mmiDataPtr );
				 mmiDataPtr->reset = true;
				 mmiDataPtr->opMode = TEACH_MODE;
				 sysLinkDataPtr->mmitointp.opMode = TEACH_MODE;

				 button_mem->BackColor = Color::SteelBlue;
				 button_mdi->BackColor = Color::SteelBlue;
				 button_jog->BackColor = Color::SteelBlue;
				 button_home->BackColor = Color::SteelBlue;
				 button_wheel->BackColor = Color::SteelBlue;
				 button_teach->BackColor = Color::Green;
				 

				 button_record->Enabled = true;
				 button_teachin->Enabled = true;
				 button_xp->Enabled  = true;
				 button_xn->Enabled  = true;
				 button_yp->Enabled  = true;
				 button_yn->Enabled  = true;
				 button_zp->Enabled  = true;
				 button_zn->Enabled  = true;

				 button_x1->Enabled  = false;
				 button_x10->Enabled  = false;
				 button_x100->Enabled  = false;

				 button_x1->BackColor = Color::Transparent;	
				 button_x10->BackColor = Color::Transparent;	
				 button_x100->BackColor = Color::Transparent;	
			 }
}
/************************  X 1 *****************************************/
private: System::Void button_x1_Click(System::Object^  sender, System::EventArgs^  e) {

			 if (mmiDataPtr->increSize	!= 1)
			 {
				 mmiDataPtr->increSize	= 1;
				 button_x1 ->BackColor   = Color::Gold;
				 button_x10 ->BackColor   = Color::Transparent;
				 button_x100 ->BackColor   = Color::Transparent;
			 }
			 else
			 {
			      button_x1 ->BackColor   = Color::Transparent;
				  mmiDataPtr->increSize	  = 0;
			 }

		 }
/************************  X10 ******************************************/
private: System::Void button_x10_Click(System::Object^  sender, System::EventArgs^  e) {
		 
			 if (mmiDataPtr->increSize	!= 10)
			 {
				 mmiDataPtr->increSize	= 10;
				 button_x1 ->BackColor   = Color::Transparent;
				 button_x10 ->BackColor   = Color::Gold;
				 button_x100 ->BackColor   = Color::Transparent;
			 }
			 else
			 {
				 button_x10 ->BackColor   = Color::Transparent;
				 mmiDataPtr->increSize	  = 0;
			 }
		 	
		 }
/************************  X100 *******************************************/
private: System::Void button_x100_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (mmiDataPtr->increSize	!= 100)
			 {
				 mmiDataPtr->increSize	= 100;
				 button_x1 ->BackColor   = Color::Transparent;
				 button_x10 ->BackColor   = Color::Transparent;
				 button_x100 ->BackColor   = Color::Gold;
			 }
			 else
			 {
				 button_x100 ->BackColor   = Color::Transparent;
				 mmiDataPtr->increSize	  = 0;
			 }
		 }
/*******************************Record****************************************/

private: System::Void button21_Click(System::Object^  sender, System::EventArgs^  e) {
				 if ( mmiDataPtr->ncCount + 50 < 1000 )												// 38為一行nc code的字元數
				 {
					//將紀錄的位置已G01 G90 XYZ F10的運動方式來記錄
					 mmiDataPtr->blockNumber++;
					 mmiDataPtr->ncCount	+= sprintf( mmiDataPtr->ncBuffer + mmiDataPtr->ncCount, "N%d G01 G90 X%.3fY%.3fZ%.3f F30\n", mmiDataPtr->blockNumber, mmiDataPtr->xyzNew[0], mmiDataPtr->xyzNew[1], mmiDataPtr->xyzNew[2] );
					 strcat( mmiDataPtr->ncBuffer, "M30" );

					 richTextBox_ncFile->Text = gcnew String( mmiDataPtr->ncBuffer );				//將buffer(filename)裡的內容傳至richTextBox顯示
				 }
				 else
				 {						//訊息				標頭			按鈕					圖示
					 MessageBox::Show( "紀錄數據超過限制", "按鈕錯誤", MessageBoxButtons::OK, MessageBoxIcon::Warning );
				 }

			 }
/*******************************Teach in and save file****************************************/
private: System::Void button20_Click(System::Object^  sender, System::EventArgs^  e) {

			 //initialize openFileDialog
			 SaveFileDialog^ saveFileDialog_file= gcnew SaveFileDialog;
			 saveFileDialog_file->InitialDirectory = "";								//檔案開啟的預設路徑 "..\\"表示上一層
			 saveFileDialog_file->Filter = "文字檔(*.txt)|*.txt|所有檔案(*.*)|*.*";		//可能的副檔名篩選
			 saveFileDialog_file->FilterIndex = 1;										//預設Filter的篩選條件
			 saveFileDialog_file->DefaultExt = "*.txt";									//預設為文字檔
			 saveFileDialog_file->FileName = "";										//清除檔案路徑的字串
			 saveFileDialog_file->RestoreDirectory = true;								//指定上一次開啟的路徑

			 //show dialog, then check success or not
			 if ( saveFileDialog_file->ShowDialog() == System::Windows::Forms::DialogResult::OK )
			 {
				 // If the file name is not an empty string open it for saving.
				 if ( saveFileDialog_file->FileName != "" )
				 {
					 //把saveFileDialog裡的檔名轉成char，並送入
					 pin_ptr<const wchar_t> wch = PtrToStringChars( saveFileDialog_file->FileName );
					 size_t convertedChars = 0;
					 size_t  sizeInBytes = ((saveFileDialog_file->FileName->Length + 1) * 2);
					 errno_t err = 0;
					 err = wcstombs_s(&convertedChars, mmiDataPtr->filename, sizeInBytes, wch, sizeInBytes);

					 //把richTextBox取得的內容，存入檔案名為""的txt檔
					 FILE* fPtr;
					 fPtr = fopen( mmiDataPtr->filename, "w" );
					 fprintf( fPtr, mmiDataPtr->ncBuffer );

					 fclose( fPtr );
				 }
			 }
					 }
/***************************************** FeedHold *******************************************/
private: System::Void button_fh_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ( mmiDataPtr->feedHold == false )						//當hold鈕未被點時，點下會使cycle停止，feed暫停，hold鈕變紅
			 {
				 mmiDataPtr->feedHold = true;
				 button_hold->BackColor = Color::Red;
			 }
			 else														//當hold鈕已點過時，點下會使cycle啟動，feed繼續，hold鈕顏色恢復
			 {
				 mmiDataPtr->feedHold = false;
				 button_hold->BackColor = SystemColors::ButtonFace;
			 }
		 }
/****************************************************************************************/
private: System::Void label19_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button_reset_Click(System::Object^  sender, System::EventArgs^  e) {

			 decReset( decDataPtr );
			 intpReset( intpDataPtr );
			 mmiReset( mmiDataPtr );
			 richTextBox_ncFile->Clear();
			 textBox_filePath->Clear();
		 }

private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label9_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void labelZn_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

