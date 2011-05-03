#pragma once
#include "Worker.h"
#include "webcrawler.h"
namespace WebSynonymFinder {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		bool showUnrealToggle;
		Form1(void)
		{
			InitializeComponent();
			showUnrealToggle = false;
			//
			//TODO: Add the constructor code here
			//
		}

		//This black magic to follow courtesy of http://www.codeproject.com/KB/mcpp/managedsafethreads.aspx
		delegate void UpdateUrlLabelCallback(Form1 ^frm, System::String ^text);
		static void UpdateUrlLabel(Form1 ^frm, System::String ^text)
		{
			if(frm->startUrl->InvokeRequired)
			{
				UpdateUrlLabelCallback ^d = gcnew UpdateUrlLabelCallback(UpdateUrlLabel);
				frm->Invoke(d,gcnew array<System::Object^>{frm, text});                
			}
			else
			{
				frm->startUrl->Text = text;
				frm->wordOfInterest->Text = "foooooo";
				frm->dataGridView1->Rows[1]->Cells[1]->Value=1;
			}
		}

		//The REAL database update call:
		delegate void updateCallback(Form1 ^frm, System::String ^word, System::Double ^ave, bool isWord);
		static void update(Form1 ^frm, System::String ^word, System::Double ^ave, bool isWord)
		{
			if(frm->dataGridView1->InvokeRequired)
			{
				updateCallback ^d = gcnew updateCallback(update);
				frm->Invoke(d,gcnew array<System::Object^>{frm, word, ave, isWord});                
			}
			else
			{
				//frm->UseWaitCursor = true;
				int dgvLength = frm->dataGridView1->RowCount; //Get DGV number of rows.

				// Delete a word if it already exists in the DGV
				for(int i=0; i<dgvLength; i++){
					System::String ^cellString = frm->dataGridView1->Rows[i]->Cells[0]->FormattedValue->ToString();
					if(cellString == word){
						frm->dataGridView1->Rows->Remove(frm->dataGridView1->Rows[i]);
						break;
					}
				}

				// Add the word in question to the DGV:
				DataGridViewRow ^newRow = gcnew DataGridViewRow; //Make a row to hold the new cells
				DataGridViewCell ^newCell0 = gcnew DataGridViewTextBoxCell; //Make the new cells (they have to be three separate ones).
				DataGridViewCell ^newCell1 = gcnew DataGridViewTextBoxCell;
				DataGridViewCell ^newCell2 = gcnew DataGridViewTextBoxCell;

				newCell0->Value = word; //Fill values into the cells
				newCell1->Value = ave;
				if(isWord){
					newCell2->Value = "Yes";
				}else{
					newCell2->Value = "No";
				}

				newRow->Cells->Add(newCell0); //Add the cells to the row
				newRow->Cells->Add(newCell1);
				newRow->Cells->Add(newCell2);

				for(int i=0; i<3; i++){
					newRow->Cells[i]->ReadOnly = true;
				}


				frm->dataGridView1->Rows->Add(newRow); // Add the row to the table
				frm->dataGridView1->Sort(frm->dataGridView1->Columns[1], System::ComponentModel::ListSortDirection::Ascending); // Resort the table


				if(!frm->showUnrealToggle && !isWord){
					//This would be the quick, elegant way to do it. If it worked:
					//frm->dataGridView1->Rows[0]->Visible = false;
					//frm->dataGridView1->RowCount-1

					for(int ii=0;ii<frm->dataGridView1->RowCount;ii++){
					if(frm->dataGridView1->Rows[ii]->Cells[2]->Value == "No"){
					//FormattedValue->ToString()
						frm->dataGridView1->Rows[ii]->Visible = false;
					}
				}
				}

				//frm->UseWaitCursor = false;

				//Some fun debugging toys.
				//frm->startUrl->Text = word;
				//frm->wordOfInterest->Text = "foooooo";
				//if(frm->dataGridView1->RowCount > 1)
				//frm->dataGridView1->Rows[1]->Cells[1]->Value=ave;
			}
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			//if(crawlerThread->isAlive)
				//crawlerThread->Abort();
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  firstUrlLabel;
	private: System::Windows::Forms::Label^  wordOfInterestLabel;
	private: System::Windows::Forms::Label^  numPagesLabel;
	private: System::Windows::Forms::TextBox^  startUrl;
	private: System::Windows::Forms::TextBox^  wordOfInterest;
	private: System::Windows::Forms::TextBox^  numPages;
	private: System::Windows::Forms::DataGridView^  dataGridView1;


	protected: 

	private:
		Thread ^crawlerThread;



private: System::Windows::Forms::Button^  goBtn;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  word;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  prox;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  isreal;
private: System::Windows::Forms::Button^  showUnreal;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Button^  stopBtn;

		 /// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->firstUrlLabel = (gcnew System::Windows::Forms::Label());
			this->wordOfInterestLabel = (gcnew System::Windows::Forms::Label());
			this->numPagesLabel = (gcnew System::Windows::Forms::Label());
			this->startUrl = (gcnew System::Windows::Forms::TextBox());
			this->wordOfInterest = (gcnew System::Windows::Forms::TextBox());
			this->numPages = (gcnew System::Windows::Forms::TextBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->word = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->prox = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->isreal = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->goBtn = (gcnew System::Windows::Forms::Button());
			this->showUnreal = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->stopBtn = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// firstUrlLabel
			// 
			this->firstUrlLabel->AutoSize = true;
			this->firstUrlLabel->Location = System::Drawing::Point(9, 12);
			this->firstUrlLabel->Name = L"firstUrlLabel";
			this->firstUrlLabel->Size = System::Drawing::Size(57, 13);
			this->firstUrlLabel->TabIndex = 0;
			this->firstUrlLabel->Text = L"Start URL:";
			this->firstUrlLabel->Click += gcnew System::EventHandler(this, &Form1::firstUrlLabel_Click);
			// 
			// wordOfInterestLabel
			// 
			this->wordOfInterestLabel->AutoSize = true;
			this->wordOfInterestLabel->Location = System::Drawing::Point(9, 51);
			this->wordOfInterestLabel->Name = L"wordOfInterestLabel";
			this->wordOfInterestLabel->Size = System::Drawing::Size(86, 13);
			this->wordOfInterestLabel->TabIndex = 1;
			this->wordOfInterestLabel->Text = L"Word of Interest:";
			this->wordOfInterestLabel->Click += gcnew System::EventHandler(this, &Form1::wordOfInterestLabel_Click);
			// 
			// numPagesLabel
			// 
			this->numPagesLabel->AutoSize = true;
			this->numPagesLabel->Location = System::Drawing::Point(9, 77);
			this->numPagesLabel->Name = L"numPagesLabel";
			this->numPagesLabel->Size = System::Drawing::Size(131, 13);
			this->numPagesLabel->TabIndex = 2;
			this->numPagesLabel->Text = L"Number of pages to crawl:";
			// 
			// startUrl
			// 
			this->startUrl->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->startUrl->Location = System::Drawing::Point(72, 9);
			this->startUrl->Name = L"startUrl";
			this->startUrl->Size = System::Drawing::Size(271, 20);
			this->startUrl->TabIndex = 3;
			// 
			// wordOfInterest
			// 
			this->wordOfInterest->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->wordOfInterest->Location = System::Drawing::Point(101, 48);
			this->wordOfInterest->Name = L"wordOfInterest";
			this->wordOfInterest->Size = System::Drawing::Size(242, 20);
			this->wordOfInterest->TabIndex = 4;
			// 
			// numPages
			// 
			this->numPages->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->numPages->Location = System::Drawing::Point(146, 74);
			this->numPages->Name = L"numPages";
			this->numPages->Size = System::Drawing::Size(197, 20);
			this->numPages->TabIndex = 5;
			this->numPages->TextChanged += gcnew System::EventHandler(this, &Form1::numPages_TextChanged);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->word, this->prox, 
				this->isreal});
			this->dataGridView1->Location = System::Drawing::Point(12, 129);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->Size = System::Drawing::Size(331, 540);
			this->dataGridView1->TabIndex = 6;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView1_CellContentClick);
			// 
			// word
			// 
			this->word->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->word->HeaderText = L"Word:";
			this->word->Name = L"word";
			this->word->ReadOnly = true;
			this->word->Width = 61;
			// 
			// prox
			// 
			this->prox->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->prox->HeaderText = L"Proximity to WOI";
			this->prox->Name = L"prox";
			this->prox->ReadOnly = true;
			this->prox->Width = 81;
			// 
			// isreal
			// 
			this->isreal->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->isreal->HeaderText = L"Is Real\?";
			this->isreal->Name = L"isreal";
			this->isreal->ReadOnly = true;
			this->isreal->Width = 66;
			// 
			// goBtn
			// 
			this->goBtn->Location = System::Drawing::Point(12, 100);
			this->goBtn->Name = L"goBtn";
			this->goBtn->Size = System::Drawing::Size(83, 23);
			this->goBtn->TabIndex = 7;
			this->goBtn->Text = L"Go";
			this->goBtn->UseVisualStyleBackColor = true;
			this->goBtn->Click += gcnew System::EventHandler(this, &Form1::goBtn_Click);
			// 
			// showUnreal
			// 
			this->showUnreal->Location = System::Drawing::Point(101, 100);
			this->showUnreal->Name = L"showUnreal";
			this->showUnreal->Size = System::Drawing::Size(120, 23);
			this->showUnreal->TabIndex = 8;
			this->showUnreal->Text = L"Show unreal words";
			this->showUnreal->UseVisualStyleBackColor = true;
			this->showUnreal->Click += gcnew System::EventHandler(this, &Form1::showUnreal_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(266, 13);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Note: must use full URL, including http:// and trailing /!";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// stopBtn
			// 
			this->stopBtn->Enabled = false;
			this->stopBtn->Location = System::Drawing::Point(227, 100);
			this->stopBtn->Name = L"stopBtn";
			this->stopBtn->Size = System::Drawing::Size(83, 23);
			this->stopBtn->TabIndex = 10;
			this->stopBtn->Text = L"Stop";
			this->stopBtn->UseVisualStyleBackColor = true;
			this->stopBtn->Visible = false;
			this->stopBtn->Click += gcnew System::EventHandler(this, &Form1::stopBtn_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(359, 681);
			this->Controls->Add(this->stopBtn);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->showUnreal);
			this->Controls->Add(this->goBtn);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->numPages);
			this->Controls->Add(this->wordOfInterest);
			this->Controls->Add(this->startUrl);
			this->Controls->Add(this->numPagesLabel);
			this->Controls->Add(this->wordOfInterestLabel);
			this->Controls->Add(this->firstUrlLabel);
			this->Name = L"Form1";
			this->Text = L"Web Synonym Finder";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void firstUrlLabel_Click(System::Object^  sender, System::EventArgs^  e) {
				 /*
				Worker ^myWorker = gcnew Worker(this);
				//this->someMethod();
				//myWorker->doStuff();

				//do that but with threading:
				ThreadStart ^myThreadDelegate = gcnew ThreadStart(myWorker, &Worker::doStuff);
				crawlerThread = gcnew Thread(myThreadDelegate);
				crawlerThread->IsBackground = true;
				crawlerThread->Start();
				*/
			 }
	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void dataGridView1_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		 }
