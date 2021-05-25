#pragma once
class RenderComponent : public Component
{
public:
	Mesh * mesh;
	Texture * text;
	RenderComponent();
	~RenderComponent();
	// Component��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	void Render3D();
	void Render2D();

};

