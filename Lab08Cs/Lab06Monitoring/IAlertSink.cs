namespace Lab06Monitoring
{
    /// <summary>
    /// Интерфейс приёмника оповещений.
    /// </summary>
    public interface IAlertSink
    {
        void ReceiveAlert(Alert alert);
    }
}