private: System::Void wordOfInterestLabel_Click(System::Object^  sender, System::EventArgs^  e) {
			 /*
			 DataGridViewRow ^newRow = gcnew DataGridViewRow; //Make a row to hold the new cells
			 DataGridViewCell ^newCell1 = gcnew DataGridViewTextBoxCell; //Make the new cells (they have to be three separate ones).
			 DataGridViewCell ^newCell2 = gcnew DataGridViewTextBoxCell;
			 DataGridViewCell ^newCell3 = gcnew DataGridViewTextBoxCell;

			 newCell1->Value = "bar"; //Fill values into the cells
			 newCell2->Value = 111.1;
			 newCell3->Value = "Yes";

			 newRow->Cells->Add(newCell1); //Add the cells to the row
			 newRow->Cells->Add(newCell2);
			 newRow->Cells->Add(newCell3);

			 //nextrow
			 DataGridViewRow ^newRow2 = gcnew DataGridViewRow; //Make a row to hold the new cells
			 DataGridViewCell ^newCell4 = gcnew DataGridViewTextBoxCell; //Make the new cells (they have to be three separate ones).
			 DataGridViewCell ^newCell5 = gcnew DataGridViewTextBoxCell;
			 DataGridViewCell ^newCell6 = gcnew DataGridViewTextBoxCell;

			 newCell4->Value = "bar"; //Fill values into the cells
			 newCell5->Value = 21.1;
			 newCell6->Value = "Yes";

			 newRow2->Cells->Add(newCell4); //Add the cells to the row
			 newRow2->Cells->Add(newCell5);
			 newRow2->Cells->Add(newCell6);

			 if(this->dataGridView1->Rows[0]->Cells[1]->Value == 2){
				 this->dataGridView1->Sort(this->dataGridView1->Columns[1], System::ComponentModel::ListSortDirection::Ascending);
			 }else{
				this->dataGridView1->Rows->Add(newRow); //Add the row to the DGV.
				this->dataGridView1->Rows->Add(newRow2);
			 }
			 this->dataGridView1->Sort(this->dataGridView1->Columns[1], System::ComponentModel::ListSortDirection::Ascending);
			 // Once this function is over, all the things above get GC'd, and we redefine them next time anyway.
			 */
		 }
