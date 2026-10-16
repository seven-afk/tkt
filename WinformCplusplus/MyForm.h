#include "Wav.h"
#include <vector>
#include <iostream>
#define	WATER_STREAM_0		"Ruisseau_Escattes_01.wav"
#define	WATER_STREAM_1		"Ruisseau_Escattes_02.wav"
#pragma once

namespace WinformCplusplus {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Description résumée de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:

		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			wavPlayer = new Wav();
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Button^ previousButton;

	private: Wav* wavPlayer = nullptr;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: List<System::String^> filePaths;
	private: bool isPaused;
	private: int playingIndex = 0;
	private: int soundNbr = 0;
	private: System::Windows::Forms::Button^ pauseButton;
	private: System::Windows::Forms::Button^ stropButton;

	private: System::Windows::Forms::Button^ playButton;
	private: System::Windows::Forms::Button^ nextButton;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::ToolStripMenuItem^ importToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exportToolStripMenuItem;

	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->previousButton = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pauseButton = (gcnew System::Windows::Forms::Button());
			this->stropButton = (gcnew System::Windows::Forms::Button());
			this->playButton = (gcnew System::Windows::Forms::Button());
			this->nextButton = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->importToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exportToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			//
			// openFileDialog1
			//
			this->openFileDialog1->FileName = L"openFileDialog1";
			//
			// label1
			//
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(111, 74);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 13);
			this->label1->TabIndex = 0;
			//
			// previousButton
			//
			this->previousButton->Location = System::Drawing::Point(76, 113);
			this->previousButton->Name = L"previousButton";
			this->previousButton->Size = System::Drawing::Size(75, 23);
			this->previousButton->TabIndex = 1;
			this->previousButton->Text = L"Previous";
			this->previousButton->UseVisualStyleBackColor = true;
			this->previousButton->Click += gcnew System::EventHandler(this, &MyForm::previousButton_Click);
			//
			// menuStrip1
			//
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(560, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			//
			// fileToolStripMenuItem
			//
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openToolStripMenuItem,
					this->importToolStripMenuItem, this->exportToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			//
			// openToolStripMenuItem
			//
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
			//
			// pauseButton
			//
			this->pauseButton->Location = System::Drawing::Point(157, 113);
			this->pauseButton->Name = L"pauseButton";
			this->pauseButton->Size = System::Drawing::Size(75, 23);
			this->pauseButton->TabIndex = 3;
			this->pauseButton->Text = L"Pause";
			this->pauseButton->UseVisualStyleBackColor = true;
			this->pauseButton->Click += gcnew System::EventHandler(this, &MyForm::pauseButton_Click);
			//
			// stropButton
			//
			this->stropButton->Location = System::Drawing::Point(319, 113);
			this->stropButton->Name = L"stropButton";
			this->stropButton->Size = System::Drawing::Size(75, 23);
			this->stropButton->TabIndex = 5;
			this->stropButton->Text = L"Stop";
			this->stropButton->UseVisualStyleBackColor = true;
			this->stropButton->Click += gcnew System::EventHandler(this, &MyForm::stropButton_Click);
			//
			// playButton
			//
			this->playButton->Location = System::Drawing::Point(238, 113);
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(75, 23);
			this->playButton->TabIndex = 4;
			this->playButton->Text = L"Play";
			this->playButton->UseVisualStyleBackColor = true;
			this->playButton->Click += gcnew System::EventHandler(this, &MyForm::playButton_Click);
			//
			// nextButton
			//
			this->nextButton->Location = System::Drawing::Point(400, 113);
			this->nextButton->Name = L"nextButton";
			this->nextButton->Size = System::Drawing::Size(75, 23);
			this->nextButton->TabIndex = 6;
			this->nextButton->Text = L"Next";
			this->nextButton->UseVisualStyleBackColor = true;
			this->nextButton->Click += gcnew System::EventHandler(this, &MyForm::nextButton_Click);
			//
			// trackBar1
			//
			this->trackBar1->Location = System::Drawing::Point(12, 42);
			this->trackBar1->Maximum = 100;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->trackBar1->Size = System::Drawing::Size(45, 125);
			this->trackBar1->TabIndex = 7;
			this->trackBar1->TickFrequency = 10;
			this->trackBar1->Value = 100;
			this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &MyForm::trackBar1_ValueChanged);
			//
			// importToolStripMenuItem
			//
			this->importToolStripMenuItem->Name = L"importToolStripMenuItem";
			this->importToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->importToolStripMenuItem->Text = L"Import";
			this->importToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::importList);
			//
			// exportToolStripMenuItem
			//
			this->exportToolStripMenuItem->Name = L"exportToolStripMenuItem";
			this->exportToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->exportToolStripMenuItem->Text = L"Export";
			this->exportToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::exportList);
			//
			// MyForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(560, 179);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->nextButton);
			this->Controls->Add(this->stropButton);
			this->Controls->Add(this->playButton);
			this->Controls->Add(this->pauseButton);
			this->Controls->Add(this->previousButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Le lecteur de l\'audio";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

	private: void PlaySound()
	{
		IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(filePaths[playingIndex]);
		wavPlayer->PlayWav(static_cast<char*>(ptrToNativeString.ToPointer()));
		isPaused = false;

		label1->Text = filePaths[playingIndex]->Substring(filePaths[playingIndex]->LastIndexOf("\\") + 1);
	}

	private: System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		PlaySound();
	}
	private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		openFileDialog1->AddExtension = "Audio files (*.wav;*.ogg)|*.wav;*.ogg";
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			filePaths.Add(openFileDialog1->FileName);
			soundNbr++;
		}
	}
	private: System::Void previousButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (playingIndex > 0)
		{
			playingIndex--;
			wavPlayer->StopWav();
			PlaySound();
		}
	}
	private: System::Void pauseButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ fileType = filePaths[playingIndex]->Substring(filePaths[playingIndex]->LastIndexOf("."));

		if (fileType == ".wav")
		{
			if (isPaused)
			{
				wavPlayer->ResumeWav();
			}
			else
			{
				wavPlayer->PauseWav();
			}
		}
		isPaused = !isPaused;
	}
	private: System::Void stropButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ fileType = filePaths[playingIndex]->Substring(filePaths[playingIndex]->LastIndexOf("."));

		if (fileType == ".wav")
		{
			wavPlayer->StopWav();
		}
	}
	private: System::Void nextButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (playingIndex < soundNbr - 1)
		{
			playingIndex++;
			wavPlayer->StopWav();
			PlaySound();
		}
	}
	private: System::Void trackBar1_ValueChanged(System::Object^ sender, System::EventArgs^ e)
	{
		String^ fileType = filePaths[playingIndex]->Substring(filePaths[playingIndex]->LastIndexOf("."));

		if (fileType == ".wav")
		{
			wavPlayer->ChangeVolume(float(trackBar1->Value / 100.f));
		}
	}

	private: System::Void exportList(System::Object^ sender, System::EventArgs^ e) {
		saveFileDialog1->Filter = "list txt|*.txt";
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(saveFileDialog1->FileName);
			for (int i = 0; i < filePaths.Count; i++) {
				writer->WriteLine(filePaths[i]);
			}
			writer->Close();
		}
	}
	private: System::Void importList(System::Object^ sender, System::EventArgs^ e) {
		openFileDialog1->AddExtension = "list txt|*.txt";
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			System::IO::StreamReader^ reader = gcnew System::IO::StreamReader(openFileDialog1->FileName);
			while (!reader->EndOfStream) {
				filePaths.Add(reader->ReadLine());
				soundNbr++;
			}
			reader->Close();
		}
	}
	};
}
