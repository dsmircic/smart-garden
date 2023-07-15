int litres;
int calculate_litre_output(int flow)
{
    litres = flow / 60;
    total_litres += litres;

    Serial.print("Ouput Liquid Quantity: ");
    Serial.print(total_litres);
    Serial.println("L");

    return litres;
}