private: System::Void goBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			// Let's crawl!
			 if(this->startUrl->Text=="" || this->numPages->Text=="" || this->wordOfInterest->Text==""){
				//something's not filled in
				MessageBox::Show("You must fill in all boxes!",
					"Web Synonym Finder",
					MessageBoxButtons::OKCancel,
					MessageBoxIcon::Asterisk);
			 }else{
				webcrawler ^theCrawler = gcnew webcrawler(this, this->startUrl->Text, int::Parse(this->numPages->Text), this->wordOfInterest->Text);

				ThreadStart ^myThreadDelegate = gcnew ThreadStart(theCrawler, &webcrawler::crawl);
				crawlerThread = gcnew Thread(myThreadDelegate);
				crawlerThread->IsBackground = true;
				crawlerThread->Start();
			 }
		 }
private: System::Void numPages_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void showUnreal_Click(System::Object^  sender, System::EventArgs^  e) {
			showUnrealToggle = !showUnrealToggle;
			if(showUnrealToggle){
				//If it's set to show unreals:

				//make unreals visible:
				for(int ii=0;ii<this->dataGridView1->RowCount;ii++){
					this->dataGridView1->Rows[ii]->Visible = true;
				}

				this->showUnreal->Text = "Hide unreal words";
			}else{
				//if it's set to hide unreals:

				//make unreals invisible:
				for(int ii=0;ii<this->dataGridView1->RowCount;ii++){
					if(this->dataGridView1->Rows[ii]->Cells[2]->Value == "No"){
					//FormattedValue->ToString()
						this->dataGridView1->Rows[ii]->Visible = false;
					}
				}

				this->showUnreal->Text = "Show unreal words";
			}
		 }
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void stopBtn_Click(System::Object^  sender, System::EventArgs^  e) {
//			 TerminateThread(crawlerThread);
		 }
};
}

