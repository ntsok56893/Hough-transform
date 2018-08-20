#pragma once

/**
* Created by 05 on 2018/8/20.
*/

#include <opencv2/core/core_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <iostream>

using namespace std;
using namespace cv;

namespace IP_HW6 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btn_HW6;
	protected:

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
			this->btn_HW6 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn_HW6
			// 
			this->btn_HW6->Location = System::Drawing::Point(98, 115);
			this->btn_HW6->Name = L"btn_HW6";
			this->btn_HW6->Size = System::Drawing::Size(75, 23);
			this->btn_HW6->TabIndex = 0;
			this->btn_HW6->Text = L"IP_HW6";
			this->btn_HW6->UseVisualStyleBackColor = true;
			this->btn_HW6->Click += gcnew System::EventHandler(this, &MyForm::btn_HW6_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->btn_HW6);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btn_HW6_Click(System::Object^  sender, System::EventArgs^  e) {

		Mat input = imread("HW6.png", -1); //Ūcanny��
		Mat ori = imread("HW6.jpg", -1);   //Ū�m��
		float rMax = sqrt(input.rows * input.rows + input.cols * input.cols);  //R�̤j�����p
		float r(0.0), r_first(0.0), r_second(0.0), r_third(0.0);  //�U���u��R
		const float PI(3.1415926);  //��P�v
		int max_first(0), max_second(0), max_third(0), sita_first(0), sita_second(0), sita_third(0), y(0);  //�̤j�ȡB���סBy�b

		Mat polar(181, 2 * rMax, CV_32S, Scalar(0));  //���y�й�

		//�Ncanny���ഫ�췥�y�йϤW�A�Ncanny�ϦU�I���p���M�췥�y�ФW�A�b���y�Ъ��Ӧ�m+1
		for (int i = 0; i < input.rows; i++) {
			for (int j = 0; j < input.cols; j++) {

				if (input.at<uchar>(i, j) == 255) {

					for (int angle = 0; angle < 181; angle++) {

						r = j * cos((double)angle * PI / 180) + i * sin((double) angle * PI / 180);
						r = r + rMax + 0.5;
						polar.at<int>(angle, (int)r)++;
					}
				}
			}
		}
		//��X���y�йϪ��̤j3�ӭ�
		for (int i = 0; i < polar.rows; i++) {
			for (int j = 0; j < polar.cols; j++) {

				if (polar.at<int>(i, j) > max_first) {
					max_first = polar.at<int>(i, j);
					sita_first = i;
					r_first = j - rMax;
				}
				else if (polar.at<int>(i, j) > max_second) {
					max_second = polar.at<int>(i, j);
					sita_second = i;
					r_second = j - rMax;
				}
				else if (polar.at<int>(i, j) > max_third) {
					max_third = polar.at<int>(i, j);
					sita_third = i;
					r_third = j - rMax;
				}
			}
		}
		//�b�m�ϤW�e�X��쪺���u
		for (int j = 0; j < input.cols; j++) {
			
			//�Ĥ@���u�e�Žu
			if (sita_first == 0 || sita_first == 180) y = 0;
			else y = ( r_first - j * cos((double)sita_first * PI / 180) ) / sin((double)sita_first * PI / 180) + 0.5;
			if(y < input.rows && y >= 0){
				ori.at<Vec3b>(y, j)[0] = 255;
				ori.at<Vec3b>(y, j)[1] = 0;
				ori.at<Vec3b>(y, j)[2] = 0;
			}
			//�ĤG���e��u
			if (sita_second == 0 || sita_second == 180) y = 0;
			else y = (r_second - j * cos((double)sita_second * PI / 180)) / sin((double)sita_second * PI / 180) + 0.5;
			if (y < input.rows && y >= 0) {
				ori.at<Vec3b>(y, j)[0] = 0;
				ori.at<Vec3b>(y, j)[1] = 255;
				ori.at<Vec3b>(y, j)[2] = 0;
			}
			//�ĤT���e���u
			if (sita_third == 0 || sita_third == 180) y = 0;
			else y = (r_third - j * cos((double)sita_third * PI / 180)) / sin((double)sita_third * PI / 180) + 0.5;
			if (y < input.rows && y >= 0) {
				ori.at<Vec3b>(y, j)[0] = 0;
				ori.at<Vec3b>(y, j)[1] = 0;
				ori.at<Vec3b>(y, j)[2] = 255;
			}
		}

		imshow("ori", ori);  //show��
		imwrite("ori.jpg", ori);//�s��
	}
	};
}
