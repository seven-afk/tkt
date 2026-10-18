#include "Wav.h"
#include "Ogg.h"
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
			oggPlayer = new Ogg();
			listView1->OwnerDraw = true;
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

	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Button^ previousButton;

	private: Wav* wavPlayer = nullptr;
	private: Ogg* oggPlayer = nullptr;
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
	private: System::Windows::Forms::ListView^ listView1;

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
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->previousButton = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->importToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exportToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pauseButton = (gcnew System::Windows::Forms::Button());
			this->stropButton = (gcnew System::Windows::Forms::Button());
			this->playButton = (gcnew System::Windows::Forms::Button());
			this->nextButton = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			//
			// openFileDialog1
			//
			this->openFileDialog1->FileName = L"openFileDialog1";
			//
			// previousButton
			//
			this->previousButton->Location = System::Drawing::Point(97, 282);
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
			this->menuStrip1->Size = System::Drawing::Size(575, 24);
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
			this->openToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
			//
			// importToolStripMenuItem
			//
			this->importToolStripMenuItem->Name = L"importToolStripMenuItem";
			this->importToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->importToolStripMenuItem->Text = L"Import";
			this->importToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::importList);
			//
			// exportToolStripMenuItem
			//
			this->exportToolStripMenuItem->Name = L"exportToolStripMenuItem";
			this->exportToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->exportToolStripMenuItem->Text = L"Export";
			this->exportToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::exportList);
			//
			// pauseButton
			//
			this->pauseButton->Location = System::Drawing::Point(178, 282);
			this->pauseButton->Name = L"pauseButton";
			this->pauseButton->Size = System::Drawing::Size(75, 23);
			this->pauseButton->TabIndex = 3;
			this->pauseButton->Text = L"Pause";
			this->pauseButton->UseVisualStyleBackColor = true;
			this->pauseButton->Click += gcnew System::EventHandler(this, &MyForm::pauseButton_Click);
			//
			// stropButton
			//
			this->stropButton->Location = System::Drawing::Point(340, 282);
			this->stropButton->Name = L"stropButton";
			this->stropButton->Size = System::Drawing::Size(75, 23);
			this->stropButton->TabIndex = 5;
			this->stropButton->Text = L"Stop";
			this->stropButton->UseVisualStyleBackColor = true;
			this->stropButton->Click += gcnew System::EventHandler(this, &MyForm::stropButton_Click);
			//
			// playButton
			//
			this->playButton->Location = System::Drawing::Point(259, 282);
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(75, 23);
			this->playButton->TabIndex = 4;
			this->playButton->Text = L"Play";
			this->playButton->UseVisualStyleBackColor = true;
			this->playButton->Click += gcnew System::EventHandler(this, &MyForm::playButton_Click);
			//
			// nextButton
			//
			this->nextButton->Location = System::Drawing::Point(421, 282);
			this->nextButton->Name = L"nextButton";
			this->nextButton->Size = System::Drawing::Size(75, 23);
			this->nextButton->TabIndex = 6;
			this->nextButton->Text = L"Next";
			this->nextButton->UseVisualStyleBackColor = true;
			this->nextButton->Click += gcnew System::EventHandler(this, &MyForm::nextButton_Click);
			//
			// trackBar1
			//
			this->trackBar1->Location = System::Drawing::Point(30, 180);
			this->trackBar1->Maximum = 100;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->trackBar1->Size = System::Drawing::Size(45, 125);
			this->trackBar1->TabIndex = 7;
			this->trackBar1->TickFrequency = 10;
			this->trackBar1->Value = 100;
			this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &MyForm::trackBar1_ValueChanged);
			//
			// listView1
			//
			this->listView1->Activation = System::Windows::Forms::ItemActivation::OneClick;
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(97, 53);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(399, 223);
			this->listView1->TabIndex = 8;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::List;
			this->listView1->DrawItem += gcnew System::Windows::Forms::DrawListViewItemEventHandler(this, &MyForm::listView1_DrawItem);
			this->listView1->ItemActivate += gcnew System::EventHandler(this, &MyForm::listView1_ItemActivate);
			//
			// MyForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(575, 318);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->nextButton);
			this->Controls->Add(this->stropButton);
			this->Controls->Add(this->playButton);
			this->Controls->Add(this->pauseButton);
			this->Controls->Add(this->previousButton);
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

	private: System::Void listView1_DrawItem(System::Object^ sender, DrawListViewItemEventArgs^ e)
	{
		// Fond avec TA couleur (celle que tu mets déjà en code sur l'item)
		e->Graphics->FillRectangle(gcnew SolidBrush(e->Item->BackColor), e->Bounds);

		// Texte
		TextRenderer::DrawText(e->Graphics, e->Item->Text, e->Item->Font,
			e->Bounds, e->Item->ForeColor, TextFormatFlags::Left);
	}

	private: System::Void listView1_DrawColumnHeader(System::Object^ sender, DrawListViewColumnHeaderEventArgs^ e)
	{
		e->DrawDefault = true; // header normal
	}

	private: String^ GetSoundName(String^ _path)
	{
		return _path->Substring(_path->LastIndexOf("\\") + 1);
	}

	private: String^ GetFileType(String^ _path)
	{
		return filePaths[playingIndex]->Substring(filePaths[playingIndex]->LastIndexOf("."));
	}

	private: void PlaySound()
	{
		IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(filePaths[playingIndex]);
		const char* file = static_cast<char*>(ptrToNativeString.ToPointer());

		String^ type = GetFileType(filePaths[playingIndex]);
		oggPlayer->Stop();
		wavPlayer->StopWav();

		if (type == ".wav")
			wavPlayer->PlayWav(file);
		else if (type == ".ogg")
		{
			oggPlayer->InitFile(file);
			oggPlayer->PlayOgg();
		}
		isPaused = false;
		listView1->Items[playingIndex]->BackColor = Color::LightBlue;
	}

	private: System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		PlaySound();
	}
	private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		openFileDialog1->Filter = "Audio files (*.wav;*.ogg)|*.wav;*.ogg";
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ path = openFileDialog1->FileName;
			filePaths.Add(path);
			listView1->Items->Add(GetSoundName(path));
			soundNbr++;
		}
	}
	private: System::Void previousButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ type = GetFileType(filePaths[playingIndex]);

		if (playingIndex > 0)
		{
			listView1->Items[playingIndex]->BackColor = Color::White;
			playingIndex--;

			if (type == ".wav")
				wavPlayer->StopWav();
			else if (type == ".ogg")
				oggPlayer->Stop();

			PlaySound();
		}
	}
	private: System::Void pauseButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ type = GetFileType(filePaths[playingIndex]);

		if (type == ".wav")
		{
			if (isPaused)
				wavPlayer->ResumeWav();
			else
				wavPlayer->PauseWav();
		}
		else if (type == ".ogg")
		{
			if (isPaused)
				oggPlayer->Resume();
			else
				oggPlayer->Pause();
		}
		isPaused = !isPaused;
	}
	private: System::Void stropButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ type = GetFileType(filePaths[playingIndex]);

		if (type == ".wav")
			wavPlayer->StopWav();
		else if (type == ".ogg")
			oggPlayer->Stop();

		listView1->Items[playingIndex]->BackColor = Color::White;
	}
	private: System::Void nextButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ type = GetFileType(filePaths[playingIndex]);

		if (playingIndex < soundNbr - 1)
		{
			listView1->Items[playingIndex]->BackColor = Color::White;
			playingIndex++;

			if (type == ".wav")
				wavPlayer->StopWav();
			else if (type == ".ogg")
				oggPlayer->Stop();

			PlaySound();
		}
	}
	private: System::Void trackBar1_ValueChanged(System::Object^ sender, System::EventArgs^ e)
	{
		alListenerf(AL_GAIN, (trackBar1->Value / 100.f));
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
				String^ path = reader->ReadLine();
				filePaths.Add(path);
				soundNbr++;

				listView1->Items->Add(GetSoundName(path));
			}
			reader->Close();
		}
	}
	private: System::Void listView1_ItemActivate(System::Object^ sender, System::EventArgs^ e)
	{
		listView1->Items[playingIndex]->BackColor = Color::White;
		int index = listView1->SelectedIndices[0];
		playingIndex = index;
		PlaySound();
	}
	};
}
