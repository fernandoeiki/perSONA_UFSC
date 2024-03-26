using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using VA;
using ZedGraph;
using TagLib;
using System.Windows.Media;
using System.Runtime.InteropServices.WindowsRuntime;

namespace perSONA
{
    public partial class speechIterTestForm : Form
    {
        private readonly speechPerceptionTest test;
        private readonly IvAInterface vAInterface;

        public string namePatient;

        public string[] speechFiles;
        public string currentFile;
        string[] audioList2;
        string caminhoArquivo;
        string caminhoArquivoList;

        public bool currentStreak = false;

        public double SumofAnswers;
        public double SumofWords;
        private double actualSNR;

        double[] signalToNoiseArray;

        private int allCountCorrectWords;
        private int allCountWords;
        private int RightSentences = 0;
        private int rt = 0;
        

        List<string> iteractiveResponseTime;
        List<string> iteractiveResponsePercentage;

        DateTime tryalStartTime;

        public VANet vA { get; private set; }

        public speechIterTestForm(speechPerceptionTest test, IvAInterface vAInterface)
        {
            InitializeComponent();
            resizeScreen();
            signalToNoiseArray = new double[] { actualSNR };
            patientLabel.Text = test.PatientName;
            applicatorLabel.Text = test.Applicator;

            tryalStartTime = DateTime.Now;
            timer1.Tick += new EventHandler(timer1_Tick);
            this.timer1.Interval = 1000;
            this.timer1.Enabled = true;

            this.test = test;
            this.vAInterface = vAInterface;

            double[] radiusList = { test.RadiusSpeech, test.RadiusNoise };
            double[] angleList = { test.AngleSpeech, test.AngleNoise };

            vAInterface.plotSceneGraph(zedGraphControl2, radiusList, angleList);

            if (test.TestOption == "azbio")
            {
                //detailsBox.Text = test.ToString();

                string[] filePaths = System.IO.Directory.GetFiles(test.SpeechFolder, "*.wav");
                speechFiles = filePaths.Select(System.IO.Path.GetFileName).ToArray();

                Random random = new Random();
                speechFiles = speechFiles.OrderBy(x => random.Next()).ToArray();

                // Os comentarios seguintes funcionam para criar dois testes com 500 sentenças cada, em específico para o teste AzBio
                //speechFiles = speechFiles.Take(500).ToArray();
                //remainingFiles = speechFiles.Skip(500).ToArray();

                string[] firstGroup = speechFiles.Take((int)test.azbionum).ToArray();
                //string[] remainingFiles = speechFiles.Skip(500).ToArray();
                
               // string[] repeatedSentences = firstGroup.Take(13).ToArray();

               // string[] finalAudioList = remainingFiles.OrderBy(x => random.Next()).ToArray();
               //finalAudioList = remainingFiles.Concat(repeatedSentences).ToArray();
               //finalAudioList = finalAudioList.OrderBy(x => random.Next()).ToArray();

               // audioList2 = finalAudioList;

                speechFiles = firstGroup;

                //Console.WriteLine("---"+audioList2.Length+"----"+remainingFiles.Length+"-------"+repeatedSentences.Length);

                filenameList.DataSource = speechFiles;
                filenameList.SelectedIndex = 0;

                currentFile = System.IO.Path.Combine(test.SpeechFolder, filenameList.GetItemText(filenameList.SelectedItem));

                //detailsBox.AppendText(currentFile);
                vAInterface.fillWords(currentFile, testWordsList);
                getDirectoryAzbio();

                caminhoArquivoList = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Desktop), test.PatientName + ".txt");
                
                try
                {
                    using (System.IO.StreamWriter writer = System.IO.File.AppendText(caminhoArquivoList))
                    {
                        writer.WriteLine(test.PatientName);
                        foreach (string file in speechFiles)
                        {
                            writer.WriteLine(file);
                        }
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Não foi possível salvar a lista de sentenças");
                }

            }
            else
            {
                //detailsBox.Text = test.ToString();
                string[] filePaths = System.IO.Directory.GetFiles(test.SpeechFolder, "*.wav");
                speechFiles = filePaths.Select(System.IO.Path.GetFileName).ToArray();

                filenameList.DataSource = speechFiles;
                filenameList.SelectedIndex = 0;

                currentFile = System.IO.Path.Combine(test.SpeechFolder, filenameList.GetItemText(filenameList.SelectedItem));

                //detailsBox.AppendText(currentFile);
                vAInterface.fillWords(currentFile, testWordsList);
                updateIterationGraph(zedGraphControl1.GraphPane, signalToNoiseArray);


            }





            updatePercentage();

