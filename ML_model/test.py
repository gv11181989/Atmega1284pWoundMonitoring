from pathlib import Path

size = Path('model_poly.h').stat().st_size

print(f'{size/1024} kb')