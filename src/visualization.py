import pandas as pd
import folium
from folium.plugins import MarkerCluster

# ----------------------------
# 📊 1. Sample Data
# ----------------------------

# Simulated dataset of areas with attributes
data = {
    'Area': ['Zone A', 'Zone B', 'Zone C', 'Zone D', 'Zone E'],
    'Latitude': [26.9124, 26.8467, 26.7606, 26.8800, 26.9250],
    'Longitude': [75.7873, 75.8028, 75.8205, 75.7700, 75.7800],
    'Population': [15000, 23000, 12000, 18000, 27000],
    'Competitor_Count': [5, 2, 6, 1, 3],
    'Avg_Income': [45000, 52000, 43000, 49000, 51000]
}

df = pd.DataFrame(data)

# ----------------------------
# 🧠 2. Scoring Logic
# ----------------------------

def score_zone(row):
    # Simple weighted scoring: more population & income, fewer competitors = better
    return (row['Population'] / 1000) + (row['Avg_Income'] / 10000) - (row['Competitor_Count'] * 2)

df['Score'] = df.apply(score_zone, axis=1)

# ----------------------------
# 🗺️ 3. Create Map
# ----------------------------

# Center map on average coordinates
map_center = [df['Latitude'].mean(), df['Longitude'].mean()]
store_map = folium.Map(location=map_center, zoom_start=12)

# Add clustered markers
marker_cluster = MarkerCluster().add_to(store_map)

# Color zones based on score
def get_color(score):
    if score >= 12:
        return 'green'
    elif score >= 10:
        return 'orange'
    else:
        return 'red'

# Add each location to the map
for _, row in df.iterrows():
    popup_text = f"""
    <b>{row['Area']}</b><br>
    Population: {row['Population']}<br>
    Competitors: {row['Competitor_Count']}<br>
    Income: ₹{row['Avg_Income']}<br>
    Score: {row['Score']:.2f}
    """
    folium.CircleMarker(
        location=[row['Latitude'], row['Longitude']],
        radius=10,
        color=get_color(row['Score']),
        fill=True,
        fill_color=get_color(row['Score']),
        fill_opacity=0.7,
        popup=folium.Popup(popup_text, max_width=300)
    ).add_to(marker_cluster)

# ----------------------------
# 💾 4. Save Map
# ----------------------------

store_map.save("store_placement_map.html")
print("✅ Map generated! Check 'store_placement_map.html'")
