using Avalonia.Controls;
using Avalonia.Threading;
using Google.Cloud.Firestore;

namespace KV_Pit;

public partial class MainWindow : Window
{
    private FirestoreDb? db;

    public MainWindow()
    {
        InitializeComponent();
        InitializeFirestore();
    }

    private async void InitializeFirestore()
    {
        db = await FirestoreDb.CreateAsync("ultimate-balm-474810-v7");

        CollectionReference collection = db.Collection("telemetry");

        collection.OrderBy("timestamp").LimitToLast(1)
            .Listen(snapshot =>
            {
                foreach (DocumentSnapshot doc in snapshot.Documents)
                {
                    var data = doc.ToDictionary();

                    Dispatcher.UIThread.Post(() =>
                    {
                        BvText.Text = $"バッテリー電圧: {data["bv"]} V";
                        BcText.Text = $"バッテリー電流: {data["bc"]} A";
                        MvText.Text = $"モーター電圧: {data["mv"]} V";
                        McText.Text = $"モーター電流: {data["mc"]} A";
                        SpeedText.Text = $"速度: {data["speed"]} km/h";
                        TempText.Text = $"温度: {data["temp"]} ℃";
                        WhText.Text = $"消費電力量: {data["wh"]} Wh";
                        AhText.Text = $"消費電流量: {data["ah"]} mAh";
                        SocText.Text = $"推定バッテリー残量: {data["soc"]} %";
                        DistanceText.Text = $"走行距離: {data["distance"]} km";
                        TimeText.Text = $"経過時間: {data["time"]} s";
                    });
                }
            });
    }
}