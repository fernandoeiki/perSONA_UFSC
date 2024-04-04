using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using VA;
using ZedGraph;
using TagLib;
using System.Windows.Controls;
using com.itextpdf.text.pdf;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace perSONA
{
    public partial class testSetup : Form
    {
        public speechPerceptionTest test;
        private readonly IvAInterface vAInterface;
        string speechFolder = "data/Sounds/Speech";
        string azbio = "data/Sounds/Speech/AzBio";
        string noiseFolder = "data/Sounds/Noise";
        string[] subjects;
        string testOption = "speechPeception";
        public VANet vA { get; private set; }
        public testSetup(IvAInterface vAInterface, string testTipe, string[] subjects)
        {

            InitializeComponent();
            resizeScreen();
            this.subjects = subjects;
            applicatorLabel.Text = subjects[0];
            patientLabel.Text = subjects[1];

            this.vAInterface = vAInterface;


            testTab.SelectedIndexChanged += testTab_SelectedIndexChanged;
            comboBox3.DataSource = Directory.GetFiles(noiseFolder).Select(Path.GetFileName).ToArray();
            comboBox3.SelectedItem = comboBox3.Items.IndexOf("4talker-babble_ISTS.wav");
            string[] procedureList = { "2-down-1-up", "1-down-1-up" };
            comboBox1.DataSource = procedureList;
            comboBox1.SelectedItem = comboBox1.Items.IndexOf("2-down-1-up");

            noiseLogic.Checked = false;
            speechLogic.Checked = true;

            string[] testnames = Directory.GetDirectories(speechFolder).Select(Path.GetFileName).ToArray();
            for (int i = 0; i < testnames.Length; i++)
            {
                Console.WriteLine(testnames[i]);
                speechFiles.Items.Add(testnames[i]);
            }
            speechFiles.SelectedItem = speechFiles.Items[0];

            vAInterface.plotSceneGraph(zedGraphControl1, getSceneDistances(), getSceneAngles());

            switch (testTipe)
            {
                case "Speech Right":
                    speechRight.Checked = true;
                    break;

                case "Speech Left":
                    speechLeft.Checked = true;
                    break;

                case "Speech Front":
                    speechFront.Checked = true;
                    break;

                default:
                    break;
            }

            //codigo para azbio 02/12/2023

            string[] azbioFiles = Directory.GetDirectories(azbio).Select(Path.GetFileName).ToArray();
            for (int i = 0; i < azbioFiles.Length; i++)
            {
                //Console.WriteLine(azbioFiles[i]);
                azbioTest.Items.Add(azbioFiles[i]);
            }
            azbioTest.SelectedItem = azbioTest.Items[0];

            //Código para sessão de retomar teste 

            string folderPath = Path.Combine(Properties.Settings.Default.RESULTS_FOLDER, "nonFinished");
            continueTestBox.Items.Clear();
            continueSentences.Items.Clear();

            try
            {
                // Verifique se a pasta existe
                if (Directory.Exists(folderPath))
                {
                    // Obtenha todos os arquivos com a extensão .json na pasta
                    string[] arquivosJson = Directory.GetFiles(folderPath, "*.json");

                    // Adicione os nomes dos arquivos ao ComboBox
                    foreach (string arquivo in arquivosJson)
                    {
                        continueTestBox.Items.Add(Path.GetFileName(arquivo));
                    }
                    if (continueTestBox.Items.Count > 0)
                    {
                        // Selecionar automaticamente o primeiro item
                        continueTestBox.SelectedIndex = 0;
                    }
                }
                else
                {
                    MessageBox.Show("A pasta não existe.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ocorreu um erro: {ex.Message}");
            }


        }



        private void BeginTest_Click(object sender, EventArgs e)
        {
            double[] angles = getSceneAngles();
            double[] radius = getSceneDistances();
            double angleSpeech = checkDirection(speechLeft.Checked, speechFront.Checked, speechRight.Checked); ;
            double radiusSpeech = (double)speechDistance.Value;
            double angleNoise = checkDirection(noiseLeft.Checked, noiseFront.Checked, noiseRight.Checked); ;
            double radiusNoise = (double)noiseDistance.Value;
            double snr = (double)initialSnr.Value;
            string noiseFile = Path.Combine(noiseFolder, comboBox3.SelectedItem.ToString());
            string sceeneLogic = checkLogic(noiseLogic.Checked);
            string procedureString = (string)comboBox1.SelectedItem;
            string TestOption = testOption;

            double[] presentingLogic = { double.Parse(procedureString.Split('-')[0]), double.Parse(procedureString.Split('-')[2]) };
            double acceptanceRule = (double)numericRule.Value;
            double signalToNoiseStep = (double)stepSnr.Value;
            double AzbionumSentences = (double)numSetencesCount.Value;

            if (testOption == "azbio")
            {
                string Location = Path.Combine(azbio, azbioTest.GetItemText(azbioTest.SelectedItem));
                speechFolder = vAInterface.getDatabaseFiles(Location);

                speechPerceptionTest speechTest = new speechPerceptionTest(
                                                    angleSpeech, radiusSpeech,
                                                    angleNoise, radiusNoise,
                                                    speechFolder, noiseFile,
                                                    textBox1.Text, snr,
                                                    presentingLogic,
                                                    acceptanceRule / 100, signalToNoiseStep,
                                                    subjects[0], subjects[1], sceeneLogic, TestOption, AzbionumSentences);
                string testString = speechTest.ToString();
                vAInterface.concatText(testString);

                if (Application.OpenForms["speechIterTestForm"] == null)
                {
                    new speechIterTestForm(speechTest, vAInterface).Show();
                }
                this.Close();
            }
            else if (testOption == "continueTest")
            {
                string Location = Path.Combine(azbio, azbioTest.GetItemText(azbioTest.SelectedItem));              
                string[] continuefiles = new string[continueSentences.Items.Count];

                try
                {
                    for (int i = 0; i < continueSentences.Items.Count; i++)
                    {
                        continuefiles[i] = continueSentences.Items[i].ToString();
                    }

                    speechFolder = vAInterface.getDatabaseFiles(Location);
                    speechPerceptionTest speechTest = new speechPerceptionTest(
                                                        angleSpeech, radiusSpeech,
                                                        angleNoise, radiusNoise,
                                                        speechFolder, noiseFile,
                                                        textBox1.Text, snr,
                                                        presentingLogic,
                                                        acceptanceRule / 100, signalToNoiseStep,
                                                        subjects[0], subjects[1], sceeneLogic, TestOption, AzbionumSentences,
                                                        continuefiles);
                    string testString = speechTest.ToString();
                    vAInterface.concatText(testString);

                    if (Application.OpenForms["speechIterTestForm"] == null)
                    {
                        new speechIterTestForm(speechTest, vAInterface).Show();
                    }
                    this.Close();
                }
                catch (Exception ex)
                {

                }
            }
            else
            {
                string Location = Path.Combine(speechFolder, speechFiles.GetItemText(speechFiles.SelectedItem), speechLists.GetItemText(speechLists.SelectedItem));
                speechFolder = vAInterface.getDatabaseFiles(Location);

                speechPerceptionTest speechTest = new speechPerceptionTest(
                                                    angleSpeech, radiusSpeech,
                                                    angleNoise, radiusNoise,
                                                    speechFolder, noiseFile,
                                                    textBox1.Text, snr,
                                                    presentingLogic,
                                                    acceptanceRule / 100, signalToNoiseStep,
                                                    subjects[0], subjects[1], sceeneLogic, TestOption, AzbionumSentences);
                string testString = speechTest.ToString();
                vAInterface.concatText(testString);

                if (Application.OpenForms["speechIterTestForm"] == null)
                {
                    new speechIterTestForm(speechTest, vAInterface).Show();
                }
                this.Close();
            }


        }

        private void playSpeech_Click(object sender, EventArgs e)
        {
            string Location = Path.Combine(speechFolder, speechFiles.GetItemText(speechFiles.SelectedItem), speechLists.GetItemText(speechLists.SelectedItem));
            string currentFile = System.IO.Path.Combine(Location, speechSentences.GetItemText(speechSentences.SelectedItem));
            double[] angles = getSceneAngles();
            double[] radius = getSceneDistances();
            double angleSpeech = checkDirection(speechLeft.Checked, speechFront.Checked, speechRight.Checked); ;
            double radiusSpeech = (double)speechDistance.Value;
            double angleNoise = checkDirection(noiseLeft.Checked, noiseFront.Checked, noiseRight.Checked); ;
            double radiusNoise = (double)noiseDistance.Value;
            double snr = (double)initialSnr.Value;
            string noiseFile = Path.Combine(noiseFolder, comboBox3.SelectedItem.ToString());

            vA = vAInterface.getVa();
            vA.Reset();
            int receiverId = vA.CreateSoundReceiver("Subject");

            double xSides = 0;
            double zFront = 0;
            double yHeight = 1.7;

            VAVec3 receiverPosition = new VAVec3(xSides, yHeight, zFront);
            VAVec3 receiverOrientationV = new VAVec3(0, 0, -1);
            VAVec3 receiverOrientationU = new VAVec3(0, 1, 0);

            vA.SetSoundReceiverPosition(receiverId, receiverPosition);
            vA.SetSoundReceiverOrientationVU(receiverId, receiverOrientationV, receiverOrientationU);
            vAInterface.concatText(string.Format("Receiver: {3} at position: {0},{1},{2}, looking forward ",
                                     xSides, zFront, yHeight, receiverId));

            int hrirId = vA.CreateDirectivityFromFile("data/ITA_Artificial_Head_5x5_44kHz_128.v17.ir.daff");
            vA.SetSoundReceiverDirectivity(receiverId, hrirId);

            if (simulaFala.Checked==true)
            {
                string speechFile = currentFile;
                vAInterface.concatText(speechFile);
                vAInterface.concatText(string.Format("Angle speech:", angleSpeech));
                vAInterface.createAcousticScene(speechFile, speechFile);

                vAInterface.playScene(radiusSpeech, angleSpeech, snr);

                TagLib.File file = TagLib.File.Create(currentFile); //Take file at taglibe format   
                var duration = file.Properties.Duration;            //Take duration
                int msecduration = Convert.ToInt32(duration.TotalMilliseconds) + 20;
                vAInterface.concatText(string.Format("Speech time: {0}", msecduration.ToString()));
                //Thread.Sleep(msecduration);      //Sleep fileduration milliseconds

                // Move o processamento para uma thread em segundo plano evitando o travamento da thread principal
                Task.Run(() =>
                {
                    Thread.Sleep(msecduration); //sleep file durantion
                    vAInterface.stopScene(true, true);
                });

            }

            else if (simulaRuido.Checked == true)
            {
                string speechFile = noiseFile;
                vAInterface.concatText(noiseFile);
                vAInterface.concatText(
                    string.Format("Angle noise:", angleNoise));
                vAInterface.createAcousticScene(noiseFile, noiseFile);

                vAInterface.playScene(radiusNoise, angleNoise, snr);

                TagLib.File file = TagLib.File.Create(currentFile); //Take file at taglibe format   
                var duration = file.Properties.Duration;            //Take duration
                int msecduration = Convert.ToInt32(duration.TotalMilliseconds) + 20;
                vAInterface.concatText(string.Format("Speech time: {0}", msecduration.ToString()));
               
                // Move o processamento para uma thread em segundo plano evitando o travamento da thread principal
                Task.Run(() =>
                {
                    Thread.Sleep(msecduration); //sleep file durantion
                    vAInterface.stopScene(true, true);
                });
            }

            else if (simulaFalaeRuido.Checked == true)
            {
                string speechFile = currentFile;
                vAInterface.concatText(speechFile);
                vAInterface.concatText(
                    string.Format("Angle speech: {0}, Angle noise: {1}", angleSpeech, angleNoise));
                vAInterface.createAcousticScene(speechFile, noiseFile);

                vAInterface.playScene(radiusSpeech, angleSpeech, snr);

                TagLib.File file = TagLib.File.Create(currentFile); //Take file at taglibe format   
                var duration = file.Properties.Duration;            //Take duration
                int msecduration = Convert.ToInt32(duration.TotalMilliseconds) + 20;
                vAInterface.concatText(string.Format("Speech time: {0}", msecduration.ToString()));
               
                // Move o processamento para uma thread em segundo plano evitando o travamento da thread principal
                Task.Run(() =>
                {
                    Thread.Sleep(msecduration); //sleep file durantion
                    vAInterface.stopScene(true, true);
                });
            }
        }

        public string checkLogic(bool noise)
        {
            if(noise)
            {
                return "NoiseConstant";
            }
            else 
            {
                return "SpeechConstant";
            }
        }

        private double checkDirection(bool left, bool front, bool right)
        {
            if (left)
            {
                return -90;
            }
            else if (front)
            {
                return 0;
            }
            else
            {
                return 90;
            }
        }

        private double[] getSceneAngles()
        {
            double angleSpeech = checkDirection(speechLeft.Checked, speechFront.Checked, speechRight.Checked);
            double angleNoise = checkDirection(noiseLeft.Checked, noiseFront.Checked, noiseRight.Checked);

            double[] angles = { angleSpeech, angleNoise };
            return angles;
        }

        private double[] getSceneDistances()
        {
            double radiusSpeech = (double)speechDistance.Value;
            double radiusNoise = (double)noiseDistance.Value;
            double[] radius = { radiusSpeech, radiusNoise };

            return radius;
        }

        private void speechLeft_CheckedChanged(object sender, EventArgs e)
        {
            vAInterface.plotSceneGraph(zedGraphControl1, getSceneDistances(), getSceneAngles());
        }

        private void speechFront_CheckedChanged(object sender, EventArgs e)
        {
            vAInterface.plotSceneGraph(zedGraphControl1, getSceneDistances(), getSceneAngles());
        }

        private void speechRight_CheckedChanged(object sender, EventArgs e)
        {
            vAInterface.plotSceneGraph(zedGraphControl1, getSceneDistances(), getSceneAngles());
        }

        private void noiseLeft_CheckedChanged(object sender, EventArgs e)
        {
            vAInterface.plotSceneGraph(zedGraphControl1, getSceneDistances(), getSceneAngles());
        }

        private void noiseFront_CheckedChanged(object sender, EventArgs e)
        {
            vAInterface.plotSceneGraph(zedGraphControl1, getSceneDistances(), getSceneAngles());
        }

        private void noiseRight_CheckedChanged(object sender, EventArgs e)
        {
            vAInterface.plotSceneGraph(zedGraphControl1, getSceneDistances(), getSceneAngles());
        }

        private void speechDistance_ValueChanged(object sender, EventArgs e)
        {
            vAInterface.plotSceneGraph(zedGraphControl1, getSceneDistances(), getSceneAngles());
        }

        private void noiseDistance_ValueChanged(object sender, EventArgs e)
        {
            vAInterface.plotSceneGraph(zedGraphControl1, getSceneDistances(), getSceneAngles());
        }
        private void resizeScreen()
        {
            double PCResolutionWidth = Screen.PrimaryScreen.Bounds.Width;
            double PCResolutionHeight = Screen.PrimaryScreen.Bounds.Height;
            double formWidth = this.Size.Width;
            double formHeight = this.Size.Height;


            if (PCResolutionHeight>768) 
            {
                speechSentences.Anchor = (AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Right | AnchorStyles.Left);
            }
            else
            {
                speechSentences.Anchor = (AnchorStyles.Top | AnchorStyles.Right | AnchorStyles.Left);
            }
           


            if ((formWidth < PCResolutionWidth) | (formHeight < PCResolutionHeight))
            {
                int newWidth = Convert.ToInt32(PCResolutionWidth * 0.95);
                int newHeight = Convert.ToInt32(PCResolutionHeight * 0.95);
                this.Size = new Size(newWidth, newHeight);
            }
        }

        private void speechFiles_SelectedIndexChanged(object sender, EventArgs e)
        {
            speechLists.Items.Clear();
            string Lists = Path.Combine(speechFolder, speechFiles.SelectedItem.ToString());
            Console.WriteLine(Lists);
            string[] testlist = Directory.GetDirectories(Lists).Select(Path.GetFileName).ToArray();
            for (int i = 0; i < testlist.Length; i++)
            {
                Console.WriteLine(testlist[i]);
                speechLists.Items.Add(testlist[i]);
            }
            speechLists.SelectedItem = speechLists.Items[0];
        }

        private void speechLists_SelectedIndexChanged(object sender, EventArgs e)
        {
            string Location = Path.Combine(speechFolder, speechFiles.GetItemText(speechFiles.SelectedItem), speechLists.GetItemText(speechLists.SelectedItem));
            string[] filePaths = System.IO.Directory.GetFiles(Location, "*.wav");
            string[] Files = filePaths.Select(System.IO.Path.GetFileName).ToArray();

            speechSentences.DataSource = Files;
            speechSentences.SelectedIndex = 0;
        }

        private void azbioTest_SelectedIndexChanged(object sender, EventArgs e)
        {
            string Location = Path.Combine(azbio, azbioTest.SelectedItem.ToString());
            Console.WriteLine(Location);
            string[] filePaths = System.IO.Directory.GetFiles(Location, "*.wav");
            string[] Files = filePaths.Select(System.IO.Path.GetFileName).ToArray();
            Console.WriteLine(Files);

            azbioSentences.DataSource = Files;
            azbioSentences.SelectedIndex = 0;
        }


        private void noiseLogic_CheckedChanged(object sender, EventArgs e)
        {
            if(noiseLogic.Checked == true)
            {
                speechLogic.Checked = false;
            }
            else
            {
                speechLogic.Checked = true;
            }
        }

        private void speechLogic_CheckedChanged(object sender, EventArgs e)
        {
            if(speechLogic.Checked == true)
            {
                noiseLogic.Checked = false;
            }
            else
            {
                noiseLogic.Checked = true;
            }
        }

        private void sceneLogic_Enter(object sender, EventArgs e)
        {

        }




        private void testTab_SelectedIndexChanged(object sender, EventArgs e)
        {
            string selectedTab = testTab.SelectedTab.Name;

            if (selectedTab == "speechPerceptionTab")
            {
                Console.WriteLine(selectedTab);
                testOption = "speechPeception";
            }
            else if (selectedTab == "azbioTab")
            {
                Console.WriteLine(selectedTab);
                testOption = "azbio";
            }
            else if (selectedTab == "continueTest") 
            {               
                Console.WriteLine(selectedTab);
                testOption = "continueTest";
                
            }
        }





        private void groupBox7_Enter(object sender, EventArgs e)
        {

        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void continueTestBox_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            string pasta = Path.Combine(Properties.Settings.Default.RESULTS_FOLDER, "nonFinished"); ;
            string nomeArquivoSelecionado = continueTestBox.SelectedItem.ToString();
            string caminhoArquivo = Path.Combine(pasta, nomeArquivoSelecionado);
            Console.WriteLine(caminhoArquivo);
            try
            {
                // Verifique se o arquivo existe
                if (System.IO.File.Exists(caminhoArquivo))
                {
                    string json = System.IO.File.ReadAllText(caminhoArquivo);

                    JArray arrayNomesArquivos = JArray.Parse(json);

                    continueSentences.Items.Clear();

                    foreach (var nomeArquivo in arrayNomesArquivos)
                    {
                        continueSentences.Items.Add(nomeArquivo.ToString());
                    }
                }
                else
                {
                    MessageBox.Show("O arquivo selecionado não existe.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ocorreu um erro ao ler o arquivo: {ex.Message}");
            }
        }
    }
}
