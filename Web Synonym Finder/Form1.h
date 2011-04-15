#pragma once

namespace WebSynonymFinder {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// firstUrlLabel
			// 
			this->firstUrlLabel->AutoSize = true;
			this->firstUrlLabel->Location = System::Drawing::Point(12, 9);
			this->firstUrlLabel->Name = L"firstUrlLabel";
			this->firstUrlLabel->Size = System::Drawing::Size(57, 13);
			this->firstUrlLabel->TabIndex = 0;
			this->firstUrlLabel->Text = L"Start URL:";
			this->firstUrlLabel->Click += gcnew System::EventHandler(this, &Form1::firstUrlLabel_Click);
			// 
			// wordOfInterestLabel
			// 
			this->wordOfInterestLabel->AutoSize = true;
			this->wordOfInterestLabel->Location = System::Drawing::Point(332, 9);
			this->wordOfInterestLabel->Name = L"wordOfInterestLabel";
			this->wordOfInterestLabel->Size = System::Drawing::Size(86, 13);
			this->wordOfInterestLabel->TabIndex = 1;
			this->wordOfInterestLabel->Text = L"Word of Interest:";
			// 
			// numPagesLabel
			// 
			this->numPagesLabel->AutoSize = true;
			this->numPagesLabel->Location = System::Drawing::Point(574, 9);
			this->numPagesLabel->Name = L"numPagesLabel";
			this->numPagesLabel->Size = System::Drawing::Size(131, 13);
			this->numPagesLabel->TabIndex = 2;
			this->numPagesLabel->Text = L"Number of pages to crawl:";
			// 
			// startUrl
			// 
			this->startUrl->Location = System::Drawing::Point(12, 25);
			this->startUrl->Name = L"startUrl";
			this->startUrl->Size = System::Drawing::Size(317, 20);
			this->startUrl->TabIndex = 3;
			// 
			// wordOfInterest
			// 
			this->wordOfInterest->Location = System::Drawing::Point(335, 25);
			this->wordOfInterest->Name = L"wordOfInterest";
			this->wordOfInterest->Size = System::Drawing::Size(236, 20);
			this->wordOfInterest->TabIndex = 4;
			// 
			// numPages
			// 
			this->numPages->Location = System::Drawing::Point(577, 25);
			this->numPages->Name = L"numPages";
			this->numPages->Size = System::Drawing::Size(128, 20);
			this->numPages->TabIndex = 5;
			// 
			// dataGridView1
			// 
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(12, 51);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(692, 618);
			this->dataGridView1->TabIndex = 6;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(718, 681);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->numPages);
			this->Controls->Add(this->wordOfInterest);
			this->Controls->Add(this->startUrl);
			this->Controls->Add(this->numPagesLabel);
			this->Controls->Add(this->wordOfInterestLabel);
			this->Controls->Add(this->firstUrlLabel);
			this->Name = L"Form1";
			this->Text = L"Web Synonym Finder";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void firstUrlLabel_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			 }
};
}