            computedAudioText.Text = (filenameList.SelectedIndex + 1).ToString();
            totalWordsText.Text = string.Format("{0}", filenameList.Items.Count);
            actualSNR = test.SignalToNoise;
            textBox3.Text = string.Format("{0}", actualSNR);

            signalToNoiseArray = new double[] { actualSNR };
            

            iteractiveResponseTime = new List<string> { };
            iteractiveResponsePercentage = new List<string> { };

           
                if (test.SceeneLogic == "SpeechConstant")
                {
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

                    string speechFile = currentFile;
                    vAInterface.concatText(speechFile);
                    vAInterface.concatText(
                        string.Format("Angle speech: {0}, Angle noise: {1}", test.AngleSpeech, test.AngleNoise));
                    vAInterface.createAcousticScene(speechFile, test.NoiseFile);

                }

                else
                {
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

                    string speechFile = currentFile;
                    vAInterface.concatText(speechFile);
                    vAInterface.concatText(
                        string.Format("Angle speech: {0}, Angle noise: {1}", test.AngleSpeech, test.AngleNoise));
                    vAInterface.createAcousticScene(speechFile, test.NoiseFile);
                }
            
        }

        private void AllCorrect_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < testWordsList.Items.Count; i++)
            {
                testWordsList.SetSelected(i, true);
            }
        }

        public Tuple<int, int> updatePercentage()
        {
            int correctWords = testWordsList.SelectedItems.Count;
            int totalWords = testWordsList.Items.Count;
            textBox1.Text = string.Format("{0}", correctWords);
            textBox2.Text = string.Format("{0}%", Math.Round(100.0 * correctWords / totalWords, 2));
            return Tuple.Create(correctWords, totalWords);
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            updatePercentage();
        }

        private void AllIncorrect_Click(object sender, EventArgs e)
        {
            testWordsList.ClearSelected();
        }


        private void playCurrentScene_Click(object sender, EventArgs e)
        {
            if(test.SceeneLogic == "SpeechConstant")
            {                
                if (false)
                {
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

                    string speechFile = currentFile;
                    vAInterface.concatText(speechFile);
                    vAInterface.concatText(
                        string.Format("Angle speech: {0}, Angle noise: {1}", test.AngleSpeech, test.AngleNoise));
                    vAInterface.createAcousticScene(speechFile, test.NoiseFile);
                    rt = 0;
                }

                vAInterface.createSpeechScene(currentFile);

                if (test.TestOption == "azbio")
                {
                    vAInterface.playSceneAzbio(test.RadiusSpeech, test.AngleSpeech, actualSNR);
                }
                else
                {
                    vAInterface.playSceneSpeechFixed(test.RadiusSpeech, test.AngleSpeech, actualSNR);
                }
                TagLib.File file = TagLib.File.Create(currentFile); //Take file at taglibe format   
                var duration = file.Properties.Duration;            //Take duration
                int msecduration = Convert.ToInt32(duration.TotalMilliseconds) + 20;
                vAInterface.concatText(string.Format("Speech time: {0}", msecduration.ToString()));

                // Move o processamento para uma thread em segundo plano evitando o travamento da thread principal
                Task.Run(() =>
                {
                    Thread.Sleep(msecduration); //sleep file duration
                    vAInterface.stopScene(true, true);
                });
                rt++;
            }

            else
            {
                vAInterface.createSpeechScene(currentFile);
                vAInterface.playSceneNoiseFixed(test.RadiusSpeech, test.AngleSpeech, actualSNR);

                TagLib.File file = TagLib.File.Create(currentFile); //Take file at taglibe format   
                var duration = file.Properties.Duration;            //Take duration
                int msecduration = Convert.ToInt32(duration.TotalMilliseconds) + 20;
                vAInterface.concatText(string.Format("Speech time: {0}", msecduration.ToString()));

                // Move o processamento para uma thread em segundo plano evitando o travamento da thread principal
                Task.Run(() =>
                {
                    Thread.Sleep(msecduration); //sleep file duration
                    vAInterface.stopScene(true, true);
                });
            }
        }

        private void updateIterationGraph(GraphPane graph, double[] signalToNoiseArray)
        {
            ZedGraph.GraphPane myPane = graph;
            myPane.CurveList.Clear();
            PointPairList snrArray = new PointPairList();
            List<double> indexes = new List<double>();
            for (int i = 1; i < signalToNoiseArray.Length + 2; i++)
            {
                double value = i;
                indexes.
                    Add(value);
            }

            string tipoSNR = "";

            if (test.SceeneLogic == "SpeechConstant")
            {
                 tipoSNR = "SNR adaptativa considerando potência da fala constante";
            }
            else
            {
                tipoSNR = "SNR adaptativa considerando potência do ruído constante";
            }

            snrArray.Add(indexes.ToArray(), signalToNoiseArray);
            LineItem snrCurve = myPane.AddCurve(tipoSNR, snrArray, System.Drawing.Color.Blue, SymbolType.XCross);
            snrCurve.Line.IsVisible = true;
            snrCurve.Line.Width = 2;
            snrCurve.Symbol.Size = 20;

            myPane.Legend.FontSpec.Size = 21;
            myPane.Legend.Border.IsVisible = false;
            myPane.Title.FontSpec.Size = 21;
            myPane.XAxis.Title.FontSpec.Size = 21;
            myPane.XAxis.Scale.FontSpec.Size = 21;

            myPane.YAxis.Title.FontSpec.Size = 21;
            myPane.YAxis.Scale.FontSpec.Size = 21;

            myPane.XAxis.Scale.MaxAuto = false;
            myPane.XAxis.Scale.MinAuto = false;
            myPane.YAxis.Scale.Min = -20;
            myPane.YAxis.Scale.Max = 0;

            if (indexes.Max() > 0)
            {
                myPane.YAxis.Scale.Max = (indexes.Max() + 5);
            }

            if (indexes.Min() < -20)
            {
                myPane.YAxis.Scale.Min = indexes.Min() - 5;
            }

            myPane.XAxis.Scale.Min = 0;
            myPane.XAxis.Scale.Max = signalToNoiseArray.Length + 3;

            myPane.XAxis.Title.Text = "Iterações";
            myPane.YAxis.Title.Text = "SNR [dB]";
            myPane.Title.Text = "Razões sinal-ruído apresentadas";
            myPane.XAxis.Title.FontSpec.Size = 25;
            myPane.Title.FontSpec.Size = 25;
            myPane.YAxis.Title.FontSpec.Size = 25;

            var path = Path.Combine("data", "Logo_Large.png");
            string filelogo = path;
            Image img = Image.FromFile(filelogo);
            var logo = new ImageObj(img, new RectangleF(0.87f, 1.22f, 0.15f, 0.19f), CoordType.ChartFraction, AlignH.Left, AlignV.Top);
            myPane.GraphObjList.Add(logo);

            zedGraphControl1.AxisChange();
            zedGraphControl1.Refresh();
        }

        private double getNextSNR(double currentSNR, double snrStep)
        {
            double answer = testWordsList.SelectedItems.Count;
            double totalWords = testWordsList.Items.Count;
            double nextSNR = 0;

            if (answer / totalWords < test.AcceptanceRule)
            {
                nextSNR = currentSNR + snrStep;
                currentStreak = false;
                streakText.Text = "False";
            }

            else if (test.PresentingLogic[0] == 2) //test verifies 2 form "2 down 1 up"
            {
                if (currentStreak)
                {
                    nextSNR = currentSNR - snrStep;
                    currentStreak = false;
                    streakText.Text = "False";
                }
                else
                {
                    nextSNR = currentSNR;
                    currentStreak = true;
                    streakText.Text = "True";
                }
            }

            else if (test.PresentingLogic[0] == 1) //test verifies 1 form "1 down 1 up"
            {
                nextSNR = currentSNR - snrStep;
                currentStreak = true;
                streakText.Text = "True";
            }

            return nextSNR;
        }

        

        private void NextSentence_Click(object sender, EventArgs e)
        {
            actualSNR = getNextSNR(actualSNR, test.SignalToNoiseStep);

            string responseTime = currentTryal.Text;
            double answer = testWordsList.SelectedItems.Count;
            double totalWords = testWordsList.Items.Count;
            double percentage = Math.Round(100 * (answer / totalWords));
            string responsePercentage = string.Format("{0}%", Math.Round(100 * (answer / totalWords))); 
            vAInterface.concatText(string.Format("{0} - response time: {1}", string.Join(",", testWordsList.Items.Cast<string>()), responseTime));


            if (percentage > 50) 
            {
                RightSentences++;
            }


            Tuple<int, int> SpeechTestFormWords = updatePercentage();
            allCountCorrectWords += SpeechTestFormWords.Item1;
            allCountWords += SpeechTestFormWords.Item2;
            double PORCENTAGEMDEACERTOTOTAL = 100.0 * allCountCorrectWords / allCountWords;

            if (test.TestOption == "azbio")
            {
                

                string AzBioLista = filenameList.Text;
                string AzBioSentence = "";
                string palavrasErradas = "";

                foreach (object item in testWordsList.Items)
                {
                    AzBioSentence += item.ToString() + " ";
                    
                    if (testWordsList.SelectedItems.Contains(item))
                    { }
                    else
                    {
                        palavrasErradas += item.ToString() + " ";
                    }
                }

                if (percentage == 100)
                {
                    try
                    {
                        using (System.IO.StreamWriter writer = System.IO.File.AppendText(caminhoArquivo))
                        {
                            writer.WriteLine(AzBioLista + " - " + AzBioSentence + "- ok");
                        }
                    }
                    catch (Exception ex)
                    { }
                }
                else 
                {
                    using (System.IO.StreamWriter writer = System.IO.File.AppendText(caminhoArquivo))
                    {
                        writer.WriteLine(AzBioLista + " - " + AzBioSentence + "- palavras erradas: " + palavrasErradas);
                    }
                }
            }





            if (filenameList.SelectedIndex + 1 < filenameList.Items.Count)
            {
                filenameList.SelectedIndex = filenameList.SelectedIndex + 1;
                currentFile = System.IO.Path.Combine(test.SpeechFolder, filenameList.GetItemText(filenameList.SelectedItem));

                //detailsBox.AppendText(currentFile);
                vAInterface.fillWords(currentFile, testWordsList);


                textBox4.Text = string.Format("{0}", allCountCorrectWords);
                textBox5.Text = string.Format("{0}%", Math.Round(100.0 * allCountCorrectWords / allCountWords, 2)); // 100.0 * (correctWords / totalWords));


                computedAudioText.Text = (filenameList.SelectedIndex + 1).ToString();
                totalWordsText.Text = string.Format("{0}", filenameList.Items.Count);

                signalToNoiseArray = signalToNoiseArray.Concat(new double[] { actualSNR }).ToArray();
                iteractiveResponseTime.Add(responseTime);
                iteractiveResponsePercentage.Add(responsePercentage);
                textBox3.Text = string.Format("{0}", actualSNR);
                if (test.TestOption == "azbio") { }
                else
                {
                    updateIterationGraph(zedGraphControl1.GraphPane, signalToNoiseArray);
                }   
            }
            else
            {
                test.FinalPercentage = Math.Round(PORCENTAGEMDEACERTOTOTAL, 2);
                test.IterativeSNR = signalToNoiseArray;

                //detailsBox.AppendText("/r/n Finished list");
                test.TotalDuration = continuousTimerText.Text;
                test.IterativeDuration = iteractiveResponseTime.ToArray();
                test.IterativePercentage = iteractiveResponsePercentage.ToArray();
                test.rightSenteces = RightSentences;

                vAInterface.concatText(string.Format("Elapsed time: {0}", test.TotalDuration));

                double meanSRT = Math.Round(vAInterface.getMeanSRT(test.IterativeSNR), 2);

                string completedTestMessage = string.Format(
                    "Avaliação finalizada. SNR de convergência: {0} dB, MédiaSTR: {3} dB, Porcentagem de acertos: {4}%, Número de iterações: {1}, duração total: {2}, sentenças acertadas: {5}",
                    actualSNR, signalToNoiseArray.Length, test.TotalDuration, meanSRT, test.FinalPercentage, test.rightSenteces);

                string message = completedTestMessage;
                const string caption = "Fim da avaliação";
                var result = MessageBox.Show(message, caption,
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
                vAInterface.addCompletedTest(test);

                this.Close();

            }
            tryalStartTime = DateTime.Now;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.continuousTimerText.Text = string.Format("{0:hh\\:mm\\:ss}", DateTime.Now - test.TestStart);
            this.currentTryal.Text = string.Format("{0:mm\\:ss}", DateTime.Now - tryalStartTime);
        }

        private void resizeScreen()
        {
            double PCResolutionWidth = Screen.PrimaryScreen.Bounds.Width;
            double PCResolutionHeight = Screen.PrimaryScreen.Bounds.Height;

            double formWidth = this.Size.Width;
            double formHeight = this.Size.Height;

            if ((formWidth < PCResolutionWidth) | (formHeight < PCResolutionHeight))
            {
                int newWidth = Convert.ToInt32(PCResolutionWidth * 0.95);
                int newHeight = Convert.ToInt32(PCResolutionHeight * 0.95);
                this.Size = new Size(newWidth, newHeight);
            }
        }

        private void getDirectoryAzbio()
        {
            string diretorioAreaTrabalho = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            string baseFileName = "AzBioTest";
            string extension = ".txt";

            int sequencial = 1;

            do
            {
                caminhoArquivo = Path.Combine(diretorioAreaTrabalho, $"{baseFileName}_{sequencial}{extension}");
                sequencial++;
            } while (System.IO.File.Exists(caminhoArquivo));
        }
    }
}